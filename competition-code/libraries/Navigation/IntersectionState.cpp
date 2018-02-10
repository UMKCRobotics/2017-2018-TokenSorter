#include "IntersectionState.h"


IntersectionState::IntersectionState(Movement* move, Intersection* intersection, String name)
{
	movement = move; container = intersection; stateName = name;
}

void IntersectionState::connectTo(IntersectionState& state) {
	// creates one-way link
	connectedState = &state;
};
void IntersectionState::connectBackwardTo(IntersectionState& state) {
	// create one-way link
	backwardConnectedState = &state;
};

IntersectionState* IntersectionState::performApproach() {
	// check if approach was set
	if (!approachEnum) {
		return nullptr;
	}
	// perform the movement
	movement->performApproach(approachEnum);
	// if there is a transition state, return it
	if (transitionState) {
		return transitionState;
	}
	// otherwise, return this state
	else {
		return this;
	}
}

IntersectionState* IntersectionState::performBackwardApproach() {
	// check if approach was set
	if (!backwardApproachEnum) {
		return nullptr;
	}
	// perform the movement
	movement->performBackwardApproach(backwardApproachEnum);
	// if there is a transition state, return it
	if (backwardTransitionState) {
		return backwardTransitionState;
	}
	// otherwise, return this state
	else {
		return this;
	}
}


String IntersectionState::getFullName() {
	return "Intersection |" + container->getName() + "| in state " + getName();
}

IntersectionState* IntersectionState::turnLeft() {
	// if turn state does not exist, return a null ptr
	if (!leftState) {
		return nullptr;
	}
	// otherwise, perform the movement and return corresponding state
	movement->performTurn(leftTurnEnum);
	return leftState;
}


IntersectionState* IntersectionState::turnRight() {
	// if turn state does not exist, return a null ptr
	if (!rightState) {
		return nullptr;
	}
	// otherwise, perform the movement and return corresponding state
	movement->performTurn(rightTurnEnum);
	return rightState;
}


IntersectionState* IntersectionState::goForward() {
	// if there does not exist a forward connected state, return null ptr
	if (!connectedState) {
		return nullptr;
	}
	// otherwise, ask the node to perform movement, return new state
	return connectedState->performApproach();
}


IntersectionState* IntersectionState::goBackward() {
	// if there does not exist a backward state or the backward state doesn't have a backward connected state, return null ptr
	if (!backwardState || !backwardState->backwardConnectedState) {
		return nullptr;
	}
	// otherwise, ask the node to perform movement, return new state
	return backwardState->backwardConnectedState->performBackwardApproach();
}


IntersectionState::~IntersectionState()
{
}
