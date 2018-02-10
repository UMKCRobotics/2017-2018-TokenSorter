#include "LineIntersection.h"

LineIntersection::LineIntersection()
{


}


LineIntersection::LineIntersection(int pin) {
	mySensorBar = new SensorBar(SX1509_ADDRESS);
	mySensorBar->clearBarStrobe();
	mySensorBar->clearInvertBits();
	mySensorBar->begin();
	//setLineByte();

	// set middlePin
	middlePin = pin;
}

//TODO: Add all different intersection types.

/*int8_t LineIntersection::checkIntersection()
{
	//intersection_count++;
	int8_t left_line, right_line;

	setLineByte(); //Update the values first.
	setLineDensity();
	if (line_density == 8){
		//Return that it is a horizontal.
	}
	else {
		left_line = determineHalf("left");
		right_line = determineHalf("right");
		setLineDensity(left_line + right_line);

		if (){ //The horizontal line is already accounted for, so this takes all other intersections with a left horizontal.
			//Return left (or default direction).
		}
		else if (){
			//
		}
		else {
			//
		}
	}
}

//NOTE: For diagonal lines, the sensor cannot differentiate between y=x and y=-x diagonals, so we will need a workaround.

int8_t LineIntersection::determineHalf(String left_or_right)
{
	int8_t sensor_line_count;
	if (left_or_right == "left"){
		sensor_line_count = countOnes(0, BYTE_SIZE/2);
	}
	else {
		sensor_line_count = countOnes(BYTE_SIZE/2, BYTE_SIZE);
	}

	//NOTE: It would be better to implement a switch statement here.
	switch (sensor_line_count) {
		case 0:
			return NO_LINE;
		case 1:
			return VERTICAL_LINE;
		case 2:
			return DIAGONAL_LINE;
		case 3:
			return VERT_AND_DIAG_LINE;
		case 4:
			return HORIZONTAL_LINE;
		default:
			return SENSOR_ERROR;
	}
}

void LineIntersection::setLineByte()
{
	line_byte = mySensorBar.getRaw(); //Gets the 8 values as a uint8_t (binary form).
	convertLineByteIntoArray();
}
*/
String LineIntersection::getArrayDataInString() {
	String lineData = "";
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		lineData += (bit_value ? ON_LINE : OFF_LINE);
	}
	return lineData;
}

bool LineIntersection::getMiddleState() {
	return analogRead(middlePin) >= middleThreshold;
}

int8_t LineIntersection::getArrayDataSum() {
	String line_data = getArrayDataInString();
	int8_t data_sum_vector = 0;
	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		/* Choose the most readable option. */
		// binary_value = (int8_t) line_data[i]
		// if (binary_value) {
		// 	data_sum_vector += binary_value * (i >= 4 ? 1 : -1)
		// }
		if (line_data[i] == ON_LINE && i >= 4) {
			data_sum_vector++;
		}
		else if (line_data[i] == ON_LINE) { // Implying that i <= 3.
			data_sum_vector--;
		}
	}
}


String LineIntersection::getFullArrayInString() {
	String lineData = "";
	density = 0;
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		/*if (bit_value) {
			lineData += 
		}*/
		lineData += (bit_value ? ON_LINE : OFF_LINE);
		density += bit_value;
		if (i == 4) {
			bool state = getMiddleState();
			lineData += (getMiddleState() ? ON_LINE : OFF_LINE);
			density += state;
		}

	}
	lastFullReading = lineData;
	return lineData;
}


int LineIntersection::getLinePosition(bool getNewData) {
	int position = 0;
	// get new data if requested
	if (getNewData) {
		getFullArrayInString();
	}
	if (lastFullReading[4] == ON_LINE) {
		// if on the line, only worry about closest two sensors
		if (lastFullReading[3] == ON_LINE) position -= 1;
		if (lastFullReading[5] == ON_LINE) position += 1;
	}
	else {
		// otherwise, worry about all
		if (lastFullReading[3] == ON_LINE || lastFullReading[5] == ON_LINE) {
			if (lastFullReading[3] == ON_LINE) position -= 4;
			if (lastFullReading[5] == ON_LINE) position += 4;
		}
		else if (lastFullReading[2] == ON_LINE || lastFullReading[6] == ON_LINE) {
			if (lastFullReading[2] == ON_LINE) position -= 8;
			if (lastFullReading[6] == ON_LINE) position += 8;
		}
		else if (lastFullReading[1] == ON_LINE || lastFullReading[7] == ON_LINE) {
			if (lastFullReading[1] == ON_LINE) position -= 12;
			if (lastFullReading[7] == ON_LINE) position += 12;
		}
		else if (lastFullReading[0] == ON_LINE || lastFullReading[8] == ON_LINE) {
			if (lastFullReading[0] == ON_LINE) position -= 16;
			if (lastFullReading[8] == ON_LINE) position += 16;
		}
		// remember last position if no IRs are on_line
		if (position == 0) {
			position = lastPosition;
		}
	}
	// set lastPosition to most recent position
	lastPosition = position;
	return lastPosition;
}


/*

void LineIntersection::setLineDensity(int8_t user_density = 0)
{
	if (user_density){
		line_density = user_density;
	}
	else {
	line_density = mySensorBar.getDensity();
	}
}

int8_t LineIntersection::countOnes(int8_t start, int8_t end) //Non-inclusive of end.
{
	int8_t ones_counter;
	ones_counter = 0;
	for (int8_t i = start; i < end; i++){
		if (line_byte_array[i] == 1){ones_counter++;}
	}
	return ones_counter;
}
*/
