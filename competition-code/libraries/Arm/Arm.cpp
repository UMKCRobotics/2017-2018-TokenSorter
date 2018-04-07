#include "Arm.h"

Arm::Arm(int linearPin, int servoPin, int emPin) {
	linear_pin = linearPin;
	linear.attach(linear_pin);
	servo_pin = servoPin;
	servo.attach(servo_pin);
	em_pin = emPin;
	pinMode(em_pin,OUTPUT);
	setEmOff(); // turn off electromagnet
	moveArmToPosition(Hole);
}


void Arm::moveArmToPosition(int slot) {
	// check if robot height is already in place
	ArmPosition requestedPos = position[slot];
	if (currentArmHeight != requestedPos.arm_up) {
		// move to height
		linear.write(requestedPos.arm_up);
		delay(2000);
	}
	else {
		// do nothing cause we done
	}
	// now that we are at right height, move to requested position
	if (currentPosition.servo_position != requestedPos.servo_position) {
		// move to position
		servo.write(requestedPos.servo_position);
		delay(1000);
	}
	currentPosition = requestedPos;
	currentArmHeight = currentPosition.arm_up;
}


void Arm::moveArmToPosition(ColorSlot slot) {
	moveArmToPosition((int)slot);
}


void Arm::moveArmDown() {
	// check if height is already correct
	Serial.println(currentArmHeight);
	Serial.println(currentPosition.arm_down);
	if (currentArmHeight != currentPosition.arm_down) {
		// move to height
		linear.write(currentPosition.arm_down);
		delay(2000);
		currentArmHeight = currentPosition.arm_down;
	}
	else {
		// do nothing cause we done
	}

}


void Arm::moveArmUp() {
	// check if height is already correct
	Serial.println(currentArmHeight);
	Serial.println(currentPosition.arm_up);
	if (currentArmHeight != currentPosition.arm_up) {
		// move to height
		linear.write(currentPosition.arm_up);
		delay(2000);
		currentArmHeight = currentPosition.arm_up;
	}
	else {
		// do nothing cause we done
	}
}

