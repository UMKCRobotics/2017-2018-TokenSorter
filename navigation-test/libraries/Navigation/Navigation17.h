#ifndef INC_2017_2018_TOKENSORTER_NAVIGATION17_H
#define INC_2017_2018_TOKENSORTER_NAVIGATION17_H

#include <Arduino.h>
#include "Coordinate.h"

class Movement;

class Navigation17 {
private:
    const static int MAX_R = 8;  // r coordinate for drop locations - TODO: verify

    Movement* movement;
    Coordinate current_position;
    Direction facing;
    Coordinate available_directions[DIRECTION_COUNT];

    /** call this when arriving somewhere **/
    void set_available_directions();
public:
    // TODO: starting position and starting facing direction
    Navigation17() : movement(nullptr),
                     current_position(0, 0),
                     facing(EAST),
                     available_directions({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}
    explicit Navigation17(Movement* _movement) : movement(_movement),
                                                 current_position(0, 0),
                                                 facing(EAST),
                                                 available_directions({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    bool turnLeft();
    bool turnRight();
    bool goForward();
    bool goBackward();

    String getCurrentStateInfo();
};

#endif //INC_2017_2018_TOKENSORTER_NAVIGATION17_H
