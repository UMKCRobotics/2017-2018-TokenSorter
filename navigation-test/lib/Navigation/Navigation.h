#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "Arduino.h"
#include "Movement.h"

using namespace moveOptions;

class Intersection;
class IntersectionState;
class Navigation;
class Gameboard;


// Class used to store the game board intersections + states
class Gameboard {
	private:
		IntersectionState* startState = nullptr;
		Movement* movement;
		int round;
		void initializeBoard();
	public:
		Gameboard() {};
		Gameboard(int round_n, Movement* move);
		IntersectionState* getStartState() { return startState; };
};


// Class used for keeping track of robot on board
class Navigation {
	private:
		IntersectionState* currentState = nullptr;
		//Gameboard gameboard;
		Movement* movement;
	public:
		Navigation(int round_n, Movement& move);
		bool turnLeft();
		bool turnRight();
		bool goForward();
		bool goBackward();
		String getCurrentStateInfo();
};


// Used to express robot actions at a particular part of an intersection
class IntersectionState {
	private:
		Movement* movement;
		String stateName;
		Turn leftTurnEnum = NULL; // Turn enum val corresponding to left turn behavior
		Turn rightTurnEnum = NULL; // Turn enum val corresponding to right turn behavior
		Approach approachEnum = NULL; // Approach enum val corresponding to approach behavior
		BackwardApproach backwardApproachEnum = NULL; // Aproach enum val corresponding to behavior when approaching backwards
		IntersectionState* leftState = nullptr; // next state if taking a left turn
		IntersectionState* rightState = nullptr; // next state if taking a right turn
		IntersectionState* transitionState = nullptr;
		IntersectionState* backwardTransitionState = nullptr;
		Intersection* container = nullptr;
	protected:
		IntersectionState* connectedState = nullptr; // next state if advancing to next intersection
		IntersectionState* backwardConnectedState = nullptr; // next state if going backwards
	public:
		IntersectionState() {};
		IntersectionState(Movement* move, Intersection* intersection, String name = "def state name")
		{ 
			movement = move; container = intersection; stateName = name; 
		};
		// setters
		void setLeftTurn(Turn enumVal, IntersectionState& state) { leftTurnEnum = enumVal; leftState = &state; };
		void setRightTurn(Turn enumVal, IntersectionState& state) { rightTurnEnum = enumVal; rightState = &state; };
		void setTransitionTo(IntersectionState& state) { transitionState = &state; };
		void setBackwardTransitionTo(IntersectionState& state) { backwardTransitionState = &state; };
		void setApproach(Approach enumVal) { approachEnum = enumVal; };
		void setBackwardApproach(BackwardApproach enumVal) { backwardApproachEnum = enumVal; };
		void setContainer(Intersection* intersection) { container = intersection; };
		// getters
		String getName() { return stateName; };
		String getFullName();
		// other functions
		void connectTo(IntersectionState& state) { connectedState = &state; }; // creates one-way link
		void connectBackwardTo(IntersectionState& state) { backwardConnectedState = &state; }; // create one-way link
		IntersectionState* turnLeft();
		IntersectionState* turnRight();
		IntersectionState* goForward();
		IntersectionState* goBackward();
		// perform approaches
		IntersectionState* performApproach();
		IntersectionState* performBackwardApproach();
};


class Intersection {
	protected:
		// state pairs; first is from center "To" a/b/c/d, second is "From" center to a/b/c/d
		IntersectionState stateA[2];
		IntersectionState stateB[2];
		IntersectionState stateC[2];
		IntersectionState stateD[2];
		String intersectName;
		bool hasToken;
		Movement* movement;
	public:
		Intersection(Movement* move, String name);
		enum Direction {To = 0, From};
		void createConnection(IntersectionState localStateArr[], IntersectionState externalStateArr[]);
		void createBackwardConnection(IntersectionState localStateArr[], IntersectionState dropStateArr[]);
		// shortcut functions to connect using certain states
		void createConnectionUsingStateA(IntersectionState externalStateArr[]) { createConnection(stateA, externalStateArr); };
		void createConnectionUsingStateB(IntersectionState externalStateArr[]) { createConnection(stateB, externalStateArr); };
		void createConnectionUsingStateC(IntersectionState externalStateArr[]) { createConnection(stateC, externalStateArr); };
		void createConnectionUsingStateD(IntersectionState externalStateArr[]) { createConnection(stateD, externalStateArr); };
		void createBackwardConnectionUsingStateA(IntersectionState dropStateArr[]) { createBackwardConnection(stateA, dropStateArr); };
		void createBackwardConnectionUsingStateB(IntersectionState dropStateArr[]) { createBackwardConnection(stateB, dropStateArr); };
		void createBackwardConnectionUsingStateC(IntersectionState dropStateArr[]) { createBackwardConnection(stateC, dropStateArr); };
		void createBackwardConnectionUsingStateD(IntersectionState dropStateArr[]) { createBackwardConnection(stateD, dropStateArr); };
		// getters
		String getName() { return intersectName; };
		IntersectionState* getStateA() { return stateA; };
		IntersectionState* getStateB() { return stateB; };
		IntersectionState* getStateC() { return stateC; };
		IntersectionState* getStateD() { return stateD; };
};


// Type Start intersection
class IntersectionStart : public Intersection {
	public:
		IntersectionStart(Movement* move, String name);
};

// Type I intersection
class IntersectionI : public Intersection {
	public:
		IntersectionI(Movement* move, String name);
};

// Type II intersection
class IntersectionII : public Intersection {
	public:
		IntersectionII(Movement* move, String name);
};

// Type III intersection
class IntersectionIII : public Intersection {
	public:
		IntersectionIII(Movement* move, String name);
};

// Type IV intersection
class IntersectionIV : public Intersection {
	public:
		IntersectionIV(Movement* move, String name);
};

// Type V intersection
class IntersectionV : public Intersection {
	public:
		IntersectionV(Movement* move, String name);
};

// Type DropToken intersection
class IntersectionDropToken : public Intersection {
	public:
		IntersectionDropToken(Movement* move, String name);
};


#endif
