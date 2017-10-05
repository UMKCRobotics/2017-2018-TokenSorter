#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "Arduino.h"
#include "Movement.h"

using namespace moveOptions;

class Intersection;
class IntersectionState;


// Class used for keeping track of robot on board
class Navigation {


};


// Class used to store the game board intersections + states
class GameBoard {
	private:
		IntersectionState* startNode = nullptr;
	public:
		GameBoard(int round);
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
		IntersectionState* transitionState = nullptr;
		Intersection* container = nullptr;
	protected:
		IntersectionState* connectedState = nullptr; // next state if advancing to next intersection
	public:
		IntersectionState();
		IntersectionState(Movement& move, Intersection* intersection) { movement = &move; container = intersection; };
		void setLeftTurn(Turn enumVal, IntersectionState& state) { leftTurnEnum = enumVal; leftState = &state; };
		void setRightTurn(Turn enumVal, IntersectionState& state) { rightTurnEnum = enumVal; rightState = &state; };
		void setTransitionTo(IntersectionState& state) { transitionState = &state; };
		void setApproach(Approach enumVal) { approachEnum = enumVal; };
		void setContainer(Intersection* intersection) { container = intersection; };
		void connectTo(IntersectionState& state) { connectedState = &state; }; // creates one-way link
		IntersectionState* turnLeft();
		IntersectionState* turnRight();
		IntersectionState* goForward();
};


class Intersection {
	protected:
		IntersectionState stateA[2];
		IntersectionState stateB[2];
		IntersectionState stateC[2];
		IntersectionState stateD[2];
		String intersectName;
		boolean hasToken;
		Movement* movement;
	public:
		Intersection(Movement& move, String name);
		enum Direction {To = 0, From = 1};
		void createConnection(IntersectionState localStateArr[], IntersectionState externalStateArr[]);
		String getName() { return intersectName; };
};


// Type Start intersection
class IntersectionStart : public Intersection {
	public:
		IntersectionStart(Movement& move, String name);
};

// Type I intersection
class IntersectionI : public Intersection {
	public:
		IntersectionI(Movement& move, String name);
};

// Type II intersection
class IntersectionII : public Intersection {
	public:
		IntersectionII(Movement& move, String name);
};

// Type III intersection
class IntersectionIII : public Intersection {
	public:
		IntersectionIII(Movement& move, String name);
};

// Type IV intersection
class IntersectionIV : public Intersection {
	public:
		IntersectionIV(Movement& move, String name);
};

// Type V intersection
class IntersectionV : public Intersection {
	public:
		IntersectionV(Movement& move, String name);
};


#endif
