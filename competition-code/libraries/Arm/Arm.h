#ifndef ARM_H
#define ARM_H
#include "Arduino.h"
#include "Servo.h"

namespace armOptions {
	enum ColorSlot {
		Red=0,
		Blue,
		Green,
		Yellow,
		Magenta,
		Cyan,
		Gray,
		Sensor,
		Hole
	};
}

using namespace armOptions;


struct ArmPosition {
	int servo_position;
	int count=0;
};


class Arm {
	private:
		// pins
		int linear_pin;
		int servo_pin;
		int em_pin;
		// servo classes for linear + servo
		Servo linear;
		Servo servo;
		// state of electro magnet
		bool em_state = false;
		// current arm position
		ArmPosition currentPosition;
		int currentArmHeight;
		// COLOR POSITIONS
		ArmPosition position[9];
	public:
		Arm();
		Arm(int linear, int servo, int em);
		~Arm() {};

};


#endif
