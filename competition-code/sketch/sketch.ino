#include "ScrapController.h"
#include "LineIntersection.h"
#include "Navigation.h"
#include "Movement.h"
#include "Servo.h"
#include "Arm.h"
#include "ColorSensor.h"
#include "RoundSwitch.h"
#include "Gameboard.h"
#include "Buttons.h"


// define necessary constants here (pins)

// SENSOR CONSTANTS
#define MIDDLE_IR_PIN A6
// ARM CONSTANTS
#define EM_RELAY 32//21
#define ARM_LINEAR 23
#define ARM_SERVO 22
// MOTOR CONSTANTS
#define PWM_LEFT 10
#define PWM_RIGHT 9
#define DIR_LEFT 12
#define DIR_RIGHT 11
// ENCODER CONSTANTS
#define ENC_INT_LEFT 4
#define ENC_INT_RIGHT 2
#define ENC_CHECK_LEFT 5 
#define ENC_CHECK_RIGHT 3 
// BUTTON PINS
#define GO_PIN 27
#define STOP_PIN 26

// define Scrap components here (motors, encoders, motor speed controls, etc)
//ScrapMotorSinglePin leftMotor = ScrapMotorSinglePin(DIR_LEFT,PWM_LEFT);
//ScrapMotorSinglePin rightMotor = ScrapMotorSinglePin(DIR_RIGHT,PWM_RIGHT);

ScrapEncoder leftEncoder = ScrapEncoder(ENC_INT_LEFT,ENC_CHECK_LEFT);
ScrapEncoder rightEncoder = ScrapEncoder(ENC_INT_RIGHT,ENC_CHECK_RIGHT);
// define Movement component
ScrapMotorSinglePin leftMotor = ScrapMotorSinglePin(DIR_LEFT,PWM_LEFT);
ScrapMotorSinglePin rightMotor = ScrapMotorSinglePin(DIR_RIGHT,PWM_RIGHT,-1);

ScrapMotorControl leftMotorControl = ScrapMotorControl(leftMotor,leftEncoder);
ScrapMotorControl rightMotorControl = ScrapMotorControl(rightMotor,rightEncoder);
ScrapDualController dualController = ScrapDualController(leftMotorControl,rightMotorControl);

// BUTTONS
Buttons buttons = Buttons(GO_PIN,STOP_PIN);
// SWITCHES
RoundSwitch roundSwitch = RoundSwitch();

ColorSensor colorInside = ColorSensor();
ColorSensor colorBottom = ColorSensor();


// SLOWEST = 180
// FASTEST = 2200
LineIntersection* line;

Movement* movement;
Navigation* navigation;
Arm arm = Arm(ARM_LINEAR,ARM_SERVO,EM_RELAY);


