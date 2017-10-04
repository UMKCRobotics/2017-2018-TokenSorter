#include "Navigation.h"
#include "Movement.h"





Movement robotMovement = Movement();



// input parsing
const int maxValues = 2;
String command; // general command
String values[maxValues]; // stores values for command
String response; // response returned to main program


void setup() {
	Serial.begin(115200);
	Serial.write(1);
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
	
	// check if movement command - make sure length is okay
	if (command == "l") {
		responseString = "1";
	}
	else if (command == "r") {
		responseString = "1";
	}
	else if (command == "f") {
		responseString = "1";
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