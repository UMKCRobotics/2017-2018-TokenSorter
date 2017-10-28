#ifndef SCRAPCONTROLLER_H
#define SCRAPCONTROLLER_H
#include "Arduino.h"
#include "ScrapDefinitions.h"


// abstract classes (interfaces)
class ScrapMotorInterface {
	protected:
		int currPower; // stores current power
		int currDir; // stores current direction (1, -1, 0)
		int powerMultiplier; // stores multiplier (-1 flips direction, 1 keeps it the same)
		virtual void initMotor() = 0; // use to initialize output/input pins
	public:
		virtual void setMotor(int pwm) = 0; // sets both direction + power of motor
		virtual void setDirection(int pwm) = 0; // set direction only
		virtual void setDirectionMultiplier(int multi) = 0; // set multiplier (1 or -1) to flip dirs
		virtual void setPower(int pwm) = 0; // set power only
		virtual void incrementPower(int val) = 0; // increase power -> DOES NOT flip directions
		virtual void decrementPower(int val) = 0; // decrease power -> DOES NOT flip directions
		virtual int getDirection() = 0; // return current direction (1, -1, 0)
		virtual int getPower() = 0; // return power
		virtual void stop() = 0; // stop the motor; should immediately send signal to stop moving
};


class ScrapEncoderInterface {
	protected:
		volatile long encCount;
		virtual void initEncoder() = 0;
	public:
		virtual long getCount() = 0;
		virtual void resetCount() = 0;
		virtual void setCount(long newCount) = 0;
		virtual void incrementCount() = 0;
		virtual void decrementCount() = 0;
		virtual void checkEncoder() = 0;
		virtual void checkEncoderFlipped() = 0;
};



// concrete classes

// ScrapMotorSinglePin: for use with motor controllers that use 1 pin for direction, 1 PWM pin for speed
class ScrapMotorSinglePin: public ScrapMotorInterface {
	protected:
		int PIN_D;
		int PIN_PWM;
		virtual void initMotor();
	public:
		ScrapMotorSinglePin(int PinD, int PinPWM, int dirMultip = 1);
		virtual void setMotor(int pwm);
		virtual void setDirection(int pwm);
		virtual void setDirectionMultiplier(int multi);
		virtual void setPower(int pwm);
		virtual void incrementPower(int val = 1) { setPower(currDir+val); };
		virtual void decrementPower(int val = 1) { setPower(currDir-val); };
		virtual int getDirection();
		virtual int getPower();
		virtual void stop();
};


// ScrapMotor: for use with motor controllers that use 2 pins for direction, 1 PWM pin for speed
class ScrapMotor: public ScrapMotorInterface {
	protected:
		int PIN_D1;
		int PIN_D2;
		int PIN_PWM;
		virtual void initMotor();
	public:
		ScrapMotor(int PinD1, int PinD2, int PinPWM, int dirMultip = 1);
		virtual void setMotor(int pwm);
		virtual void setDirection(int pwm);
		virtual void setDirectionMultiplier(int multi);
		virtual void setPower(int pwm);
		virtual void incrementPower(int val = 1) { setPower(currDir+val); };
		virtual void decrementPower(int val = 1) { setPower(currDir-val); };
		virtual int getDirection();
		virtual int getPower();
		virtual void stop();
};


class ScrapEncoder: public ScrapEncoderInterface {
	protected:
		int PINA_INTERRUPT;
		int PINB_CHECKER;
		virtual void initEncoder();
	public:
		ScrapEncoder(int pinA, int pinB);
		virtual long getCount();
		virtual void resetCount();
		virtual void setCount(long newCount);
		virtual void incrementCount();
		virtual void decrementCount();
		virtual void checkEncoder();
		virtual void checkEncoderFlipped();
};


