#include "Navigation17.h"

#include "Movement.h"

void Navigation17::set_available_directions() {
    // default
    for (int i = 0; i < DIRECTION_COUNT; ++i) {
        // all directions are not available
        available_directions[i].t = 0;
        available_directions[i].r = 0;
        approaches[i] = NoApproach;
    }

    if (current_position.r > 0) {  // if not in the center
        if (current_position.r < MAX_R) {  // if not on outer edge of board
            // can move around clockwise or counter clockwise
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
            // approaches moving counter clockwise
            if ((current_position.t + available_directions[counter_clockwise_direction].t) % 2) {
                // approaching odd direction counter clockwise
                approaches[counter_clockwise_direction] = FollowOnLeftUntilCrossesLine;  // TODO: verify
            }
            else {
                // approaching even direction
                approaches[counter_clockwise_direction] = FollowUntilPerpendicularLine;  // TODO: verify
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
            // approaches moving clockwise
            if ((current_position.t + available_directions[clockwise_direction].t) % 2) {
                // approaching odd direction clockwise
                approaches[counter_clockwise_direction] = FollowOnRightUntilCrossesLine;  // TODO: verify
            }
            else {
                // approaching even direction
                approaches[counter_clockwise_direction] = FollowUntilPerpendicularLine;  // TODO: verify
            }

            // move out
            available_directions[current_position.t].r = 1;
            // approaches moving out
            if (current_position.t % 2) {
                // moving out in odd direction
                approaches[current_position.t] = FollowUntilCrossingY;  // TODO: verify
            }
            // moving out in even direction is below with moving in
        }
        // move in
        int in_direction = opposite(Direction(current_position.t));
        available_directions[in_direction].r = -1;
        // approaches moving in
        if (current_position.t % 2) {
            // moving in in odd direction
            approaches[in_direction] = FollowUntilSeparatingY;  // TODO: verify
        }
        else {
            // in and out in even directions
            if (current_position.t == NORTH || current_position.t == SOUTH) {
                approaches[NORTH] = NoFollowUntilPerpendicularLine;  // TODO: verify
                approaches[SOUTH] = NoFollowUntilPerpendicularLine;  // TODO: verify
            } else {
                // east and west
                approaches[EAST] = FollowUntilPerpendicularLine;  // TODO: verify
                approaches[WEST] = FollowUntilPerpendicularLine;  // TODO: verify
            }
        }
    }
    else {  // r == 0, center of the board
        current_position.t = 0;

        for (int i = 0; i < DIRECTION_COUNT; ++i) {
            available_directions[i].t = i;
            available_directions[i].r = 1;
        }

        /* if we don't want to allow turning in the middle
         * delete that for loop and just use this
        available_directions[facing].t = facing;
        available_directions[facing].r = 1;
         */

        // TODO: approaches from center
    }

    // TODO: special cases for approaches
}

bool Navigation17::turn(const int& direction) {
    // find the amount to turn
    Direction checking_direction = (facing + direction) % DIRECTION_COUNT;
    int amount_turned = 1;  // in octants
    while (available_directions[checking_direction].t == 0 && available_directions[checking_direction].r == 0) {
        checking_direction = (checking_direction + direction) % DIRECTION_COUNT;
        ++amount_turned;

        if (amount_turned >= DIRECTION_COUNT) {
            // 360 turn
            return false;
        }
    }
    // found amount to turn
    if (amount_turned > DIRECTION_COUNT / 2) {  // > 180 degrees
        return turn(0 - direction);
    }
    int degreesLeft = amount_turned * 45 * direction;

    // make the turn
    facing = checking_direction;
    movement->turn(degreesLeft);

    return true;
}


bool Navigation17::turnLeft() {
    turn(1);
}

bool Navigation17::turnRight() {
    turn(-1);
}

// TODO: use approaches
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
