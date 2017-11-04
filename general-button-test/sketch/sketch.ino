#define BUTTON_PIN 2

bool was_pressed = false;
unsigned long previous_time_pressed = 0;
unsigned long current_time_pressed = 0;
const unsigned long min_press = 120;
const unsigned long max_press = 1500;
bool was_actually_just_pressed = false;
bool was_actually_just_badly_pressed = false;
unsigned long good_press_count = 0;


void setup() {
	pinMode(BUTTON_PIN, INPUT);
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(2),checkButton,CHANGE);
}

void loop() {
	if (was_actually_just_pressed) {
		good_press_count++;
		Serial.print("GOOD PRESSED! ");
		Serial.println(good_press_count);
		was_actually_just_pressed = false;
	}
	else if (was_actually_just_badly_pressed) {
		Serial.println("BAD PRESS!");
		was_actually_just_badly_pressed = false;
	}
}

void checkButton() {
	current_time_pressed = millis();
	// make sure that button is pressed when checking if was not pressed before
	if (digitalRead(BUTTON_PIN) == HIGH) {
		// if was not pressed, set previous time to current time, register as a press
		if (!was_pressed) {
			previous_time_pressed = current_time_pressed;
			was_pressed = true;
		}
		else {
			// do nothing, this is a bad input
		}
	}
	// make sure button is NOT pressed when checking if was pressed before
	else {
		// if was pressed 
		if (was_pressed) {
			// if between min and max time:
			if (current_time_pressed - previous_time_pressed >= min_press &&
				current_time_pressed - previous_time_pressed <= max_press) {
				// then it was ACTUALLY pressed
				was_actually_just_pressed = true;
			}
			else {
				// otherwise, this was a bad press
				was_actually_just_badly_pressed = true;
			}
			was_pressed = false;
		}
	}
}