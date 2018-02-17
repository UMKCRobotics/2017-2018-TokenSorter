//#include "ScrapController.h"
#include "LineIntersection.h"
//#include "TunnelRobot.h"
//#include "Navigation.h"
#include "Movement.h"
//#include "ColorSensor.h"
//#include "RoundSwitch.h"
//#include "GoStopButtons.h"


// define necessary constants here (pins)
#define MIDDLE_IR_PIN A0

// define Scrap components here (motors, encoders, motor speed controls, etc)


// define Movement component


// define Navigation component


// define TunnelRobot here


LineIntersection* line;



void setup() {
	// Start serial for debugging purposes
	Serial.begin(9600);
	Serial.println("serial started");
	line = new LineIntersection(MIDDLE_IR_PIN);
}


void loop() {
	delay(20);
	//Serial.print(line->getMiddleState());
	//Serial.print("\t");
	Serial.print(line->getFullArrayInString());
	Serial.print("\t");
	Serial.print(line->getDensity());
	Serial.print("\t");
	Serial.print(line->getLinePosition());
	Serial.print("\t");
	Serial.println(line->getIfAtCrossingY());
}