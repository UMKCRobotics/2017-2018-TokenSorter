#include "RoundSwitch.h"

RoundSwitch::RoundSwitch() {
	pinMode(ROUND_SWITCH_1_PIN, INPUT);
	pinMode(ROUND_SWITCH_2_PIN, INPUT);
}
int RoundSwitch::getRound() {
	int currentRound = 1;
	if(digitalRead(ROUND_SWITCH_1_PIN) == HIGH)
		currentRound += 2;
	if(digitalRead(ROUND_SWITCH_2_PIN) == HIGH)
		currentRound += 1;
	return currentRound;
}