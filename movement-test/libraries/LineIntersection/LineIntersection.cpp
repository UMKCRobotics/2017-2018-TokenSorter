#include "LineIntersection.h"

LineIntersection::LineIntersection()
{
	mySensorBar = new SensorBar(SX1509_ADDRESS);
	mySensorBar->clearBarStrobe();
	mySensorBar->clearInvertBits();
	mySensorBar->begin();
	//setLineByte();
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
	String lineData = '';
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		// if (bit_value == 1){
		// 	lineData += "1";
		// }
		// else {
		// 	lineData += "0";
		// }
		lineData += (bit_value ? '1' : '0')
	}
	return lineData;
}

int8_t getArrayDataSum() {
	line_data = getArrayDataInString();
	int8_t data_sum_vector = 0;
	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		/* Choose the most readable option. */
		// binary_value = (int8_t) line_data[i]
		// if (binary_value) {
		// 	data_sum_vector += binary_value * (i >= 4 ? 1 : -1)
		// }
		if (line_data[i] == '1' && i >= 4) {
			data_sum_vector++;
		}
		else if (line_data[i] == '1') { // Implying that i <= 3.
			data_sum_vector--;
		}
	}
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