void setup() {
	// Start serial for debugging purposes
	colorInside.initSensor(0);
	colorBottom.initSensor(1);
	initEncoders();
	initButtons();
	//initializePins();
	Serial.begin(9600);
	Serial.println("serial started");
	line = new LineIntersection(MIDDLE_IR_PIN);
	movement = new Movement(dualController,line,buttons);
	navigation = new Navigation(roundSwitch.getRound(),movement);
	//arm = new Arm(ARM_LINEAR,ARM_SERVO,EM_RELAY);
	//linear.attach(ARM_LINEAR);
	//servo.attach(ARM_SERVO);
	//linear.write(0);
	//linear.write(40);
	//servo.write(180);
	//digitalWrite(EM_RELAY,HIGH);
	//leftMotorControl.setControl(0);
	//rightMotorControl.setControl(0);
	//leftMotor.setMotor(30);
	//rightMotor.setMotor(30);
	// CONFIGURE DUAL CONTROLLER
	dualController.setDiffTolerance(5);
	dualController.setEncTolerance(5);
	dualController.setSlowdownThresh(500);
	dualController.setMinSlowPower(40);
	dualController.setMinEncSpeed(180);
	dualController.setMaxEncSpeed(1700);
	dualController.setSpeedBalance(30);
	dualController.initControllers();
	while(!buttons.wasGoPressed()) {
		delay(50);
	}

	/*while(true) {
		delay(100);
		Serial.println(colorBottom.getColor());
	}*/

	//movement->approachFollowUntilPerpendicularLine();
	
	//navigation->goForward();
	//navigation->goForward();
	//navigation->turnLeft();
	//navigation->goForward();
	
	//IMPORTANT
	/*movement->approachFollowUntilPerpendicularLine();
	navigation->lineUpForToken();
	arm.moveArmToPosition(armOptions::Hole);
	arm.moveArmDown();
	arm.setEmOn();
	arm.moveArmUp();
	arm.moveArmToPosition(armOptions::Sensor);
	arm.moveArmDown();
	delay(200);
	int color = colorInside.getColor();
	arm.moveArmUp();
	if (color == 0) {
		arm.moveArmToPosition(armOptions::Hole);
		arm.setEmOff();		
	}
	else {
		arm.moveArmToPosition(color);
		arm.setEmOff();
		delay(300);
		arm.moveArmToPosition(armOptions::Hole);
		arm.moveArmToPosition(color);
		arm.moveArmDown();
		arm.setEmOn();
		delay(400);
		arm.moveArmUp();
		arm.moveArmToPosition(armOptions::Hole);
		arm.setEmOff();
	}*/

	//if (roundSwitch.getRound() == 1) {
	navigation->goForward();
	navigation->goForward();
	navigation->goForward();
	movement->positionForTurning();
	navigation->turnLeft();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnRight();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnRight();
	navigation->turnRight();
	navigation->goForward();
	navigation->goForward();
	//movement->approachFollowUntilSeparatingY();
	movement->lineUpForTokenSeparatingY();
	pickUpToken();
	movement->reverseLineUpForTokenSeparatingY();
	//movement->positionForTurning();
	navigation->turnRight();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnLeft();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnLeft();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnRight();
	navigation->goForward();
	navigation->goForward();
	movement->lineUpForTokenCrossingY();
	pickUpToken();
	navigation->turnRight();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->goForward();
	navigation->lineUpForToken();
	pickUpToken();
	navigation->turnLeft();
	navigation->goForward();
	// DEPOSITING TOKENS
	movement->approachFollowUntilSeparatingY();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilSeparatingY();
	movement->lineUpForTokenSeparatingY(); // go forward a bit
	movement->turnLeft135();
	movement->approachFollowUntilPerpendicularLine();
	movement->positionForTurning();
	movement->turnRight90();
	movement->approachFollowUntilPerpendicularLine();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilPerpendicularLine();
	movement->positionForTurning();
	movement->turnLeft90();
	movement->approachFollowUntilPerpendicularLine();
	movement->lineUpForTokenSeparatingY(); // go forward a bit
	movement->turnRight45();
	movement->approachFollowUntilSeparatingY();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilSeparatingY();
	movement->positionForTurning();
	movement->turnLeft135();
	movement->approachFollowUntil5ftHalfway();
	movement->approachFollowUntilPerpendicularLine();
	movement->lineUpForTokenSeparatingY(); // go forward a bit
	movement->turnRight45();
	// copy paste
	movement->approachFollowUntilSeparatingY();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilSeparatingY();
	movement->positionForTurning(); // go forward a bit
	movement->turnLeft135();
	movement->approachFollowUntilPerpendicularLine();
	movement->positionForTurning();
	movement->turnRight90();
	movement->approachFollowUntilPerpendicularLine();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilPerpendicularLine();
	movement->positionForTurning();
	movement->turnLeft90();
	movement->approachFollowUntilPerpendicularLine();
	movement->lineUpForTokenSeparatingY(); // go forward a bit
	movement->turnRight45();
	movement->approachFollowUntilSeparatingY();
	movement->approachMoveIntoDropPosition();
	depositToken();
	depositToken();
	depositGray();
	depositGray();
	depositGray();
	movement->approachBackwardLeaveDropPosition();
	movement->approachBackwardFollowUntilSeparatingY();
	movement->positionForTurning();
	movement->turnLeft135();
	movement->approachFollowUntil5ftHalfway();
	movement->turnRight90();
	movement->approachFollowUntilPerpendicularLine();
	movement->approachMoveIntoDropPosition();







	/*arm.moveArmUp();
	arm.moveArmToPosition(armOptions::Red);
	arm.setEmOff();
	delay(300);
	arm.moveArmToPosition(armOptions::Hole);*/
	
	//arm.moveArmDown();
	//arm.setEmOn();
	//arm.moveArmUp();
	//delay(1000);
	/*arm.moveArmToPosition(armOptions::Sensor);
	arm.moveArmToPosition(armOptions::Yellow);
	arm.moveArmDown();
	arm.setEmOn();
	delay(250);
	arm.moveArmUp();*/
	/*arm.moveArmToPosition(armOptions::Green);
	arm.moveArmToPosition(armOptions::Blue);
	arm.moveArmToPosition(armOptions::Yellow);
	arm.moveArmToPosition(armOptions::Magenta);
	arm.moveArmToPosition(armOptions::Cyan);
	arm.moveArmToPosition(armOptions::Gray);*/
	/*arm.moveArmToPosition(armOptions::Hole);
	arm.setEmOff();
	//delay(1000);
	//linear.write(125);
	//delay(3000);
	//digitalWrite(EM_RELAY,LOW);
	//linear.write(40);
	//delay(2000);
	//digitalWrite(EM_RELAY,HIGH);
	

	buttons.resetGo();
	while (!buttons.wasGoPressed()) {
		//Serial.println(colorInside.getColor());
		delay(50);
	}

	movement->approachFollowUntilPerpendicularLine();
	//movement->approachNoFollowUntilPerpendicularLine();
	//movement->turnLeft90();
	//dualController.set(2500,2500);*/
	
	/*for(int i = 0; i < roundSwitch.getRound(); i++) {
		digitalWrite(EM_RELAY,LOW);
		delay(50);
		digitalWrite(EM_RELAY,HIGH);
		delay(250);
	}*/

	/*

	navigation->goForward();
	navigation->goForward();
	navigation->goForward();
	navigation->turnLeft();
	*/

	/*delay(1000);
	navigation->goForward();
	delay(1000);
	navigation->goForward();*/
}

