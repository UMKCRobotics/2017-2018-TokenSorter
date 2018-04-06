#include "Buttons.h"

Buttons::Buttons(int goPin, int stopPin) {
	goButton = StartButton(goPin);
	stopButton = StartButton(stopPin);
}

