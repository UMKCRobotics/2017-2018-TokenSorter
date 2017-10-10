#include "Navigation.h"
#include "Movement.h"





Movement robotMovement = Movement();
Navigation navigation = Navigation(1, robotMovement);


// input parsing
const int maxValues = 2;
String command; // general command
String values[maxValues]; // stores values for command
String response; // response returned to main program


void setup() {
	Serial.begin(115200);
	String statename = navigation.getCurrentStateInfo();
	Serial.println("PRGM BEGIN");
	Serial.println(statename);
}

void loop() {
	
	if(Serial.available()){

		int addTo = 0; // 0 for command, 1 for value

		while (Serial.available() > 0)
		{
			char readIn = (char)Serial.read();
			if (readIn == '\n') {
				break;
			}
			else if (readIn == '|') {
				addTo += 1;
				continue;
			}
			// add to command if no | reached yet
			if (addTo == 0) {
				command += readIn;
			}
			// add to proper value in array
			else if (addTo <= maxValues) {
				values[addTo-1] += readIn;
			}
			// if values exceed max, then stop listening to prevent problems
			else {
				break;
			}
			delayMicroseconds(31);
		}
		//clear anything remaining in serial
		while (Serial.available() > 0) {
			Serial.read();
		}
		response = interpretCommand();
		Serial.println(response); //sends response with \n at the end
		// empty out command and value strings
		command = "";
		for (int i = 0; i < maxValues; i++) {
			values[i] = "";
		}
	}
	delay(2);
}

String interpretCommand() {
	String responseString = "n";  // string to be sent to main program
	String returnString = "";     // string received from a subfunction

	// determine what to do:
	
	// check if movement command
	if (command == "l") {
		// check if actually turned left
		if (navigation.turnLeft()) {
			responseString = navigation.getCurrentStateInfo();
		}
		else {
			responseString = "Can't turn left here";
		}
	}
	else if (command == "r") {
		if (navigation.turnRight()) {
			responseString = navigation.getCurrentStateInfo();
		}
		else {
			responseString = "Can't turn right here";
		}
	}
	else if (command == "f") {
		if (navigation.goForward()) {
			responseString = navigation.getCurrentStateInfo();
		}
		else {
			responseString = "Can't go forward here";
		}
	}
	else if (command == "b") {
		if (navigation.goBackward()) {
			responseString = navigation.getCurrentStateInfo();
		}
		else {
			responseString = "Can't go backward here";
		}
	}
	// check if mode-setting command
	// TODO: add functionality to STREAMOUT
	else if (command == "SYNCOUT") {
		responseString = "1";
	}
	else if (command == "STREAMOUT") {
		responseString = "1";
	}
	else {
		responseString = command;
	}

	responseString += returnString;
	return responseString;
}