#ifndef GAMEBOARD_H
#define GAMEBOARD_H



#include "Arduino.h"
#include "Movement.h"
#include "IntersectionState.h"
#include "Intersection.h"

class Gameboard
{
private:
	IntersectionState* startState = nullptr;
	Movement* movement;
	int round;
	void initializeBoard();
public:
	Gameboard(int round_n, Movement* move);
	~Gameboard();
	IntersectionState* getStartState() { return startState; };
};



#endif