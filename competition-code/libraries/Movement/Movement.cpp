#include "Movement.h"


Movement::Movement()
{
}

Movement::Movement(ScrapDualController& dualController, LineIntersection* lineIntersection) {
	attachController(dualController);
	attachLineIntersection(lineIntersection);
}

Movement::~Movement()
{
}

void Movement::performTurn(Turn turnType) {
	switch (turnType) {
	case Left45:
		turnLeft45();
		break;
	case Right45:
		turnRight45();
		break;
	case Left90:
		turnLeft90();
		break;
	case Right90:
		turnRight90();
		break;
	case Left135:
		turnLeft135();
		break;
	case Right135:
		turnRight135();
		break;
	case Left180:
		turnLeft180();
		break;
	case Right180:
		turnRight180();
		break;
	default:
		Serial.println("Turn type does not exist");
		break;
	}

}


void Movement::performApproach(Approach approachType) {
	switch (approachType) {
	case NoFollowUntilPerpendicularLine:
		approachNoFollowUntilPerpendicularLine();
		break;
	case FollowUntilPerpendicularLine:
		approachFollowUntilPerpendicularLine();
		break;
	case FollowUntilTokenSlot:
		approachFollowUntilTokenSlot();
		break;
	case FollowOnLeftUntilPerpendicularLine:
		approachFollowOnLeftUntilPerpendicularLine();
		break;
	case FollowOnRightUntilPerpendicularLine:
		approachFollowOnRightUntilPerpendicularLine();
		break;
	case FollowOnLeftUntilCrossesLine:
		approachFollowOnLeftUntilCrossesLine();
		break;
	case FollowOnRightUntilCrossesLine:
		approachFollowOnRightUntilCrossesLine();
		break;
	case FollowUntilCrossingY:
		approachFollowUntilCrossingY();
		break;
	case FollowUntilSeparatingY:
		approachFollowUntilSeparatingY();
		break;
	case MoveIntoStart:
		approachMoveIntoStart();
		break;
	case MoveIntoDropPosition:
		approachMoveIntoDropPosition();
		break;
	default:
		Serial.println("Approach type does not exist");
		break;
	}
}


void Movement::performBackwardApproach(BackwardApproach approachType) {
	switch (approachType) {
	case BackwardLeaveDropPosition:
		approachBackwardLeaveDropPosition();
		break;
	case BackwardFollowUntilCrossingY:
		approachBackwardFollowUntilCrossingY();
		break;
	case BackwardFollowUntilSeparatingY:
		approachBackwardFollowUntilSeparatingY();
		break;
	case BackwardFollowUntilPerpendicularLine:
		approachBackwardFollowUntilPerpendicularLine();
		break;
	default:
		Serial.println("Backward approach type does not exist");
		break;
	}
}

void Movement::turnTillEncoderValue(long encoderCount) {
	// set appropriate goals
	controller->set(-encoderCount,encoderCount);
	// perform movement until goal is reached
	while (!controller->performMovement()) {
		delay(2);
	}
	// stop the motors
	controller->stop();
	// shift the encoder counts so they are relative to goal
	controller->shiftCount();
}

// TURNING COMMANDS
void Movement::turnLeft45() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight45() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnLeft90() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight90() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnLeft135() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight135() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnLeft180() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight180() {
	long encoderCount = 0;
	turnTillEncoderValue(encoderCount);
}

// FORWARD APPROACH COMMANDS
void Movement::approachNoFollowUntilPerpendicularLine() {
	// Go forward some amount until a perpendicular line is reached
	controller->set(2550);
	while(!controller->performMovement() || !line->getIfAtPerpendicular()) {
		delay(2);
	}
	controller->stop();
	controller->shiftCount();
	// TO-DO: maybe line up robot with line
}

void Movement::approachFollowUntilPerpendicularLine() {
	// Go forward while following line, until perpendicular line is reached
}



// BACKWARD APPROACH COMMANDS