/*class ScrapMotorControl {
	private:
		unsigned long prevTime = 0;
		float prevSpeed = 0.0;
		float speedGoal = 0.0;
		long prevCount = 0;
		int minPower = SCRAPMOTORCONTROL_MINPOWER;
		float minSpeed;
		float maxSpeed;
		ScrapMotorInterface* motor;
		ScrapEncoderInterface* encoder;
		float calcSpeed(); // calculates speed and updates relevant vals
	public:
		ScrapMotorControl();
		ScrapMotorControl(ScrapMotorInterface& mot, ScrapEncoderInterface& enc);
		void setControl(float newSpeed); // set direction + speed
		void setControlEnc(int encPerSec) { setControl(convertToSpeed(encPerSec)); };
		void setSpeed(float newSpeed); // set direction only
		void setSpeedEnc(int encPerSec) { setSpeed(convertToSpeed(encPerSec)); };
		void setMinSpeed(float newMin) { minSpeed = newMin; };
		void setMinSpeedEnc(float newMinEnc) { setMinSpeed(convertToSpeed(newMinEnc)); };
		void setMaxSpeed(float newMax) { maxSpeed = newMax; };
		void setMaxSpeedEnc(float newMaxEnc) { setMaxSpeed(convertToSpeed(newMaxEnc)); };
		void incrementSpeed(int speedEncDiff);
		void decrementSpeed(int speedEncDiff);
		float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
		float constrainFloat(float x, float min, float max);
		float convertToSpeed(int encPerSec);
		void setMinPower(int power) { minPower = power; };
		void reset();
		void stop();
		long getCount() { return encoder->getCount(); };
		int getSpeedEnc() { return prevSpeed*1000000; };
		float getSpeed(); // returns speed
		float getSpeedGoal() { return speedGoal; }; // return speed goal
		int getSpeedEncGoal() { return getSpeedGoal()*1000000; };
		unsigned long getTime();
		void performMovement();
		void attachMotor(ScrapMotorInterface& mot) { motor = &mot; };
		void attachEncoder(ScrapEncoderInterface& enc) { encoder = &enc; };
};*/


class ScrapMotorControl {
	/*
	Speed is stored as Encoder Value Change PER Second
	MicroSpeed is stored as Encoder Value Change PER Microsecond
	*/
	protected:
		unsigned long prevTime = 0; // time of previous speed calculation
		float prevSpeed = 0.0; // previously-calculated speed
		float speedGoal = 0.0; // speed to reach
		long prevCount = 0; // previous encoder count
		int minPower = 0; // minimum power to get motor to move
		float minSpeed;
		float maxSpeed;
		ScrapMotorInterface* motor; // motor
		ScrapEncoderInterface* encoder; // encoder
		float calcSpeed(); // calculates speed and updates relevant time
	public:
		ScrapMotorControl();
		ScrapMotorControl(ScrapMotorInterface& mot, ScrapEncoderInterface& enc);
		// set control
		void setControl(float newSpeed); // set direction + speed
		// set speed goal
		void setSpeed(float newSpeed); // set speed only
		// set min speed
		void setMinSpeed(float newMin) { minSpeed = newMin; };
		// set max speed
		void setMaxSpeed(float newMax) { maxSpeed = newMax; };
		// set min motor power
		void setMinPower(int power) { minPower = power; };
		// change speed
		void incrementSpeed(float speedDiff);
		void decrementSpeed(float speedDiff);
		// helper functions
		float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
		float constrainFloat(float x, float min, float max);
		float convertToSpeed(float microSpeed);
		// reset and stop
		void reset();
		void stop();
		// get/set encoder count
		long getCount() { return encoder->getCount(); };
		void setCount(long count) { encoder->setCount(count); };
		void resetCount() { encoder->resetCount(); };
		// get motor direction
		int getDirection() { return motor->getDirection(); };
		// get previous speed and speed goal
		float getSpeed() { return prevSpeed; };
		float getSpeedGoal() { return speedGoal; }; // return speed goal
		// get time of previous reading
		unsigned long getTime();
		// perform movement, incrementing speed/power/time
		void performMovement();
		// attach motor/encoder
		void attachMotor(ScrapMotorInterface& mot) { motor = &mot; };
		void attachEncoder(ScrapEncoderInterface& enc) { encoder = &enc; };
};


