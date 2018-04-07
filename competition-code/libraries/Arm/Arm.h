#ifndef ARM_H
#define ARM_H
#include "Arduino.h"
#include "Servo.h"

namespace armOptions {
	enum ColorSlot {
		Hole=0,
		Red,
		Green,
		Blue,
		Yellow,
		Magenta,
		Cyan,
		Gray,
		Sensor
	};
}


struct ArmPosition {
	int servo_position;
	int arm_up;
	int arm_down;
	int count=0;
};

using namespace armOptions;

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
		ArmPosition position[9] = {
			{180,40,125,0}, // Hole
			{134,40,87,0}, // Red
			{113,40,87,0}, // Green
			{92,40,87,0}, // Blue
			{69,40,87,0}, // Yellow
			{48,40,87,0}, // Magenta
			{30,40,87,0}, // Cyan
			{8,40,87,0}, // Gray
			{157,40,60,0} // Sensor
		};
	public:
		Arm() {};
		Arm(int linearPin, int servoPin, int emPin);
		void setEmOn() { digitalWrite(em_pin,LOW); em_state = true; }; // electromagnet on
		void setEmOff() { digitalWrite(em_pin,HIGH); em_state = false; }; // electromagnet off
		bool getIfEmOn() { return em_state; };
		void moveArmToPosition(ColorSlot slot);
		void moveArmToPosition(int slot);
		void moveArmDown();
		void moveArmUp();
		void addCount() { };
		void dumpAll() { };

		~Arm() {};


};


#endif
