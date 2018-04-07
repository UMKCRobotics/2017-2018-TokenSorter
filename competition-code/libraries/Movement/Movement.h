#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Arduino.h"
#include "ScrapController.h"
#include "LineIntersection.h"
#include "Buttons.h"
#include "PID.h"

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
private:
	ScrapDualController* controller;
	LineIntersection* line;
	Buttons* buttons;
	PID pid = PID(50,2,0.5);
	// Freeze robot until reboot
	void stopUntilReboot();
	void stopIfPressed();
public:
	Movement();
	Movement(ScrapDualController& dualController, LineIntersection* lineIntersection, Buttons& bothButtons);
	~Movement();
	virtual void performTurn(Turn turnType);
	virtual void performApproach(Approach approachType);
	virtual void performBackwardApproach(BackwardApproach approachType);
	// Attach components
	virtual void attachController(ScrapDualController& dualController) { controller = &dualController; };
	virtual void attachLineIntersection(LineIntersection* lineIntersection) { line = lineIntersection; };
	virtual void attachButtons(Buttons& bothButtons) { buttons = &bothButtons; };
	// Turn methods
    // TODO: stop using these, make them private if we really need them (I doubt we need them), use the parameter one
	virtual void turnLeft45();
	virtual void turnRight45();
	virtual void turnLeft90();
	virtual void turnRight90();
	virtual void turnLeft135();
	virtual void turnRight135();
	virtual void turnLeft180();
	virtual void turnRight180();
	// Turning helper function
	void turnTillEncoderValue(long encoderCount);
	void turnTillEncoderValue(long encoderCountL, long encoderCountR);
    // use this
    /** negative for right **/
	virtual void turn(const int& degreesLeft) {
        Serial.print("Turning ");
        Serial.print(abs(degreesLeft));
        if (degreesLeft > 0)
            Serial.println(" deg to the left");
        else
            Serial.println(" deg to the right");
    }
    virtual void followLine();
	// Approach functions
	virtual void approachNoFollowUntilPerpendicularLine();
	virtual void approachFollowUntilPerpendicularLine();
	virtual void approachFollowUntilTokenSlot() {};
	virtual void approachFollowOnLeftUntilPerpendicularLine(){};
	virtual void approachFollowOnRightUntilPerpendicularLine(){};
	virtual void approachFollowOnLeftUntilCrossesLine(){};
	virtual void approachFollowOnRightUntilCrossesLine(){};
	virtual void approachFollowUntilCrossingY(){};
	virtual void approachFollowUntilSeparatingY(){};
	virtual void approachMoveIntoStart(){};
	virtual void approachMoveIntoDropPosition(){};
	// Backward Approach functions
	virtual void approachBackwardLeaveDropPosition(){};
	virtual void approachBackwardFollowUntilCrossingY(){};
	virtual void approachBackwardFollowUntilSeparatingY(){};
	virtual void approachBackwardFollowUntilPerpendicularLine(){};
	// Lining Up Functions
	virtual void lineUpForToken();
};



class MovementMock : Movement
{
public:
	MovementMock();
	~MovementMock();
	//void performTurn(Turn turnType);
	//void performApproach(Approach approachType);
	//void performBackwardApproach(BackwardApproach approachType);
	// Turn methods
    // TODO: stop using these, make them private if we really need them (I doubt we need them), use the parameter one
	virtual void turnLeft45() { Serial.println("Turning 45 deg to the left"); };
	virtual void turnRight45() { Serial.println("Turning 45 deg to the right"); };
	virtual void turnLeft90() { Serial.println("Turning 90 deg to the left"); };
	virtual void turnRight90() { Serial.println("Turning 90 deg to the right"); };
	virtual void turnLeft135() { Serial.println("Turning 135 deg to the left"); };
	virtual void turnRight135() { Serial.println("Turning 135 deg to the right"); };
	virtual void turnLeft180() { Serial.println("Turning 180 deg to the left"); };
	virtual void turnRight180() { Serial.println("Turning 180 deg to the right"); };
    // use this
    /** negative for right **/
	virtual void turn(const int& degreesLeft) {
        Serial.print("Turning ");
        Serial.print(abs(degreesLeft));
        if (degreesLeft > 0)
            Serial.println(" deg to the left");
        else
            Serial.println(" deg to the right");
    }
	// Approach functions
	virtual void approachNoFollowUntilPerpendicularLine() { Serial.println("Not following line until perpendicular line is hit"); };
	virtual void approachFollowUntilPerpendicularLine() { Serial.println("Following line until perpendicular line is hit"); };
	virtual void approachFollowUntilTokenSlot() { Serial.println("Following line until token slot is hit"); };
	virtual void approachFollowOnLeftUntilPerpendicularLine() { Serial.println("Following line on its left until perpendicular line is hit on the left"); };
	virtual void approachFollowOnRightUntilPerpendicularLine() { Serial.println("Following line on its right until perpendicular line is hit on the right"); };
	virtual void approachFollowOnLeftUntilCrossesLine() { Serial.println("Following line on its left until some line is hit on the left"); };
	virtual void approachFollowOnRightUntilCrossesLine() { Serial.println("Following line on its right until some line is hit on the left"); };
	virtual void approachFollowUntilCrossingY() { Serial.println("Following line until two lines of Y start to cross"); };
	virtual void approachFollowUntilSeparatingY() { Serial.println("Following line until two liens of Y start to separate"); };
	virtual void approachMoveIntoStart() { Serial.println("Go forward some amount to be in center of start square"); };
	virtual void approachMoveIntoDropPosition() { Serial.println("Go forward some amount to be in center of start square"); };
	// Backward Approach functions
	virtual void approachBackwardLeaveDropPosition() { Serial.println("Go backward some amount to leave drop position"); };
	virtual void approachBackwardFollowUntilCrossingY() { Serial.println("Go backward until two lines of Y start to cross"); };
	virtual void approachBackwardFollowUntilSeparatingY() { Serial.println("Go backward until two lines of Y start to separate"); };
	virtual void approachBackwardFollowUntilPerpendicularLine() { Serial.println("Go backward until perpendicular line is hit"); };
};


#endif
