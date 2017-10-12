#include "Gameboard.h"


Gameboard::Gameboard(int round_n, Movement* move)
{
	round = round_n;
	movement = move;
	//initializeBoard();
	IntersectionStart* start = new IntersectionStart(movement, "test intersection");
	startState = start->getStateA()->To;
	IntersectionState* somestate = testInit();
	//IntersectionState* somestate2 = testInit();
}


IntersectionState* Gameboard::testInit() {
	// creating middle drop token intersections
	IntersectionDropToken dropMiddleand0 = IntersectionDropToken(movement, "Middle drop and  0deg");
	IntersectionDropToken dropMiddleand45 = IntersectionDropToken(movement, "Middle drop and  45deg");
	IntersectionDropToken dropMiddleand135 = IntersectionDropToken(movement, "Middle drop and  135deg");
	IntersectionDropToken dropMiddleand180 = IntersectionDropToken(movement, "Middle drop and  180deg");
	IntersectionDropToken dropMiddleand225 = IntersectionDropToken(movement, "Middle drop and  225deg");
	IntersectionDropToken dropMiddleand315 = IntersectionDropToken(movement, "Middle drop and  315deg");
	// creating intersections for 1-foot square
	IntersectionIV at1and0 = IntersectionIV(movement, "1ft and 0deg");
	IntersectionIII at1and45 = IntersectionIII(movement, "1ft and 45deg");
	IntersectionIII at1and135 = IntersectionIII(movement, "1ft and 135deg");
	IntersectionIV at1and180 = IntersectionIV(movement, "1ft and 180deg");
	IntersectionIII at1and225 = IntersectionIII(movement, "1ft and 225deg");
	IntersectionIII at1and315 = IntersectionIII(movement, "1ft and 315deg");
	IntersectionI at2and0 = IntersectionI(movement, "2ft and 0deg");

	// CONNECTIONS

	/* Connecting intersections within same squares */
	// connect 1-foot square intersections together
	at1and0.createConnectionUsingStateB(at1and45.getStateD());
	at1and45.createConnectionUsingStateB(at1and135.getStateD());
	at1and135.createConnectionUsingStateB(at1and180.getStateD());
	at1and180.createConnectionUsingStateB(at1and225.getStateD());
	at1and225.createConnectionUsingStateB(at1and315.getStateD());
	at1and315.createConnectionUsingStateB(at1and0.getStateD());

	return at1and0.getStateA()->To;

	/*
	// creating intersections for 2-foot square
	IntersectionI* at2and0 = new IntersectionI(movement, "2ft and 0deg");
	IntersectionI* at2and45 = new IntersectionI(movement, "2ft and 45deg");
	IntersectionI* at2and135 = new IntersectionI(movement, "2ft and 135deg");
	IntersectionII* at2and180 = new IntersectionII(movement, "2ft and 180deg");
	IntersectionI* at2and225 = new IntersectionI(movement, "2ft and 225deg");
	IntersectionI* at2and315 = new IntersectionI(movement, "2ft and 315deg");
	// creating intersections for 3-foot squate
	IntersectionII* at3and0 = new IntersectionII(movement, "3ft and 0deg");
	IntersectionI* at3and45 = new IntersectionI(movement, "3ft and 45deg");
	IntersectionI* at3and135 = new IntersectionI(movement, "3ft and 135deg");
	IntersectionII* at3and180 = new IntersectionII(movement, "3ft and 180deg");
	IntersectionI* at3and225 = new IntersectionI(movement, "3ft and 225deg");
	IntersectionI* at3and315 = new IntersectionI(movement, "3ft and 315deg");
	// creating intersections for 4-foot square
	IntersectionII* at4and0 = new IntersectionII(movement, "4ft and 0deg");
	IntersectionI* at4and45 = new IntersectionI(movement, "4ft and 45deg");
	IntersectionV* at4and90 = new IntersectionV(movement, "4ft and 90deg");
	IntersectionI* at4and135 = new IntersectionI(movement, "4ft and 135deg");
	IntersectionII* at4and180 = new IntersectionII(movement, "4ft and 180deg");
	IntersectionI* at4and225 = new IntersectionI(movement, "4ft and 225deg");
	IntersectionV* at4and270 = new IntersectionV(movement, "4ft and 270deg");
	IntersectionI* at4and315 = new IntersectionI(movement, "4ft and 315deg");
	// creating intersections for 5-foot square
	IntersectionII* at5and0 = new IntersectionII(movement, "5ft and 0deg");
	IntersectionI* at5and45 = new IntersectionI(movement, "5ft and 45deg");
	IntersectionV* at5and90 = new IntersectionV(movement, "5ft and 90deg");
	IntersectionI* at5and135 = new IntersectionI(movement, "5ft and 135deg");
	IntersectionII* at5and180 = new IntersectionII(movement, "5ft and 180deg");
	IntersectionI* at5and225 = new IntersectionI(movement, "5ft and 225deg");
	IntersectionV* at5and270 = new IntersectionV(movement, "5ft and 270deg");
	IntersectionI* at5and315 = new IntersectionI(movement, "5ft and 315deg");
	// creating intersections for outer squares
	IntersectionIV* atOuterand0 = new IntersectionIV(movement, "Outer and 0deg");
	IntersectionIII* atOuterand45 = new IntersectionIII(movement, "Outer and 45deg");
	IntersectionV* atOuterand90 = new IntersectionV(movement, "Outer and 90deg");
	IntersectionIII* atOuterand135 = new IntersectionIII(movement, "Outer and 135deg");
	IntersectionIV* atOuterand180 = new IntersectionIV(movement, "Outer and 180deg");
	IntersectionIII* atOuterand225 = new IntersectionIII(movement, "Outer and 225deg");
	IntersectionV* atOuterand270 = new IntersectionV(movement, "Outer and 270deg");
	IntersectionIII* atOuterand315 = new IntersectionIII(movement, "Outer and 315deg");
	// creating drop token + start intersections for outer squares
	IntersectionDropToken* dropOuterand0 = new IntersectionDropToken(movement, "Outer drop and 0deg");
	IntersectionDropToken* dropOuterand45 = new IntersectionDropToken(movement, "Outer drop and 45deg");
	IntersectionStart* dropOuterand90 = new IntersectionStart(movement, "Start and 90deg");
	IntersectionDropToken* dropOuterand135 = new IntersectionDropToken(movement, "Outer drop and 135deg");
	IntersectionDropToken* dropOuterand180 = new IntersectionDropToken(movement, "Outer drop and 180deg");
	IntersectionDropToken* dropOuterand225 = new IntersectionDropToken(movement, "Outer drop and 225deg");
	IntersectionStart* dropOuterand270 = new IntersectionStart(movement, "Start and 270deg");
	IntersectionDropToken* dropOuterand315 = new IntersectionDropToken(movement, "Outer drop and 315deg");*/

}


