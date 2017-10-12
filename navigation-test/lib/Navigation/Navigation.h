#ifndef NAVIGATION_H
#define NAVIGATION_H


#include "Arduino.h"
#include "Movement.h"
#include "Gameboard.h"

using namespace std;

class Gameboard;

class Navigation
{
private:
	IntersectionState* currentState = nullptr;
	Gameboard* gameboard;
	Movement* movement;
public:
	Navigation() {};
	Navigation(int round_n, Movement& move);
	~Navigation();
	bool turnLeft();
	bool turnRight();
	bool goForward();
	bool goBackward();
	String getCurrentStateInfo();
};


#endif
