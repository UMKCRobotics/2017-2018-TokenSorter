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
		Gray
	};
}

using namespace armOptions;


struct ArmPosition {
	int servo_position;
	int count;
};


class Arm {
	private:
		int linear_pin;
		int servo_pin;
		int em_pin;
		Servo linear;
		Servo servo;
		bool em_state = false;
		// COLOR POSITIONS

	public:
		Arm();
		Arm(int linear, int servo, int em);
		~Arm() {};

};







#endif