class ScrapSwitch {
	private:
		int PIN_SWITCH;
		bool highWhenOpen = true;
		void initSwitch() { pinMode(PIN_SWITCH,INPUT); };
	public:
		ScrapSwitch(int pinSwitch) { PIN_SWITCH=pinSwitch; initSwitch(); };
		void setOpenHigh(bool openHigh) { highWhenOpen = openHigh; };
		bool getIfPressed() {
			if (highWhenOpen) 
				return (digitalRead(PIN_SWITCH)==LOW);
			else
				return (digitalRead(PIN_SWITCH)==HIGH);
		};
};


class ScrapControllerInterface {
	protected:
		long goal;
		long encTolerance;
		long slowdownThresh;
		int minSlowPower;
		float minEncSpeed;
		float maxEncSpeed;
		virtual float calcSpeed() = 0;
	public:
		// set/get encoder goal
		virtual bool set(long g) = 0;
		virtual long getGoal() = 0;
		virtual long getDiff() = 0;
		virtual bool checkIfDone() = 0;
		// set/get speed goal; these are wrappers for motor control commands
		virtual void setSpeed(float speed) = 0;
		virtual void incrementSpeed(float speedDiff) = 0;
		virtual void decrementSpeed(float speedDiff) = 0;
		virtual float getSpeed() = 0;
		// stop movement
		virtual void stop() = 0;
		// get encoder count
		virtual long getCount() = 0;
		// perform movement or reset
		virtual bool performMovement() = 0;
		virtual bool performReset() = 0;
		// set values
		virtual void setEncTolerance(long tolerance) { encTolerance = tolerance; };
		virtual void setSlowdownThresh(long thresh) { slowdownThresh = thresh; };
		virtual void setMinSlowPower(int power) { minSlowPower = power; };
		virtual void setMinEncSpeed(float speed) { minEncSpeed = speed; };
		virtual void setMaxSpeedEnc(float speed) { maxEncSpeed = speed; };
};


class ScrapController: public ScrapControllerInterface  {
	protected:
		ScrapSwitch* resetswitch;
		ScrapMotorControl* speedControl;
		virtual float calcSpeed();
	public:
		ScrapController();
		ScrapController(ScrapMotorControl& motorControl);
		ScrapController(ScrapMotor& mot, ScrapEncoder& enc);
		ScrapController(ScrapMotor& mot, ScrapEncoder& enc, ScrapSwitch& swi);
		// set/get encoder goal
		virtual bool set(long g);
		virtual long getGoal() { return goal; };
		virtual long getDiff();
		virtual bool checkIfDone();
		// set/get speed goal; these are wrappers for motor control commands
		virtual void setSpeed(float speed) { speedControl->setControl(speed); };
		virtual void incrementSpeed(float speedDiff);
		virtual void decrementSpeed(float speedDiff);
		virtual float getSpeed() { return speedControl->getSpeed(); };
		// stop movement
		virtual void stop();
		// get encoder count
		virtual long getCount() { return speedControl->getCount(); };
		// perform movement or reset
		virtual bool performMovement();
		virtual void performSpeedMovement() { speedControl->performMovement(); };
		virtual bool performReset();
		// attach components
		void attachSwitch(ScrapSwitch& swi) { resetswitch = &swi; };
};


