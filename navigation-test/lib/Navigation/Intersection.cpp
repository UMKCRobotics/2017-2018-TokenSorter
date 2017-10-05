#include "Navigation.h"


Intersection::Intersection(Movement& move, String name) { 
	stateA[To] = IntersectionState(move, this);
	stateA[From] = IntersectionState(move,this);
	stateB[To] = IntersectionState(move, this);
	stateB[From] = IntersectionState(move, this);
	stateC[To] = IntersectionState(move, this);
	stateC[From] = IntersectionState(move, this);
	stateD[To] = IntersectionState(move, this);
	stateD[From] = IntersectionState(move, this);
	movement = &move;
	intersectName = name;
}

void Intersection::createConnection(IntersectionState localStateArr[], IntersectionState externalStateArr[]) {
	// create a bidirectional connection between To and From versions of given ItersectionStates
	localStateArr[To].connectTo(externalStateArr[From]);
	externalStateArr[To].connectTo(localStateArr[From]);
}


IntersectionStart::IntersectionStart(Movement& move, String name) : Intersection(move, name) {
	/*
	+---------------------------------+
	|                                 |
	|                A                |
	|                                 |
	|                ^                |
	|               /|\               |
	|                |                |
	|              Start              |
	|                |                |
	|                |                |
	|                |                |
	|                                 |
	|                B                |
	|                                 |
	+---------------------------------+
	*/
	// This intersection CANNOT be approached from B 
	// setup states To/From A
	stateA[To].setLeftTurn(Left180, stateB[To]);
	stateA[To].setRightTurn(Right180, stateB[To]);
	stateA[From].setApproach(MoveIntoSquare);
	// setup states To/From B
	stateB[To].setLeftTurn(Left180, stateA[To]);
	stateB[To].setRightTurn(Right180, stateA[To]);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateB[To]);
}


IntersectionI::IntersectionI(Movement& move, String name) : Intersection(move, name) {
    /*

                            A
                            |
                            |
                            |
                            t
                          / | \
                        /   |   \
                      /     |     \
                  B /        C       \ D
    */
	// setup states To/From A
	stateA[To].setLeftTurn(Left135, stateB[To]);
	stateA[To].setRightTurn(Right135, stateD[To]);
	stateA[From].setApproach(FollowUntilTokenSlot);
	// setup states To/From B
	stateB[To].setLeftTurn(Left90, stateC[To]);
	stateB[To].setRightTurn(Right90, stateA[To]);
	stateB[From].setLeftTurn(Left45, stateA[To]);
	stateB[From].setRightTurn(Right90, stateD[To]);
	stateB[From].setApproach(FollowUntilTokenSlot);
	// setup states To/From C
	stateC[To].setLeftTurn(Left90, stateD[To]);
	stateC[To].setRightTurn(Right90, stateB[To]);
	stateC[From].setApproach(FollowUntilTokenSlot);
	// setup states To/From D
	stateD[To].setLeftTurn(Left90, stateA[To]);
	stateD[To].setRightTurn(Right90, stateC[To]);
	stateD[From].setLeftTurn(Left90, stateB[To]);
	stateD[From].setRightTurn(Right45, stateA[To]);
	stateD[From].setApproach(FollowUntilTokenSlot);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateC[To]);
	stateC[From].setTransitionTo(stateA[To]);
}


IntersectionII::IntersectionII(Movement& move, String name) : Intersection(move, name) {
    /*

                            A
                            |
                            |
                            |
                  B --------t-------- D
                            |
                            |
                            |
                            C
    */
	// setup state To A
	stateA[To].setLeftTurn(Left90, stateB[To]);
	stateA[To].setRightTurn(Right90, stateD[To]);
	stateA[From].setApproach(FollowUntilTokenSlot);
	// setup state To B
	stateB[To].setLeftTurn(Left90, stateC[To]);
	stateB[To].setRightTurn(Right90, stateA[To]);
	stateB[From].setApproach(FollowUntilTokenSlot);
	// setup state To C
	stateC[To].setLeftTurn(Left90, stateD[To]);
	stateC[To].setRightTurn(Right90, stateB[To]);
	stateC[From].setApproach(FollowUntilTokenSlot);
	// setup state To D
	stateD[To].setLeftTurn(Left90, stateA[To]);
	stateD[To].setRightTurn(Right90, stateC[To]);
	stateD[From].setApproach(FollowUntilTokenSlot);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateC[To]);
	stateC[From].setTransitionTo(stateA[To]);
	stateB[From].setTransitionTo(stateD[To]);
	stateD[From].setTransitionTo(stateB[To]);
}


