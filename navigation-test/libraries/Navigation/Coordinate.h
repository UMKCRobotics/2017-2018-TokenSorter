#ifndef INC_2017_2018_TOKENSORTER_COORDINATE_H
#define INC_2017_2018_TOKENSORTER_COORDINATE_H

#include "Arduino.h"

enum Direction {
    EAST = 0,
    NORTHEAST = 1,
    NORTH = 2,
    NORTHWEST = 3,
    WEST = 4,
    SOUTHWEST = 5,
    SOUTH = 6,
    SOUTHEAST = 7,
    DIRECTION_COUNT = 8
};

const char DIRECTION_NAMES[DIRECTION_COUNT + 1][10] = {
        "EAST",
        "NORTHEAST",
        "NORTH",
        "NORTHWEST",
        "WEST",
        "SOUTHWEST",
        "SOUTH",
        "SOUTHEAST",
        "COUNT"
};

static Direction opposite(const Direction& t) {
    return Direction((t + (DIRECTION_COUNT / 2)) % DIRECTION_COUNT);
}

/** polar coordinates (octant, number of lines from center) **/
class Coordinate {
public:
    int t;
    int r;

    Coordinate() : t(), r() {}
    Coordinate(const int& _t, const int& _r) : t(_t), r(_r) {}

    Coordinate operator+ (const Coordinate& other) {
        return { (t + other.t) % DIRECTION_COUNT, r + other.r };
    }

    String str() {
        return "(" + String(t) + ", " + String(r) + ")";
    }
};

#endif //INC_2017_2018_TOKENSORTER_COORDINATE_H