class ScrapDualController: public ScrapControllerInterface {
	protected:
		long goal1;
		long goal2;
		long diffTolerance;
		long encTolerance1;
		long encTolerance2;
		long slowdownThresh1;
		long slowdownThresh2;
		int minSlowPower1;
		int minSlowPower2;
		float speedBalance; // speed to increment/decrement to balance motors
		ScrapSwitch* switch1;
		ScrapSwitch* switch2;
		ScrapMotorControl* speedControl1;
		ScrapMotorControl* speedControl2;
		virtual float calcSpeed1();
		virtual float calcSpeed2();
		virtual float calcSpeed() { return (calcSpeed1() + calcSpeed2())/2.0; }; 
	public:
		ScrapDualController();
		ScrapDualController(ScrapMotorControl& motorControl1, ScrapMotorControl& motorControl2);
		ScrapDualController(ScrapMotor& mot1, ScrapMotor& mot2, ScrapEncoder& enc1, ScrapEncoder& enc2);
		ScrapDualController(ScrapMotor& mot1, ScrapMotor& mot2, ScrapEncoder& enc1, ScrapEncoder& enc2, ScrapSwitch& swi1, ScrapSwitch& swi2);
		// get/set encoder goals
		virtual bool set(long g1, long g2);
		virtual bool set(long goal);
		virtual void shiftCount(); //sets encoders to relative value from current goal
		virtual long getGoal1() { return goal1; };
		virtual long getGoal2() { return goal2; };
		virtual long getGoal() { return (goal1+goal2)/2; };
		virtual long getDiff1();
		virtual long getDiff2();
		virtual long getDiff() { return (getDiff1() + getDiff2())/2; };
		virtual bool checkIfDone1();
		virtual bool checkIfDone2();
		virtual bool checkIfDone();
		// get/set speed goal; these are mostly wrappers for motor control commands
		virtual void setSpeed1(float speed) { speedControl1->setControl(speed); };
		virtual void setSpeed2(float speed) { speedControl2->setControl(speed); };
		virtual void setSpeed(float speed) { setSpeed1(speed); setSpeed2(speed); };
		virtual void incrementSpeed(float speedDiff);
		virtual void decrementSpeed(float speedDiff);
		virtual float getSpeed1() { return speedControl1->getSpeed(); };
		virtual float getSpeed2() { return speedControl2->getSpeed(); };
		virtual float getSpeed() { return (getSpeed1() + getSpeed2())/2.0; };
		virtual bool checkIfNoSpeed(); // check if both motors are not moving
		// stop movement
		virtual void stop();
		// get encoder count
		long getCount1() { return speedControl1->getCount(); };
		long getCount2() { return speedControl2->getCount(); };
		long getCount() { return (getCount1()+getCount2())/2; }; //returns average of encoder counts
		void resetCount() { speedControl1->resetCount(); speedControl2->resetCount();};
		// perform movement or reset
		bool performMovement();
		void performSpeedMovement() { speedControl1->performMovement(); speedControl2->performMovement(); };
		bool performReset();
		// balance motor speeds
		void moveSpeedToward1(float speedDiff);
		void moveSpeedToward2(float speedDiff);
		void balanceSpeed();
		// attach
		void attachSwitch1(ScrapSwitch& swi) { switch1 = &swi; };
		void attachSwitch2(ScrapSwitch& swi) { switch2 = &swi; };
		// set values
		virtual void setDiffTolerance(long tolerance) { diffTolerance = tolerance; };
		virtual void setEncTolerance1(long tolerance) { encTolerance1 = tolerance; };
		virtual void setEncTolerance2(long tolerance) { encTolerance2 = tolerance; };
		virtual void setEncTolerance(long tolerance) { setEncTolerance1(tolerance); setEncTolerance2(tolerance); };
		virtual void setSlowdownThresh1(long thresh) { slowdownThresh1 = thresh; };
		virtual void setSlowdownThresh2(long thresh) { slowdownThresh2 = thresh; };
		virtual void setSlowdownThresh(long thresh) { setSlowdownThresh1(thresh); setSlowdownThresh2(thresh); };
		virtual void setMinSlowPower1(int power) { minSlowPower1 = power; };
		virtual void setMinSlowPower2(int power) { minSlowPower2 = power; };
		virtual void setMinSlowPower(int power) { setMinSlowPower1(power); setMinSlowPower2(power); };
};


