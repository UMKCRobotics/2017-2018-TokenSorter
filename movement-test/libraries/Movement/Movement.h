#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Arduino.h"
#include "ScrapController.h"

/// namespace to access Turn and Approach enumerations
namespace moveOptions {
	enum Turn { Left45=1, Right45, Left90, Right90, Left135, Right135, Left180, Right180 };
	enum Approach {
        NoApproach=0,
		NoFollowUntilPerpendicularLine=1,
        FollowUntilPerpendicularLine,  // 2
        FollowUntilTokenSlot,
		FollowOnLeftUntilPerpendicularLine,
        FollowOnRightUntilPerpendicularLine,  // 5
		FollowOnLeftUntilCrossesLine,
        FollowOnRightUntilCrossesLine,
		FollowUntilCrossingY,
        FollowUntilSeparatingY,  // 9
		MoveIntoStart,
        MoveIntoDropPosition
	};
	enum BackwardApproach {
		BackwardLeaveDropPosition=1,
		BackwardFollowUntilCrossingY, BackwardFollowUntilSeparatingY,
		BackwardFollowUntilPerpendicularLine
	};
}

using namespace moveOptions;

class Movement
{
public:
	Movement();
	~Movement();
	void performTurn(Turn turnType);
	void performApproach(Approach approachType);
	void performBackwardApproach(BackwardApproach approachType);
	// Turn methods
    // TODO: stop using these, make them private if we really need them (I doubt we need them), use the parameter one
	void turnLeft45() { Serial.println("Turning 45 deg to the left"); };
	void turnRight45() { Serial.println("Turning 45 deg to the right"); };
	void turnLeft90() { Serial.println("Turning 90 deg to the left"); };
	void turnRight90() { Serial.println("Turning 90 deg to the right"); };
	void turnLeft135() { Serial.println("Turning 135 deg to the left"); };
	void turnRight135() { Serial.println("Turning 135 deg to the right"); };
	void turnLeft180() { Serial.println("Turning 180 deg to the left"); };
	void turnRight180() { Serial.println("Turning 180 deg to the right"); };
    // use this
    /** negative for right **/
	void turn(const int& degreesLeft) {
        Serial.print("Turning ");
        Serial.print(abs(degreesLeft));
        if (degreesLeft > 0)
            Serial.println(" deg to the left");
        else
            Serial.println(" deg to the right");
    }
	// Approach functions
	void approachNoFollowUntilPerpendicularLine() { Serial.println("Not following line until perpendicular line is hit"); };
	void approachFollowUntilPerpendicularLine();
	void approachFollowUntilTokenSlot() { Serial.println("Following line until token slot is hit"); };
	void approachFollowOnLeftUntilPerpendicularLine() { Serial.println("Following line on its left until perpendicular line is hit on the left"); };
	void approachFollowOnRightUntilPerpendicularLine() { Serial.println("Following line on its right until perpendicular line is hit on the right"); };
	void approachFollowOnLeftUntilCrossesLine() { Serial.println("Following line on its left until some line is hit on the left"); };
	void approachFollowOnRightUntilCrossesLine() { Serial.println("Following line on its right until some line is hit on the left"); };
	void approachFollowUntilCrossingY() { Serial.println("Following line until two lines of Y start to cross"); };
	void approachFollowUntilSeparatingY() { Serial.println("Following line until two liens of Y start to separate"); };
	void approachMoveIntoStart() { Serial.println("Go forward some amount to be in center of start square"); };
	void approachMoveIntoDropPosition() { Serial.println("Go forward some amount to be in center of start square"); };
	// Backward Approach functions
	void approachBackwardLeaveDropPosition() { Serial.println("Go backward some amount to leave drop position"); };
	void approachBackwardFollowUntilCrossingY() { Serial.println("Go backward until two lines of Y start to cross"); };
	void approachBackwardFollowUntilSeparatingY() { Serial.println("Go backward until two lines of Y start to separate"); };
	void approachBackwardFollowUntilPerpendicularLine() { Serial.println("Go backward until perpendicular line is hit"); };
};



class MovementMock
{
public:
	MovementMock();
	~MovementMock();
	void performTurn(Turn turnType);
	void performApproach(Approach approachType);
	void performBackwardApproach(BackwardApproach approachType);
	// Turn methods
    // TODO: stop using these, make them private if we really need them (I doubt we need them), use the parameter one
	void turnLeft45() { Serial.println("Turning 45 deg to the left"); };
	void turnRight45() { Serial.println("Turning 45 deg to the right"); };
	void turnLeft90() { Serial.println("Turning 90 deg to the left"); };
	void turnRight90() { Serial.println("Turning 90 deg to the right"); };
	void turnLeft135() { Serial.println("Turning 135 deg to the left"); };
	void turnRight135() { Serial.println("Turning 135 deg to the right"); };
	void turnLeft180() { Serial.println("Turning 180 deg to the left"); };
	void turnRight180() { Serial.println("Turning 180 deg to the right"); };
    // use this
    /** negative for right **/
	void turn(const int& degreesLeft) {
        Serial.print("Turning ");
        Serial.print(abs(degreesLeft));
        if (degreesLeft > 0)
            Serial.println(" deg to the left");
        else
            Serial.println(" deg to the right");
    }
	// Approach functions
	void approachNoFollowUntilPerpendicularLine() { Serial.println("Not following line until perpendicular line is hit"); };
	void approachFollowUntilPerpendicularLine() { Serial.println("Following line until perpendicular line is hit"); };
	void approachFollowUntilTokenSlot() { Serial.println("Following line until token slot is hit"); };
	void approachFollowOnLeftUntilPerpendicularLine() { Serial.println("Following line on its left until perpendicular line is hit on the left"); };
	void approachFollowOnRightUntilPerpendicularLine() { Serial.println("Following line on its right until perpendicular line is hit on the right"); };
	void approachFollowOnLeftUntilCrossesLine() { Serial.println("Following line on its left until some line is hit on the left"); };
	void approachFollowOnRightUntilCrossesLine() { Serial.println("Following line on its right until some line is hit on the left"); };
	void approachFollowUntilCrossingY() { Serial.println("Following line until two lines of Y start to cross"); };
	void approachFollowUntilSeparatingY() { Serial.println("Following line until two liens of Y start to separate"); };
	void approachMoveIntoStart() { Serial.println("Go forward some amount to be in center of start square"); };
	void approachMoveIntoDropPosition() { Serial.println("Go forward some amount to be in center of start square"); };
	// Backward Approach functions
	void approachBackwardLeaveDropPosition() { Serial.println("Go backward some amount to leave drop position"); };
	void approachBackwardFollowUntilCrossingY() { Serial.println("Go backward until two lines of Y start to cross"); };
	void approachBackwardFollowUntilSeparatingY() { Serial.println("Go backward until two lines of Y start to separate"); };
	void approachBackwardFollowUntilPerpendicularLine() { Serial.println("Go backward until perpendicular line is hit"); };
};


#endif
