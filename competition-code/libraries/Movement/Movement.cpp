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
	case FollowUntil5ftHalfway:
		approachFollowUntil5ftHalfway();
		break;
	case FollowUntil4ftHalfway:
		approachFollowUntil4ftHalfway();
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


void Movement::positionForTurning() {
	turnTillEncoderValue(800,800);
}


// TURNING COMMANDS
void Movement::turnLeft45() {
	long encoderCount = 1300;
	turnTillEncoderValue(encoderCount);
	turnTillEncoderValue(500,500);
}

void Movement::turnRight45() {
	long encoderCount = -1300;
	turnTillEncoderValue(encoderCount);
	turnTillEncoderValue(500,500);
}

void Movement::turnLeft90() {
	long encoderCount = 2600;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight90() {
	long encoderCount = -2600;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnLeft135() {
	long encoderCount = 3700;
	turnTillEncoderValue(encoderCount);
	turnTillEncoderValue(700,700);
}

void Movement::turnRight135() {
	long encoderCount = -3700;
	turnTillEncoderValue(encoderCount);
	turnTillEncoderValue(700,700);
}

void Movement::turnLeft180() {
	long encoderCount = 5200;
	turnTillEncoderValue(encoderCount);
}

void Movement::turnRight180() {
	long encoderCount = -5200;
	turnTillEncoderValue(encoderCount);
}


void Movement::followLine() {
	int position = line->getLinePosition(true);
	float defaultSpeed = 1600;
	//float maxOffset = 800;
	float offset = 0;
	
	offset = pid.calculate(position);

	Serial.println(offset);
	// set motor speeds
	controller->setSpeed1(defaultSpeed+offset);
	controller->setSpeed2(defaultSpeed-offset);
}


void Movement::followLineBackwards() {
	int position = line->getLinePosition(true);
	float defaultSpeed = -1600;
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

void Movement::approachFollowUntilSeparatingY() {
	bool onLine = line->getIfAtSeparatingY();
	Serial.println(onLine);
	pid.reset();
	followLine();
	unsigned long time = millis();
	while (controller->getCount() < 400) {
		stopIfPressed();
		if (millis()-time > 30) {
			followLine();
			time = millis();
		}
		controller->performSpeedMovement();
		delay(2);
	}
	while(!line->getIfAtSeparatingY()) {
		stopIfPressed();
		if (onLine) {
			if (!line->getIfAtSeparatingY()) {
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

void Movement::approachFollowUntilCrossingY() {
	bool onLine = line->getIfAtCrossingY();
	Serial.println(onLine);
	pid.reset();
	followLine();
	unsigned long time = millis();
	while (controller->getCount() < 500) {
		stopIfPressed();
		if (millis()-time > 30) {
			followLine();
			time = millis();
		}
		controller->performSpeedMovement();
		delay(2);
	}
	while(!line->getIfAtCrossingY()) {
		stopIfPressed();
		if (onLine) {
			if (!line->getIfAtCrossingY()) {
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

void Movement::approachMoveIntoDropPosition() {
	turnTillEncoderValue(2000,2000);
}

void Movement::approachFollowUntil5ftHalfway() {
	//bool onLine = line->getIfAtPerpendicular();
	pid.reset();
	followLine();
	unsigned long time = millis();
	while(controller->getCount() <= 9000) {
		stopIfPressed();
		/*if (onLine) {
			if (!line->getIfAtPerpendicular()) {
				onLine = false;
			}
		}*/
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

void Movement::approachFollowUntil4ftHalfway() {
	pid.reset();
	followLine();
	unsigned long time = millis();
	while(controller->getCount() <= 6000) {
		stopIfPressed();
		/*if (onLine) {
			if (!line->getIfAtPerpendicular()) {
				onLine = false;
			}
		}*/
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

void Movement::lineUpForTokenSeparatingY() {
	turnTillEncoderValue(450,450);
}

void Movement::lineUpForTokenCrossingY() {
	turnTillEncoderValue(1100,1100);
}

void Movement::reverseLineUpForToken() {
	turnTillEncoderValue(-650,-650);
}

void Movement::reverseLineUpForTokenSeparatingY() {
	turnTillEncoderValue(-450,-450);
}

void Movement::reverseLineUpForTokenCrossingY() {
	turnTillEncoderValue(-1100,-1100);
}



// BACKWARD APPROACH COMMANDS
void Movement::approachBackwardLeaveDropPosition() {
	turnTillEncoderValue(-2200,-2200);
}

void Movement::approachBackwardFollowUntilSeparatingY() {
	/*bool onLine = line->getIfAtSeparatingY();
	Serial.println(onLine);
	pid.reset();
	followLineBackwards();
	unsigned long time = millis();
	while (controller->getCount() > -400) {
		stopIfPressed();
		if (millis()-time > 30) {
			followLineBackwards();
			time = millis();
		}
		controller->performSpeedMovement();
		delay(2);
	}
	while(!line->getIfAtSeparatingY()) {
		stopIfPressed();
		if (onLine) {
			if (!line->getIfAtSeparatingY()) {
				onLine = false;
			}
		}
		if (millis()-time > 30) {
			followLineBackwards();
			time = millis();
		}
		controller->performSpeedMovement();
		delay(2);
	}
	controller->stop();
	controller->set(0,0);
	controller->resetCount();*/
	turnTillEncoderValue(-3000,-3000);
}

void Movement::approachBackwardFollowUntilPerpendicularLine() {
	turnTillEncoderValue(-2300,-2300);
}

