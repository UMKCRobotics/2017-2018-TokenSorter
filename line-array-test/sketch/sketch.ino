#include "LineIntersection.h"

LineIntersection lineSensor = LineIntersection();

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(lineSensor.getArrayDataInString());
	delay(250);
}