/*class ScrapDualController {
	private:
		long goal1;
		long goal2;
		int diffTolerance = SCRAPDUALCONTROLLER_DIFFTOLERANCE; //max diff in encoder values
		int encTolerance = SCRAPDUALCONTROLLER_ENCTOLERANCE; // max window of error from set goal
		int slowdownThresh1 = SCRAPDUALCONTROLLER_SLOWDOWNTHRESH1; // slow down range
		int slowdownThresh2 = SCRAPDUALCONTROLLER_SLOWDOWNTHRESH2; // slow down range
		int minSlowPower1 = SCRAPDUALCONTROLLER_MINSLOWPOWER1; // minimum power of motor1
		int minSlowPower2 = SCRAPDUALCONTROLLER_MINSLOWPOWER2; // minimum power of motor2
		int minEncSpeed = SCRAPDUALCONTROLLER_MINENCSPEED;
		int maxEncSpeed = SCRAPDUALCONTROLLER_MAXENCSPEED;
		int encSpeedBalance = SCRAPDUALCONTROLLER_ENCSPEEDBALANCE;
		ScrapMotor* motor1;
		ScrapMotor* motor2;
		ScrapEncoder* encoder1;
		ScrapEncoder* encoder2;
		ScrapSwitch* switch1;
		ScrapSwitch* switch2;
	public:
		ScrapDualController();
		ScrapDualController(ScrapMotor& mot1, ScrapMotor& mot2, ScrapEncoder& enc1, ScrapEncoder& enc2);
		ScrapDualController(ScrapMotor& mot1, ScrapMotor& mot2, ScrapEncoder& enc1, ScrapEncoder& enc2, ScrapSwitch& swi1, ScrapSwitch& swi2);
		// speed can be externally controlled
		ScrapMotorControl speedControl1;
		ScrapMotorControl speedControl2;
		// other functions and junk
		bool set(long g1,long g2); //returns state of 'done'
		bool set(long goal_both); //returns state of 'done'
		void shiftCount(); //sets encoders to relative value from current goal
		long getGoal1() { return goal1; };
		long getGoal2() { return goal2; };
		long getGoal() { return (goal1+goal2)/2; };
		long getDiff1();
		long getDiff2();
		bool checkIfDone();
		bool checkIfDone1();
		bool checkIfDone2();
		bool checkIfNoSpeed(); 
		float calcSpeed1();
		float calcSpeed2(); 
		bool performMovement();
		bool performReset();
		void incrementSpeed(int speedEncDiff);
		void decrementSpeed(int speedEncDiff);
		void moveSpeedToward1(int speedEncDiff);
		void moveSpeedToward2(int speedEncDiff);
		void balanceSpeed();
		void stop();
		long getCount1() { return encoder1->getCount(); };
		long getCount2() { return encoder2->getCount(); };
		long getCount() { return (getCount1()+getCount2())/2; }; //returns average of encoder counts
		void resetCount() { encoder1->resetCount(); encoder2->resetCount();};
		void attachMotor1(ScrapMotor& mot);
		void attachMotor2(ScrapMotor& mot);
		void attachEncoder1(ScrapEncoder& enc);
		void attachEncoder2(ScrapEncoder& enc);
		void attachSwitch1(ScrapSwitch& swi) { switch1 = &swi; };
		void attachSwitch2(ScrapSwitch& swi) { switch2 = &swi; };
};*/


class ScrapFullController {
	private:
		ScrapController* xControl;
		ScrapDualController* yControl;
		float diffDecim = 0.01; // percentage diff from desired proportion
		float desiredProportion; // x_goal/y_goal proportion
		int encSpeedBalance = 30;
	public:
		ScrapFullController();
		ScrapFullController(ScrapController& xCont, ScrapDualController& yCont);
		bool set(int gx, int gy);
		int getGoalX() { return xControl->getGoal(); };
		int getGoalY() { return yControl->getGoal(); };
		int getCountX() { return xControl->getCount(); };
		int getCountY() { return yControl->getCount(); };
		bool checkIfDoneX() { return xControl->checkIfDone(); };
		bool checkIfDoneY() { return yControl->checkIfDone(); };
		bool checkIfDone() { return checkIfDoneX() && checkIfDoneY(); };
		bool performMovement();
		bool performReset();
		float getMovementProportion();
		void balanceSpeed(); 
		void moveSpeedTowardX(int speedEncDiff);
		void moveSpeedTowardY(int speedEncDiff);
		void stop() { xControl->stop(); yControl->stop(); };
		void attachControllerX(ScrapController& xCont);
		void attachControllerY(ScrapDualController& yCont);
};


#endif
