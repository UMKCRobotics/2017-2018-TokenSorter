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
#define EM_RELAY 21
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

// SLOWEST = 180
// FASTEST = 2200
LineIntersection* line;

Movement* movement;
Navigation* navigation;

Servo linear;
Servo servo;

String firstReading;

void setup() {
	// Start serial for debugging purposes
	initEncoders();
	initButtons();
	initializePins();
	Serial.begin(9600);
	Serial.println("serial started");
	line = new LineIntersection(MIDDLE_IR_PIN);
	movement = new Movement(dualController,line);
	navigation = new Navigation(3,movement);
	linear.attach(ARM_LINEAR);
	servo.attach(ARM_SERVO);
	linear.write(40);
	//linear.write(120);
	servo.write(180);
	digitalWrite(EM_RELAY,HIGH);
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
	dualController.setMaxEncSpeed(1100);
	dualController.setSpeedBalance(30);
	dualController.initControllers();
	delay(1000);
	//movement->approachNoFollowUntilPerpendicularLine();
	//movement->turnLeft90();
	//dualController.set(2500,2500);
	for(int i = 0; i < roundSwitch.getRound(); i++) {
		digitalWrite(EM_RELAY,LOW);
		delay(50);
		digitalWrite(EM_RELAY,HIGH);
		delay(250);
	}

	while (!buttons.wasGoPressed()) {
		delay(50);
	}
	navigation->goForward();
	navigation->goForward();
	navigation->goForward();
	/*delay(1000);
	navigation->goForward();
	delay(1000);
	navigation->goForward();*/
}


void initializePins() {
	pinMode(EM_RELAY,OUTPUT);
}


void loop() {	
	delay(2);
	dualController.performMovement();
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

