#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "Arduino.h"
#include "Movement.h"

using namespace moveOptions;

// Class used for keeping track of robot on board
class Navigation {


};


// Used to express robot actions at a particular part of an intersection
class IntersectionState {
	private:
		Movement* movement;
		Turn leftTurnEnum; // Turn enum val corresponding to left turn behavior
		Turn rightTurnEnum; // Turn enum val corresponding to right turn behavior
		Approach approachEnum; // Approach enum val corresponding to approach behavior
		IntersectionState* leftState = nullptr; // next state if taking a left turn
		IntersectionState* rightState = nullptr; // next state if taking a right turn
	protected:
		IntersectionState* connectedState = nullptr; // next state if advancing to next intersection
	public:
		IntersectionState();
		IntersectionState(Movement& move) { movement = &move; };
		void setLeftTurn(Turn enumVal, IntersectionState& state) { leftTurnEnum = enumVal; leftState = &state; };
		void setRightTurn(Turn enumVal, IntersectionState& state) { rightTurnEnum = enumVal; rightState = &state; };
		void setApproach(Approach enumVal) { approachEnum = enumVal; };
		void connectTo(IntersectionState& state) { connectedState = &state; }; // creates one-way link
		void connectBidirectionallyTo(IntersectionState& state) { connectTo(state); connectedState->connectTo(*this); } //creates two-way link
};


class Intersection {
	protected:
		IntersectionState stateA;
		IntersectionState stateB;
		IntersectionState stateC;
		IntersectionState stateD;
		String type;
		boolean hasToken;
		Movement* movement;
	public:
		Intersection(Movement& move) { movement = &move; };
};


// Type I intersection
class IntersectionI : public Intersection {
	private:
		IntersectionState stateToCenterFromB;
		IntersectionState stateToCenterFromD;
	public:
		IntersectionI(Movement& move);
};

// Type II intersection
class IntersectionII : public Intersection {
	public:
		IntersectionII(Movement& move);
};

// Type V intersection
class IntersectionV : public Intersection {
	public:
		IntersectionV(Movement& move);
};




#endif