void pickUpToken() {
	arm.moveArmToPosition(armOptions::Hole);
	arm.moveArmDown();
	arm.setEmOn();
	arm.moveArmUp();
	arm.moveArmToPosition(armOptions::Sensor);
	arm.moveArmDown();
	delay(200);
	int color = colorInside.getColor();
	arm.moveArmUp();
	//if (color == 0) {
	//	arm.moveArmToPosition(armOptions::Hole);
	//	arm.setEmOff();		
	//}
	//else {
	arm.moveArmToPosition(color);
	arm.setEmOff();
	delay(300);
	arm.moveArmToPosition(armOptions::Hole);
	//arm.moveArmToPosition(color);
	//arm.moveArmDown();
	//arm.setEmOn();
	//delay(400);
	//arm.moveArmUp();
	//arm.moveArmToPosition(armOptions::Hole);
	//arm.setEmOff();
}

void depositToken() {
	int color = colorBottom.getColor();
	arm.moveArmToPosition(color);
	arm.moveArmDown();
	arm.setEmOn();
	arm.moveArmUp();
	arm.moveArmToPosition(armOptions::Hole);
	arm.setEmOff();
}

void depositGray() {
	//int color = colorBottom.getColor();
	arm.moveArmToPosition(armOptions::Gray);
	arm.moveArmDown();
	arm.setEmOn();
	arm.moveArmUp();
	arm.moveArmToPosition(armOptions::Hole);
	arm.setEmOff();
}

void initializePins() {
	pinMode(EM_RELAY,OUTPUT);
}


void loop() {	
	delay(2);
	dualController.performMovement();

	//Serial.println(line->getLinePosition(true));
	//delay(100);

	//counter++;
	//if (dualController.performMovement()) {
	//	delay(1000);
	//}	
	//if (dualController.performMovement()) {
	//	
	//}
	//else {
	//	if (counter >= 51) {
	//		counter = 0;
	//		Serial.print(dualController.getDiff1());
	//		Serial.print("\t");
	//		Serial.println(dualController.getDiff2());
	//	}
	//}
	//leftMotorControl.performMovement();
	//rightMotorControl.performMovement();
	/*Serial.print(line->getMiddleState());
	Serial.print("\t");
	Serial.print(line->getFullArrayInString());
	Serial.print("\t");
	Serial.print(line->getDensity());
	Serial.print("\t");
	Serial.print(line->getLinePosition());
	Serial.print("\t");
	Serial.println(line->getIfAtCrossingY());*/
}

void initEncoders() {
	attachInterrupt(digitalPinToInterrupt(ENC_INT_LEFT),checkEncoderL,CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENC_INT_RIGHT),checkEncoderR,CHANGE);
}

void checkEncoderL() {
	leftEncoder.checkEncoderFlipped();
}

void checkEncoderR() {
	rightEncoder.checkEncoder();
}

void initButtons() {
	attachInterrupt(digitalPinToInterrupt(GO_PIN),goButtonFunction,CHANGE);
	attachInterrupt(digitalPinToInterrupt(STOP_PIN),stopButtonFunction,CHANGE);
}

void goButtonFunction() {
	buttons.checkGoButton();
}

void stopButtonFunction() {
	buttons.checkStopButton();
}

