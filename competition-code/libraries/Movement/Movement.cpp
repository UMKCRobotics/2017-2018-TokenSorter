#include "Movement.h"


Movement::Movement()
{
}

Movement::Movement(ScrapDualController& dualController, LineIntersection* lineIntersection, Buttons& bothButtons) {
	attachController(dualController);
	attachLineIntersection(lineIntersection);
	attachButtons(bothButtons);
}

Movement::~Movement()
{
}


void Movement::stopUntilReboot() {
	controller->stop();
	while(true) {
		delay(1000);
	} 
}

void Movement::stopIfPressed() {
	if (buttons->wasStopPressed()) {
		stopUntilReboot();
	}
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


void Movement::turnTillEncoderValue(long encoderCountL, long encoderCountR) {
	// set appropriate goals
	controller->set(encoderCountL,encoderCountR);
	// perform movement until goal is reached
	while (!controller->performMovement()) {
		stopIfPressed();	
		delay(2);
	}
	// stop the motors
	controller->stop();
	// shift the encoder counts so they are relative to goal
	controller->shiftCount();
}


void Movement::turnTillEncoderValue(long encoderCount) {
	// set appropriate goals
	controller->set(-encoderCount,encoderCount);
	// perform movement until goal is reached
	while (!controller->performMovement()) {
		stopIfPressed();	
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
	long encoderCount = 2600;
	turnTillEncoderValue(800,800);
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight90() {
	long encoderCount = -2600;
	turnTillEncoderValue(800,800);
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


void Movement::followLine() {
	int position = line->getLinePosition(true);
	float defaultSpeed = 1100;
	//float maxOffset = 800;
	float offset = 0;
	
	offset = pid.calculate(position);

	Serial.println(offset);
	// set motor speeds
	controller->setSpeed1(defaultSpeed+offset);
	controller->setSpeed2(defaultSpeed-offset);
}


// FORWARD APPROACH COMMANDS
void Movement::approachNoFollowUntilPerpendicularLine() {
	// Go forward some amount until a perpendicular line is reached
	bool onLine = line->getIfAtPerpendicular();
	controller->set(2550);
	unsigned long time = millis();
	while(!controller->performMovement()) {
		stopIfPressed();
		if (onLine) {
			if (!line->getIfAtPerpendicular()) {
				onLine = false;
			}
		}
		else if (line->getIfAtPerpendicular()) {
			break;
		}
		if (millis()-time > 30) {
			line->read();
			time = millis();
		}
		delay(2);
	}
	controller->stop();
	controller->set(controller->getCount());
	controller->shiftCount();
	// TO-DO: maybe line up robot with line
}

void Movement::approachFollowUntilPerpendicularLine() {
	// Go forward while following line, until perpendicular line is reached
	bool onLine = line->getIfAtPerpendicular();
	Serial.println(onLine);
	pid.reset();
	followLine();
	unsigned long time = millis();
	while(!line->getIfAtPerpendicular()) {
		stopIfPressed();
		if (onLine) {
			if (!line->getIfAtPerpendicular()) {
				onLine = false;
			}
		}
		if (millis()-time > 30) {
			followLine();
			time = millis();
		}
		controller->performSpeedMovement();
		delay(2);
	}
	controller->stop();
	controller->set(0,0);
	controller->resetCount();
}

void Movement::lineUpForToken() {
	turnTillEncoderValue(650,650);	
}



// BACKWARD APPROACH COMMANDS
