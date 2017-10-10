#include "Navigation.h"


Navigation::Navigation(int round_n, Movement& move) {
	movement = &move; //save pointer
	gameboard = Gameboard(round_n, movement); //create gameboard
	currentState = gameboard.getStartState(); //set current state as start state
}


String Navigation::getCurrentStateInfo() {
	return "Currently at " + currentState->getFullName();
}


void Navigation::turnLeft() {

}

void Navigation::turnRight() {

}

void Navigation::goForward() {

}

void Navigation::goBackward() {
	
}