void Gameboard::initializeBoard() {
	// creating middle drop token intersections
	IntersectionDropToken* dropMiddleand0 = new IntersectionDropToken(movement, "Middle drop and  0deg");
	IntersectionDropToken* dropMiddleand45 = new IntersectionDropToken(movement, "Middle drop and  45deg");
	IntersectionDropToken* dropMiddleand135 = new IntersectionDropToken(movement, "Middle drop and  135deg");
	IntersectionDropToken* dropMiddleand180 = new IntersectionDropToken(movement, "Middle drop and  180deg");
	IntersectionDropToken* dropMiddleand225 = new IntersectionDropToken(movement, "Middle drop and  225deg");
	IntersectionDropToken* dropMiddleand315 = new IntersectionDropToken(movement, "Middle drop and  315deg");
	// creating intersections for 1-foot square
	IntersectionIV* at1and0 = new IntersectionIV(movement, "1ft and 0deg");
	IntersectionIII* at1and45 = new IntersectionIII(movement, "1ft and 45deg");
	IntersectionIII* at1and135 = new IntersectionIII(movement, "1ft and 135deg");
	IntersectionIV* at1and180 = new IntersectionIV(movement, "1ft and 180deg");
	IntersectionIII* at1and225 = new IntersectionIII(movement, "1ft and 225deg");
	IntersectionIII* at1and315 = new IntersectionIII(movement, "1ft and 315deg");
	// creating intersections for 2-foot square
	IntersectionII* at2and0 = new IntersectionII(movement, "2ft and 0deg");
	IntersectionI* at2and45 = new IntersectionI(movement, "2ft and 45deg");
	IntersectionI* at2and135 = new IntersectionI(movement, "2ft and 135deg");
	IntersectionII* at2and180 = new IntersectionII(movement, "2ft and 180deg");
	IntersectionI* at2and225 = new IntersectionI(movement, "2ft and 225deg");
	IntersectionI* at2and315 = new IntersectionI(movement, "2ft and 315deg");
	// creating intersections for 3-foot squate
	IntersectionII* at3and0 = new IntersectionII(movement, "3ft and 0deg");
	IntersectionI* at3and45 = new IntersectionI(movement, "3ft and 45deg");
	IntersectionI* at3and135 = new IntersectionI(movement, "3ft and 135deg");
	IntersectionII* at3and180 = new IntersectionII(movement, "3ft and 180deg");
	IntersectionI* at3and225 = new IntersectionI(movement, "3ft and 225deg");
	IntersectionI* at3and315 = new IntersectionI(movement, "3ft and 315deg");
	// creating intersections for 4-foot square
	IntersectionII* at4and0 = new IntersectionII(movement, "4ft and 0deg");
	IntersectionI* at4and45 = new IntersectionI(movement, "4ft and 45deg");
	IntersectionV* at4and90 = new IntersectionV(movement, "4ft and 90deg");
	IntersectionI* at4and135 = new IntersectionI(movement, "4ft and 135deg");
	IntersectionII* at4and180 = new IntersectionII(movement, "4ft and 180deg");
	IntersectionI* at4and225 = new IntersectionI(movement, "4ft and 225deg");
	IntersectionV* at4and270 = new IntersectionV(movement, "4ft and 270deg");
	IntersectionI* at4and315 = new IntersectionI(movement, "4ft and 315deg");
	// creating intersections for 5-foot square
	IntersectionII* at5and0 = new IntersectionII(movement, "5ft and 0deg");
	IntersectionI* at5and45 = new IntersectionI(movement, "5ft and 45deg");
	IntersectionV* at5and90 = new IntersectionV(movement, "5ft and 90deg");
	IntersectionI* at5and135 = new IntersectionI(movement, "5ft and 135deg");
	IntersectionII* at5and180 = new IntersectionII(movement, "5ft and 180deg");
	IntersectionI* at5and225 = new IntersectionI(movement, "5ft and 225deg");
	IntersectionV* at5and270 = new IntersectionV(movement, "5ft and 270deg");
	IntersectionI* at5and315 = new IntersectionI(movement, "5ft and 315deg");
	// creating intersections for outer squares
	IntersectionIV* atOuterand0 = new IntersectionIV(movement, "Outer and 0deg");
	IntersectionIII* atOuterand45 = new IntersectionIII(movement, "Outer and 45deg");
	IntersectionV* atOuterand90 = new IntersectionV(movement, "Outer and 90deg");
	IntersectionIII* atOuterand135 = new IntersectionIII(movement, "Outer and 135deg");
	IntersectionIV* atOuterand180 = new IntersectionIV(movement, "Outer and 180deg");
	IntersectionIII* atOuterand225 = new IntersectionIII(movement, "Outer and 225deg");
	IntersectionV* atOuterand270 = new IntersectionV(movement, "Outer and 270deg");
	IntersectionIII* atOuterand315 = new IntersectionIII(movement, "Outer and 315deg");
	// creating drop token + start intersections for outer squares
	IntersectionDropToken* dropOuterand0 = new IntersectionDropToken(movement, "Outer drop and 0deg");
	IntersectionDropToken* dropOuterand45 = new IntersectionDropToken(movement, "Outer drop and 45deg");
	IntersectionStart* dropOuterand90 = new IntersectionStart(movement, "Start and 90deg");
	IntersectionDropToken* dropOuterand135 = new IntersectionDropToken(movement, "Outer drop and 135deg");
	IntersectionDropToken* dropOuterand180 = new IntersectionDropToken(movement, "Outer drop and 180deg");
	IntersectionDropToken* dropOuterand225 = new IntersectionDropToken(movement, "Outer drop and 225deg");
	IntersectionStart* dropOuterand270 = new IntersectionStart(movement, "Start and 270deg");
	IntersectionDropToken* dropOuterand315 = new IntersectionDropToken(movement, "Outer drop and 315deg");

	// CONNECTIONS

	/* Connecting intersections within same squares */
	// connect 1-foot square intersections together
	at1and0->createConnectionUsingStateB(at1and45->getStateD());
	at1and45->createConnectionUsingStateB(at1and135->getStateD());
	at1and135->createConnectionUsingStateB(at1and180->getStateD());
	at1and180->createConnectionUsingStateB(at1and225->getStateD());
	at1and225->createConnectionUsingStateB(at1and315->getStateD());
	at1and315->createConnectionUsingStateB(at1and0->getStateD());
	// connect 2-foot square intersections together
	at2and0->createConnectionUsingStateB(at2and45->getStateD());
	at2and45->createConnectionUsingStateB(at2and135->getStateD());
	at2and135->createConnectionUsingStateB(at2and180->getStateD());
	at2and180->createConnectionUsingStateB(at2and225->getStateD());
	at2and225->createConnectionUsingStateB(at2and315->getStateD());
	at2and315->createConnectionUsingStateB(at2and0->getStateD());
	// connect 3-foot square intersections together
	at3and0->createConnectionUsingStateB(at3and45->getStateD());
	at3and45->createConnectionUsingStateB(at3and135->getStateD());
	at3and135->createConnectionUsingStateB(at3and180->getStateD());
	at3and180->createConnectionUsingStateB(at3and225->getStateD());
	at3and225->createConnectionUsingStateB(at3and315->getStateD());
	at3and315->createConnectionUsingStateB(at3and0->getStateD());
	// connect 4-foot square intersections together
	at4and0->createConnectionUsingStateB(at4and45->getStateD());
	at4and45->createConnectionUsingStateB(at4and90->getStateD());
	at4and90->createConnectionUsingStateB(at4and135->getStateD());
	at4and135->createConnectionUsingStateB(at4and180->getStateD());
	at4and180->createConnectionUsingStateB(at4and225->getStateD());
	at4and225->createConnectionUsingStateB(at4and270->getStateD());
	at4and270->createConnectionUsingStateB(at4and315->getStateD());
	at4and315->createConnectionUsingStateB(at4and0->getStateD());
	// connect 5-foot square intersections together
	at5and0->createConnectionUsingStateB(at5and45->getStateD());
	at5and45->createConnectionUsingStateB(at5and90->getStateD());
	at5and90->createConnectionUsingStateB(at5and135->getStateD());
	at5and135->createConnectionUsingStateB(at5and180->getStateD());
	at5and180->createConnectionUsingStateB(at5and225->getStateD());
	at5and225->createConnectionUsingStateB(at5and270->getStateD());
	at5and270->createConnectionUsingStateB(at5and315->getStateD());
	at5and315->createConnectionUsingStateB(at5and0->getStateD());

	/* Connecting intersections on different squares */
	// **connect middle drop intersections to corresponding 1-foot square intersections
	at1and0->createBackwardConnectionUsingStateC(dropMiddleand0->getStateA());
	at1and45->createBackwardConnectionUsingStateC(dropMiddleand45->getStateA());
	at1and135->createBackwardConnectionUsingStateC(dropMiddleand135->getStateA());
	at1and180->createBackwardConnectionUsingStateC(dropMiddleand180->getStateA());
	at1and225->createBackwardConnectionUsingStateC(dropMiddleand225->getStateA());
	at1and315->createBackwardConnectionUsingStateC(dropMiddleand315->getStateA());
	// **connect 1-foot square to 2-foot square
	at1and0->createConnectionUsingStateA(at2and0->getStateC());
	at1and45->createConnectionUsingStateA(at2and45->getStateC());
	at1and135->createConnectionUsingStateA(at2and135->getStateC());
	at1and180->createConnectionUsingStateA(at2and180->getStateC());
	at1and225->createConnectionUsingStateA(at2and225->getStateC());
	at1and315->createConnectionUsingStateA(at2and315->getStateC());
	// **create backward connections
	at2and0->createBackwardConnectionUsingStateC(at1and0->getStateA());
	at2and45->createBackwardConnectionUsingStateC(at1and45->getStateA());
	at2and135->createBackwardConnectionUsingStateC(at1and135->getStateA());
	at2and180->createBackwardConnectionUsingStateC(at1and180->getStateA());
	at2and225->createBackwardConnectionUsingStateC(at1and225->getStateA());
	at2and315->createBackwardConnectionUsingStateC(at1and315->getStateA());

	// **connect 2-foot square to 3-foot square
	at2and0->createConnectionUsingStateA(at3and0->getStateC());
	at2and45->createConnectionUsingStateA(at3and45->getStateC());
	at2and135->createConnectionUsingStateA(at3and135->getStateC());
	at2and180->createConnectionUsingStateA(at3and180->getStateC());
	at2and225->createConnectionUsingStateA(at3and225->getStateC());
	at2and315->createConnectionUsingStateA(at3and315->getStateC());
	// **connect 3-foot square to 4-foot square
	at3and0->createConnectionUsingStateA(at4and0->getStateC());
	at3and45->createConnectionUsingStateA(at4and45->getStateC());
	at3and135->createConnectionUsingStateA(at4and135->getStateC());
	at3and180->createConnectionUsingStateA(at4and180->getStateC());
	at3and225->createConnectionUsingStateA(at4and225->getStateC());
	at3and315->createConnectionUsingStateA(at4and315->getStateC());
	// **connect 4-foot square to 5-foot square
	at4and0->createConnectionUsingStateA(at5and0->getStateC());
	at4and45->createConnectionUsingStateA(at5and45->getStateC());
	at4and90->createConnectionUsingStateA(at5and90->getStateC());
	at4and135->createConnectionUsingStateA(at5and135->getStateC());
	at4and180->createConnectionUsingStateA(at5and180->getStateC());
	at4and225->createConnectionUsingStateA(at5and225->getStateC());
	at4and270->createConnectionUsingStateA(at5and270->getStateC());
	at4and315->createConnectionUsingStateA(at5and315->getStateC());
	// **connect outer intersections to 5-foot square
	at5and0->createBackwardConnectionUsingStateA(atOuterand0->getStateA());
	at5and45->createBackwardConnectionUsingStateA(atOuterand45->getStateA());
	at5and90->createConnectionUsingStateA(atOuterand90->getStateC());
	at5and135->createBackwardConnectionUsingStateA(atOuterand135->getStateA());
	at5and180->createBackwardConnectionUsingStateA(atOuterand180->getStateA());
	at5and225->createBackwardConnectionUsingStateA(atOuterand225->getStateA());
	at5and270->createConnectionUsingStateA(atOuterand270->getStateC());
	at5and315->createBackwardConnectionUsingStateA(atOuterand315->getStateA());
	// **connect outer drop and start intersections to outer intersections
	atOuterand0->createBackwardConnectionUsingStateC(dropOuterand0->getStateA());
	atOuterand45->createBackwardConnectionUsingStateC(dropOuterand45->getStateA());
	atOuterand90->createConnectionUsingStateA(dropOuterand90->getStateA());
	atOuterand135->createBackwardConnectionUsingStateC(dropOuterand135->getStateA());
	atOuterand180->createBackwardConnectionUsingStateC(dropOuterand180->getStateA());
	atOuterand225->createBackwardConnectionUsingStateC(dropOuterand225->getStateA());
	atOuterand270->createConnectionUsingStateA(dropOuterand270->getStateA());
	atOuterand315->createBackwardConnectionUsingStateC(dropOuterand315->getStateA());

	// set a start state for the gameboard (going "To" A from center)
	startState = dropOuterand270->getStateA()->To;
}


Gameboard::~Gameboard()
{
}
