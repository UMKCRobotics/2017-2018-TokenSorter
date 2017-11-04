#include "Navigation17.h"

#include "Movement.h"

void Navigation17::set_available_directions() {
    // default
    for (int i = 0; i < DIRECTION_COUNT; ++i) {
        // all directions are not available
        available_directions[i].t = 0;
        available_directions[i].r = 0;
    }

    if (current_position.r > 0) {  // if not in the center
        if (current_position.r < MAX_R) {  // if not on outer edge of board
            // TODO: any other restrictions for moving around?
            // move counter-clockwise
            int counter_clockwise_direction = ((((current_position.t + 1) % DIRECTION_COUNT) / 2) + 1) * 2;
            available_directions[counter_clockwise_direction].t = 1;
            // don't stop on north or south
            if (available_directions[counter_clockwise_direction].t == 1 &&
                ((current_position.t + 1) % DIRECTION_COUNT == NORTH ||
                 (current_position.t + 1) % DIRECTION_COUNT == SOUTH))
            {
                available_directions[counter_clockwise_direction].t = 2;
            }

            // move clockwise
            int clockwise_direction = (((current_position.t / 2) * 2) - 2) % DIRECTION_COUNT;
            available_directions[clockwise_direction].t = -1;
            // don't stop on north or south
            if (available_directions[clockwise_direction].t == -1 &&
                ((current_position.t - 1) % DIRECTION_COUNT == NORTH ||
                 (current_position.t - 1) % DIRECTION_COUNT == SOUTH))
            {
                available_directions[counter_clockwise_direction].t = -2;
            }

            // move out
            available_directions[current_position.t].r = 1;
        }
        // move in
        available_directions[opposite(Direction(current_position.t))].r = -1;
    }
    else {  // r == 0, center of the board
        current_position.t = 0;

        for (int i = 0; i < DIRECTION_COUNT; ++i) {
            available_directions[i].t = 1;
            available_directions[i].r = 1;
        }
    }
}

bool Navigation17::turnLeft() {
    // find the amount to turn
    Direction checking_direction = (facing + 1) % DIRECTION_COUNT;
    int amount_turned = 1;  // in octants
    while (available_directions[checking_direction].t == 0 && available_directions[checking_direction].r == 0) {
        checking_direction = (checking_direction + 1) % DIRECTION_COUNT;
        ++amount_turned;

        if (amount_turned > DIRECTION_COUNT / 2) {  // > 180 degrees
            return turnRight();
        }
    }
    // found amount to turn
    int degrees = amount_turned * 45;

    // make the turn
    facing = checking_direction;
    movement->turnLeft(degrees);

    return true;
}

bool Navigation17::turnRight() {
    // find the amount to turn
    Direction checking_direction = (facing - 1) % DIRECTION_COUNT;
    int amount_turned = 1;  // in octants
    while (available_directions[checking_direction].t == 0 && available_directions[checking_direction].r == 0) {
        checking_direction = (checking_direction - 1) % DIRECTION_COUNT;
        ++amount_turned;

        if (amount_turned > DIRECTION_COUNT / 2) {  // > 180 degrees
            return turnLeft();
        }
    }
    // found amount to turn
    int degrees = amount_turned * 45;

    // make the turn
    facing = checking_direction;
    movement->turnRight(degrees);

    return true;
}

bool Navigation17::goForward() {
    if (available_directions[facing].t == 0 && available_directions[facing].r == 0) {
        // this direction not available
        return false;
    }

    // make the movement
    current_position = current_position + available_directions[facing];
    // movement->something()
    set_available_directions();
    return true;
}

bool Navigation17::goBackward() {
    if (available_directions[opposite(facing)].t == 0 && available_directions[opposite(facing)].r == 0) {
        // this direction is not available
        return false;
    }

    // make the movement
    current_position = current_position + available_directions[opposite(facing)];
    // movement->DO_IT!!()
    set_available_directions();
    return true;
}

String Navigation17::getCurrentStateInfo() {
    return "at " + current_position.str() + " facing " + String(facing);
}
