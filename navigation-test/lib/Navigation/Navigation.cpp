#include "Navigation.h"


Navigation::Navigation(int round_n, Movement& move)
{
	movement = &move; //save pointer
	//IntersectionStart intersectionStart = IntersectionStart(movement, "Test Intersection");
	//currentState = &intersectionStart.getStateA()[Intersection::To];
	gameboard = new Gameboard(round_n, movement); //create gameboard
	//IntersectionStart* start = new IntersectionStart(movement, "test intersection");
	//currentState = start->getStateA()->To;//gameboard->getStartState(); //set current state as start state
	currentState = gameboard->getStartState(); //set current state as start state
}


Navigation::~Navigation()
{
}

bool Navigation::turnLeft()
{
	// attempt to turn left and get new state
	IntersectionState* newState = currentState->turnLeft();
	// if new state is a null pointer, then we can't go left so return false
	if (!newState) {
		return false;
	}
	// otherwise, current state became the new state and return true
	else {
		currentState = newState;
		return true;
	}
}

bool Navigation::turnRight()
{
	// attempt to turn right and get new state
	IntersectionState* newState = currentState->turnRight();
	// if new state is a null pointer, then we can't go right so return false
	if (!newState) {
		return false;
	}
	// otherwise, current state became the new state and return true
	else {
		currentState = newState;
		return true;
	}
}

bool Navigation::goForward()
{
	// attempt to go forward and get new state
	IntersectionState* newState = currentState->goForward();
	// if new state is a null pointer, then we can't go forward so return false
	if (!newState) {
		return false;
	}
	// otherwise, current state became the new state and return true
	else {
		currentState = newState;
		return true;
	}
}

bool Navigation::goBackward()
{
	// attempt to go backward and get new state
	IntersectionState* newState = currentState->goBackward();
	// if new state is a null pointer, then we can't go backward so return false
	if (!newState) {
		return false;
	}
	// otherwise, current state became the new state and return true
	else {
		currentState = newState;
		return true;
	}
}

String Navigation::getCurrentStateInfo()
{
	return "Currently at " + currentState->getFullName();
}
