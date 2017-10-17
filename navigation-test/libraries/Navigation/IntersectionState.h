#ifndef INTERSECTIONSTATE_H
#define INTERSECTIONSTATE_H

#include "Arduino.h"
#include "Intersection.h"
#include "Movement.h"

using namespace moveOptions;


class Intersection;



class IntersectionState
{
private:
	Movement* movement;
	String stateName;
	Turn leftTurnEnum;
	Turn rightTurnEnum;
	Approach approachEnum;
	BackwardApproach backwardApproachEnum;
	IntersectionState* leftState = nullptr;
	IntersectionState* rightState = nullptr;
	IntersectionState* transitionState = nullptr;
	IntersectionState* backwardTransitionState = nullptr;
	IntersectionState* backwardState = nullptr;
	Intersection* container = nullptr;
protected:
	
public:
	IntersectionState() {};
	IntersectionState(Movement* move, Intersection* intersection, String name);
	// setters
	void setLeftTurn(Turn enumVal, IntersectionState* state) { leftTurnEnum = enumVal; leftState = state; };
	void setRightTurn(Turn enumVal, IntersectionState* state) { rightTurnEnum = enumVal; rightState = state; };
	void setTransitionTo(IntersectionState* state) { transitionState = state; };
	void setBackwardTransitionTo(IntersectionState* state) { backwardTransitionState = state; };
	void setBackwardState(IntersectionState* state) { backwardState = state; };
	void setApproach(Approach enumVal) { approachEnum = enumVal; };
	void setBackwardApproach(BackwardApproach enumVal) { backwardApproachEnum = enumVal; };
	void setContainer(Intersection* intersection) { container = intersection; };
	// getters
	String getName() { return stateName; };
	String getFullName();
	IntersectionState* getSelf() { return this; };
	// other functions
	IntersectionState* connectedState = nullptr;
	IntersectionState* backwardConnectedState = nullptr;
	void connectTo(IntersectionState& state); // creates one-way link
	void connectBackwardTo(IntersectionState& state); // create one-way link
	IntersectionState* turnLeft();
	IntersectionState* turnRight();
	IntersectionState* goForward();
	IntersectionState* goBackward();
	// perform approaches
	IntersectionState* performApproach();
	IntersectionState* performBackwardApproach();

	~IntersectionState();
};




#endif