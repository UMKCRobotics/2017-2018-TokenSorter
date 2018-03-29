#include "ScrapController.h"
#include "LineIntersection.h"
//#include "TunnelRobot.h"
//#include "Navigation.h"
#include "Movement.h"
//#include "ColorSensor.h"
//#include "RoundSwitch.h"
//#include "GoStopButtons.h"


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

// define Scrap components here (motors, encoders, motor speed controls, etc)
//ScrapMotorSinglePin leftMotor = ScrapMotorSinglePin(DIR_LEFT,PWM_LEFT);
//ScrapMotorSinglePin rightMotor = ScrapMotorSinglePin(DIR_RIGHT,PWM_RIGHT);

ScrapEncoder leftEncoder = ScrapEncoder(ENC_INT_LEFT,ENC_CHECK_LEFT);
ScrapEncoder rightEncoder = ScrapEncoder(ENC_INT_RIGHT,ENC_CHECK_RIGHT);
// define Movement component
ScrapMotorSinglePin leftMotor = ScrapMotorSinglePin(DIR_LEFT,PWM_LEFT);
ScrapMotorSinglePin rightMotor = ScrapMotorSinglePin(DIR_RIGHT,PWM_RIGHT);
// define Navigation component


// define TunnelRobot here


LineIntersection* line;



void setup() {
	// Start serial for debugging purposes
	Serial.begin(9600);
	Serial.println("serial started");
	line = new LineIntersection(MIDDLE_IR_PIN);
	//leftMotor.stop();
	//rightMotor.stop();
	pinMode(DIR_LEFT,OUTPUT);
	pinMode(DIR_RIGHT,OUTPUT);
	pinMode(PWM_LEFT,OUTPUT);
	pinMode(PWM_RIGHT,OUTPUT);
	leftMotor.setMotor(255);
	rightMotor.setMotor(255);
	delay(1000);
	leftMotor.stop();
	rightMotor.stop();
	//digitalWrite(DIR_LEFT,HIGH);
	//digitalWrite(DIR_RIGHT,LOW);
	//digitalWrite(PWM_LEFT,HIGH);
	//digitalWrite(PWM_RIGHT,HIGH);
}


void initializePins() {
	pinMode(EM_RELAY,OUTPUT);
	pinMode(ARM_LINEAR,OUTPUT);
	pinMode(ARM_SERVO,OUTPUT);
}


void loop() {
	delay(200);
	Serial.print(line->getMiddleState());
	Serial.print("\t");
	Serial.print(line->getFullArrayInString());
	Serial.print("\t");
	Serial.print(line->getDensity());
	Serial.print("\t");
	Serial.print(line->getLinePosition());
	Serial.print("\t");
	Serial.println(line->getIfAtCrossingY());
	//Serial.println(leftMotor.getPower());
	//Serial.println(rightMotor.getPower());
	//leftMotor.stop();
	//rightMotor.stop();
}
