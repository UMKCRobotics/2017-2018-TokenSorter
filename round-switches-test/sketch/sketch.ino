#include "RoundSwitch.h"
RoundSwitch round1 = RoundSwitch();
void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(round1.getRound());
	delay(250);
}