IntersectionIII::IntersectionIII(Movement& move, String name) : Intersection(move, name) {
    /*

                                A
                                |
                                |
                                |
                                |
                              /   \
                            /       \
                          /           \
                      B /       C       \ D
    */
	// This intersection CANNOT be approached from C
	// setup states To/From A
	stateA[To].setLeftTurn(Left135, stateB[To]);
	stateA[To].setRightTurn(Right135, stateD[To]);
	stateA[From].setApproach(FollowUntilSeparatingY);
	// setup states To/From B
	stateB[To].setLeftTurn(Left90, stateC[To]);
	stateB[To].setRightTurn(Right90, stateA[To]);
	stateB[From].setLeftTurn(Left45, stateA[To]);
	stateB[From].setRightTurn(Right90, stateD[To]);
	stateB[From].setApproach(FollowOnLeftUntilCrossesLine);
	// setup states To/From C
	stateC[To].setLeftTurn(Left90, stateD[To]);
	stateC[To].setRightTurn(Right90, stateB[To]);
	// setup states To/From D
	stateD[To].setLeftTurn(Left90, stateA[To]);
	stateD[To].setRightTurn(Right90, stateC[To]);
	stateD[From].setLeftTurn(Left90, stateB[To]);
	stateD[From].setRightTurn(Right45, stateA[To]);
	stateD[From].setApproach(FollowOnRightUntilCrossesLine);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateC[To]);
}


IntersectionIV::IntersectionIV(Movement& move, String name) : Intersection(move, name) {
    /*

                            A
                            |
                            |
                            |
                  B ----------------- D
                            
                            
                            
                            C
    */
	// This intersection CANNOT be approached from C
	// setup state To A
	stateA[To].setLeftTurn(Left90, stateB[To]);
	stateA[To].setRightTurn(Right90, stateD[To]);
	stateA[From].setApproach(FollowUntilPerpendicularLine);
	// setup state To B
	stateB[To].setLeftTurn(Left90, stateC[To]);
	stateB[To].setRightTurn(Right90, stateA[To]);
	stateB[From].setApproach(FollowOnLeftUntilPerpendicularLine);
	// setup state To C
	stateC[To].setLeftTurn(Left90, stateD[To]);
	stateC[To].setRightTurn(Right90, stateB[To]);
	// setup state To D
	stateD[To].setLeftTurn(Left90, stateA[To]);
	stateD[To].setRightTurn(Right90, stateC[To]);
	stateD[From].setApproach(FollowOnRightUntilPerpendicularLine);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateC[To]);
	stateC[From].setTransitionTo(stateA[To]);
	stateB[From].setTransitionTo(stateD[To]);
	stateD[From].setTransitionTo(stateB[To]);
}


IntersectionV::IntersectionV(Movement& move, String name) : Intersection(move, name) {
    /*

                            A
                            
                            
                            
                  B ----------------- D
                            
                            
                            
                            C
    */
	// setup state To A
	stateA[To].setLeftTurn(Left90, stateB[To]);
	stateA[To].setRightTurn(Right90, stateD[To]);
	stateA[From].setApproach(NoFollowUntilPerpendicularLine);
	// setup state To B
	stateB[To].setLeftTurn(Left90, stateC[To]);
	stateB[To].setRightTurn(Right90, stateA[To]);
	stateB[From].setApproach(FollowUntilPerpendicularLine);
	// setup state To C
	stateC[To].setLeftTurn(Left90, stateD[To]);
	stateC[To].setRightTurn(Right90, stateB[To]);
	stateC[From].setApproach(NoFollowUntilPerpendicularLine);
	// setup state To D
	stateD[To].setLeftTurn(Left90, stateA[To]);
	stateD[To].setRightTurn(Right90, stateC[To]);
	stateD[From].setApproach(FollowUntilPerpendicularLine);
	// set appropriate transitions
	stateA[From].setTransitionTo(stateC[To]);
	stateC[From].setTransitionTo(stateA[To]);
	stateB[From].setTransitionTo(stateD[To]);
	stateD[From].setTransitionTo(stateB[To]);
}
