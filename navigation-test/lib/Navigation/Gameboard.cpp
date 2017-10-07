#include "Navigation.h"

Gameboard::Gameboard(int round_n, Movement& move) {
	round = round_n;
	movement = &move;

}

void Gameboard::initializeBoard() {
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
	// creating intersections for 2-foot square
	IntersectionII at2and0 = IntersectionII(movement, "2ft and 0deg");
	IntersectionI at2and45 = IntersectionI(movement, "2ft and 45deg");
	IntersectionI at2and135 = IntersectionI(movement, "2ft and 135deg");
	IntersectionII at2and180 = IntersectionII(movement, "2ft and 180deg");
	IntersectionI at2and225 = IntersectionI(movement, "2ft and 225deg");
	IntersectionI at2and315 = IntersectionI(movement, "2ft and 315deg");
	// creating intersections for 3-foot squate
	IntersectionII at3and0 = IntersectionII(movement, "3ft and 0deg");
	IntersectionI at3and45 = IntersectionI(movement, "3ft and 45deg");
	IntersectionI at3and135 = IntersectionI(movement, "3ft and 135deg");
	IntersectionII at3and180 = IntersectionII(movement, "3ft and 180deg");
	IntersectionI at3and225 = IntersectionI(movement, "3ft and 225deg");
	IntersectionI at3and315 = IntersectionI(movement, "3ft and 315deg");
	// creating intersections for 4-foot square
	IntersectionII at4and0 = IntersectionII(movement, "4ft and 0deg");
	IntersectionI at4and45 = IntersectionI(movement, "4ft and 45deg");
	IntersectionV at4and90 = IntersectionV(movement, "4ft and 90deg");
	IntersectionI at4and135 = IntersectionI(movement, "4ft and 135deg");
	IntersectionII at4and180 = IntersectionII(movement, "4ft and 180deg");
	IntersectionI at4and225 = IntersectionI(movement, "4ft and 225deg");
	IntersectionV at4and270 = IntersectionV(movement, "4ft and 270deg");
	IntersectionI at4and315 = IntersectionI(movement, "4ft and 315deg");
	// creating intersections for 5-foot square
	IntersectionII at5and0 = IntersectionII(movement, "5ft and 0deg");
	IntersectionI at5and45 = IntersectionI(movement, "5ft and 45deg");
	IntersectionV at5and90 = IntersectionV(movement, "5ft and 90deg");
	IntersectionI at5and135 = IntersectionI(movement, "5ft and 135deg");
	IntersectionII at5and180 = IntersectionII(movement, "5ft and 180deg");
	IntersectionI at5and225 = IntersectionI(movement, "5ft and 225deg");
	IntersectionV at5and270 = IntersectionV(movement, "5ft and 270deg");
	IntersectionI at5and315 = IntersectionI(movement, "5ft and 315deg");
	// creating intersections for outer squares
	IntersectionIV atOuterand0 = IntersectionIV(movement, "Outer and 0deg");
	IntersectionIII atOuterand45 = IntersectionIII(movement, "Outer and 45deg");
	IntersectionV atOuterand90 = IntersectionV(movement, "Outer and 90deg");
	IntersectionIII atOuterand135 = IntersectionIII(movement, "Outer and 135deg");
	IntersectionIV atOuterand180 = IntersectionIV(movement, "Outer and 180deg");
	IntersectionIII atOuterand225 = IntersectionIII(movement, "Outer and 225deg");
	IntersectionV atOuterand270 = IntersectionV(movement, "Outer and 270deg");
	IntersectionIII atOuterand315 = IntersectionIII(movement, "Outer and 315deg");
	// creating drop token + start intersections for outer squares
	IntersectionDropToken dropOuterand0 = IntersectionDropToken(movement, "Outer drop and 0deg");
	IntersectionDropToken dropOuterand45 = IntersectionDropToken(movement, "Outer drop and 45deg");
	IntersectionStart dropOuterand90 = IntersectionStart(movement, "Start and 90deg");
	IntersectionDropToken dropOuterand135 = IntersectionDropToken(movement, "Outer drop and 135deg");
	IntersectionDropToken dropOuterand180 = IntersectionDropToken(movement, "Outer drop and 180deg");
	IntersectionDropToken dropOuterand225 = IntersectionDropToken(movement, "Outer drop and 225deg");
	IntersectionStart dropOuterand270 = IntersectionStart(movement, "Start and 270deg");
	IntersectionDropToken dropOuterand315 = IntersectionDropToken(movement, "Outer drop and 315deg");

	// CONNECTIONS
	// connect middle drop intersections to corresponding 1-foot square intersections
	at1and0.createBackwardConnectionUsingStateC(dropMiddleand0.getStateA());
	at1and45.createBackwardConnectionUsingStateC(dropMiddleand45.getStateA());
	at1and135.createBackwardConnectionUsingStateC(dropMiddleand135.getStateA());
	at1and180.createBackwardConnectionUsingStateC(dropMiddleand180.getStateA());
	at1and225.createBackwardConnectionUsingStateC(dropMiddleand225.getStateA());
	at1and315.createBackwardConnectionUsingStateC(dropMiddleand315.getStateA());
	// connect 1-foot square intersections together
	at1and0.createConnectionUsingStateB(at1and45.getStateD());
	at1and45.createConnectionUsingStateB(at1and135.getStateD());
	at1and135.createConnectionUsingStateB(at1and180.getStateD());
	at1and180.createConnectionUsingStateB(at1and225.getStateD());
	at1and225.createConnectionUsingStateB(at1and315.getStateD());
	at1and315.createConnectionUsingStateD(at1and0.getStateB());
	// connect 2-foot square intersections together
	at2and0.createConnectionUsingStateB(at2and45.getStateD());
	at2and45.createConnectionUsingStateB(at2and135.getStateD());
	at2and135.createConnectionUsingStateB(at2and180.getStateD());
	at2and180.createConnectionUsingStateB(at2and225.getStateD());
	at2and225.createConnectionUsingStateB(at2and315.getStateD());
	at2and315.createConnectionUsingStateD(at2and0.getStateB());
	// connect 3-foot square intersections together
	at3and0.createConnectionUsingStateB(at3and45.getStateD());
	at3and45.createConnectionUsingStateB(at3and135.getStateD());
	at3and135.createConnectionUsingStateB(at3and180.getStateD());
	at3and180.createConnectionUsingStateB(at3and225.getStateD());
	at3and225.createConnectionUsingStateB(at3and315.getStateD());
	at3and315.createConnectionUsingStateD(at3and0.getStateB());
	// connect 4-foot square intersections together
	at4and0.createConnectionUsingStateB(at4and45.getStateD());
	at4and45.createConnectionUsingStateB(at4and90.getStateD());
	at4and90.createConnectionUsingStateB(at4and135.getStateD());
	at4and135.createConnectionUsingStateB(at4and180.getStateD());
	at4and180.createConnectionUsingStateB(at4and225.getStateD());
	at4and225.createConnectionUsingStateB(at4and270.getStateD());
	at4and270.createConnectionUsingStateB(at4and315.getStateD());
	at4and315.createConnectionUsingStateD(at4and0.getStateB());
	// connect 5-foot square intersections together
	at5and0.createConnectionUsingStateB(at5and45.getStateD());
	at5and45.createConnectionUsingStateB(at5and90.getStateD());
	at5and90.createConnectionUsingStateB(at5and135.getStateD());
	at5and135.createConnectionUsingStateB(at5and180.getStateD());
	at5and180.createConnectionUsingStateB(at5and225.getStateD());
	at5and225.createConnectionUsingStateB(at5and270.getStateD());
	at5and270.createConnectionUsingStateB(at5and315.getStateD());
	at5and315.createConnectionUsingStateD(at5and0.getStateB());
}