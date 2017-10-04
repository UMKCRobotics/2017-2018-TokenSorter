#include "Navigation.h"

Intersection::Intersection(Movement& move) { 
	stateFromA = IntersectionState(move);
	stateToA = IntersectionState(move);
	stateFromB = IntersectionState(move);
	stateToB = IntersectionState(move);
	stateFromC = IntersectionState(move);
	stateToC = IntersectionState(move);
	stateFromD = IntersectionState(move);
	stateToD = IntersectionState(move);
	movement = &move;
}


IntersectionI::IntersectionI(Movement& move) : Intersection(move) {
	/*

							A
							|
							|
							|
				  			t
						  / | \
						/   |   \
					  / 	|     \
				  B /		C       \ D
	*/
	// setup states To/From A
	stateToA.setLeftTurn(Left135, stateToB);
	stateToA.setRightTurn(Right135, stateToD);
	stateFromA.setApproach(FollowUntilTokenSlot);
	// setup states To/From B
	stateToB.setLeftTurn(Left90, stateToC);
	stateToB.setRightTurn(Right90, stateToA);
	stateFromB.setLeftTurn(Left45, stateToA);
	stateFromB.setRightTurn(Right90, stateToD);
	stateFromB.setApproach(FollowUntilTokenSlot);
	// setup states To/From C
	stateToC.setLeftTurn(Left90, stateToD);
	stateToC.setRightTurn(Right90, stateToB);
	stateFromC.setApproach(FollowUntilTokenSlot);
	// setup states To/From D
	stateToD.setLeftTurn(Left90, stateToA);
	stateToD.setRightTurn(Right90, stateToC);
	stateFromD.setLeftTurn(Left90, stateToB);
	stateFromD.setRightTurn(Right45, stateToA);
	stateFromD.setApproach(FollowUntilTokenSlot);
	// set appropriate transitions
	stateFromA.setTransitionTo(stateToC);
	stateFromC.setTransitionTo(stateToA);
}


IntersectionII::IntersectionII(Movement& move) : Intersection(move) {
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
	stateToA.setLeftTurn(Left90, stateToB);
	stateToA.setRightTurn(Right90, stateToD);
	stateFromA.setApproach(FollowUntilTokenSlot);
	// setup state To B
	stateToB.setLeftTurn(Left90, stateToC);
	stateToB.setRightTurn(Right90, stateToA);
	stateFromB.setApproach(FollowUntilTokenSlot);
	// setup state To C
	stateToC.setLeftTurn(Left90, stateToD);
	stateToC.setRightTurn(Right90, stateToB);
	stateFromC.setApproach(FollowUntilTokenSlot);
	// setup state To D
	stateToD.setLeftTurn(Left90, stateToA);
	stateToD.setRightTurn(Right90, stateToC);
	stateFromD.setApproach(FollowUntilTokenSlot);
	// set appropriate transitions
	stateFromA.setTransitionTo(stateToC);
	stateFromC.setTransitionTo(stateToA);
	stateFromB.setTransitionTo(stateToD);
	stateFromD.setTransitionTo(stateToB);
}


IntersectionIII::IntersectionIII(Movement& move) : Intersection(move) {
	/*

							A
							|
							|
							|
				  			|
						  /   \
						/       \
					  / 	      \
				  B /		C       \ D
	*/
	// This intersection CANNOT be approached from C
	// setup states To/From A
	stateToA.setLeftTurn(Left135, stateToB);
	stateToA.setRightTurn(Right135, stateToD);
	stateFromA.setApproach(FollowUntilSeparatingY);
	// setup states To/From B
	stateToB.setLeftTurn(Left90, stateToC);
	stateToB.setRightTurn(Right90, stateToA);
	stateFromB.setLeftTurn(Left45, stateToA);
	stateFromB.setRightTurn(Right90, stateToD);
	stateFromB.setApproach(FollowOnLeftUntilCrossesLine);
	// setup states To/From C
	stateToC.setLeftTurn(Left90, stateToD);
	stateToC.setRightTurn(Right90, stateToB);
	// setup states To/From D
	stateToD.setLeftTurn(Left90, stateToA);
	stateToD.setRightTurn(Right90, stateToC);
	stateFromD.setLeftTurn(Left90, stateToB);
	stateFromD.setRightTurn(Right45, stateToA);
	stateFromD.setApproach(FollowOnRightUntilCrossesLine);
	// set appropriate transitions
	stateFromA.setTransitionTo(stateToC);
}


IntersectionIV::IntersectionIV(Movement& move) : Intersection(move) {
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
	stateToA.setLeftTurn(Left90, stateToB);
	stateToA.setRightTurn(Right90, stateToD);
	stateFromA.setApproach(FollowUntilPerpendicularLine);
	// setup state To B
	stateToB.setLeftTurn(Left90, stateToC);
	stateToB.setRightTurn(Right90, stateToA);
	stateFromB.setApproach(FollowOnLeftUntilPerpendicularLine);
	// setup state To C
	stateToC.setLeftTurn(Left90, stateToD);
	stateToC.setRightTurn(Right90, stateToB);
	// setup state To D
	stateToD.setLeftTurn(Left90, stateToA);
	stateToD.setRightTurn(Right90, stateToC);
	stateFromD.setApproach(FollowOnRightUntilPerpendicularLine);
	// set appropriate transitions
	stateFromA.setTransitionTo(stateToC);
	stateFromC.setTransitionTo(stateToA);
	stateFromB.setTransitionTo(stateToD);
	stateFromD.setTransitionTo(stateToB);
}


IntersectionV::IntersectionV(Movement& move) : Intersection(move) {
	/*

							A
							
							
							
				  B ----------------- D
							
							
							
							C
	*/
	// setup state To A
	stateToA.setLeftTurn(Left90, stateToB);
	stateToA.setRightTurn(Right90, stateToD);
	stateFromA.setApproach(NoFollowUntilPerpendicularLine);
	// setup state To B
	stateToB.setLeftTurn(Left90, stateToC);
	stateToB.setRightTurn(Right90, stateToA);
	stateFromB.setApproach(FollowUntilPerpendicularLine);
	// setup state To C
	stateToC.setLeftTurn(Left90, stateToD);
	stateToC.setRightTurn(Right90, stateToB);
	stateFromC.setApproach(NoFollowUntilPerpendicularLine);
	// setup state To D
	stateToD.setLeftTurn(Left90, stateToA);
	stateToD.setRightTurn(Right90, stateToC);
	stateFromD.setApproach(FollowUntilPerpendicularLine);
	// set appropriate transitions
	stateFromA.setTransitionTo(stateToC);
	stateFromC.setTransitionTo(stateToA);
	stateFromB.setTransitionTo(stateToD);
	stateFromD.setTransitionTo(stateToB);
}