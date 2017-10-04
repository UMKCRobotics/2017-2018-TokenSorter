#include "Navigation.h"


IntersectionI::IntersectionI(Movement& move) : Intersection(move) {
	/*

							A
							|
							|
							|
				  			|
						  / | \
						/   |   \
					  / 	|     \
				  B /		C       \ D
	*/
	stateA = IntersectionState(move);
	stateB = IntersectionState(move);
	stateToCenterFromB = IntersectionState(move);
	stateC = IntersectionState(move);
	stateD = IntersectionState(move);
	stateToCenterFromD = IntersectionState(move);
	// setup state A
	stateA.setLeftTurn(Left135, stateB);
	stateA.setRightTurn(Right135, stateD);
	stateA.setApproach(FollowUntilSeparatingY);
	// setup state B
	stateB.setLeftTurn(Left90, stateC);
	stateB.setRightTurn(Right90, stateA);
	stateB.setApproach(FollowUntilPerpendicularLine);
	// setup state B (facing towards center)
	stateToCenterFromB.setLeftTurn(Left90, stateC);
	stateToCenterFromB.setRightTurn(Right90, stateA);
	stateToCenterFromB.setApproach(FollowUntilPerpendicularLine);
	// setup state C
	stateC.setLeftTurn(Left90, stateD);
	stateC.setRightTurn(Right90, stateB);
	stateC.setApproach(FollowUntilPerpendicularLine);
	// setup state D
	stateD.setLeftTurn(Left90, stateA);
	stateD.setRightTurn(Right90, stateC);
	stateD.setApproach(FollowUntilPerpendicularLine);
	// setup state D (facing towards center)
	stateToCenterFromD.setLeftTurn(Left90, stateC);
	stateToCenterFromD.setRightTurn(Right90, stateA);
	stateToCenterFromD.setApproach(FollowUntilPerpendicularLine);
}


IntersectionII::IntersectionII(Movement& move) : Intersection(move) {
	/*

							A
							|
							|
							|
				  B ----------------- D
							|
							|
							|
							C
	*/
	stateA = IntersectionState(move);
	stateB = IntersectionState(move);
	stateC = IntersectionState(move);
	stateD = IntersectionState(move);
	// setup state A
	stateA.setLeftTurn(Left90, stateB);
	stateA.setRightTurn(Right90, stateD);
	stateA.setApproach(FollowUntilPerpendicularLine);
	// setup state B
	stateB.setLeftTurn(Left90, stateC);
	stateB.setRightTurn(Right90, stateA);
	stateB.setApproach(FollowUntilPerpendicularLine);
	// setup state C
	stateC.setLeftTurn(Left90, stateD);
	stateC.setRightTurn(Right90, stateB);
	stateC.setApproach(FollowUntilPerpendicularLine);
	// setup state D
	stateD.setLeftTurn(Left90, stateA);
	stateD.setRightTurn(Right90, stateC);
	stateD.setApproach(FollowUntilPerpendicularLine);
}


IntersectionV::IntersectionV(Movement& move) : Intersection(move) {
	/*

							A
							
							
							
				  B ----------------- D
							
							
							
							C
	*/
	stateA = IntersectionState(move);
	stateB = IntersectionState(move);
	stateC = IntersectionState(move);
	stateD = IntersectionState(move);
	// setup state A
	stateA.setLeftTurn(Left90, stateB);
	stateA.setRightTurn(Right90, stateD);
	stateA.setApproach(NoFollowUntilPerpendicularLine);
	// setup state B
	stateB.setLeftTurn(Left90, stateC);
	stateB.setRightTurn(Right90, stateA);
	stateB.setApproach(FollowUntilPerpendicularLine);
	// setup state C
	stateC.setLeftTurn(Left90, stateD);
	stateC.setRightTurn(Right90, stateB);
	stateC.setApproach(NoFollowUntilPerpendicularLine);
	// setup state D
	stateD.setLeftTurn(Left90, stateA);
	stateD.setRightTurn(Right90, stateC);
	stateD.setApproach(FollowUntilPerpendicularLine);
}