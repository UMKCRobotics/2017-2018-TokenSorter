#ifndef BUTTONS_H
#define BUTTONS_H
#include "Arduino.h"
#include "StartButton.h"


class Buttons {
private:
	StartButton goButton;
	StartButton stopButton;
public:
	Buttons() {};
	Buttons(int goPin, int stopPin);
	void checkGoButton() { goButton.checkButton(); }; // INTERRUPT FUNCTION
	void checkStopButton() { stopButton.checkButton(); }; // INTERRUPT FUNCTION
	bool wasGoPressed() { return goButton.wasPressed(); };
	bool wasStopPressed() { return stopButton.wasPressed(); };
	void resetGo() { goButton.reset(); };
	void resetStop() { stopButton.reset(); };
};






#endif