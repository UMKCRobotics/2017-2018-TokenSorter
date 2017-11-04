#include "LineIntersection.h"

LineIntersection::LineIntersection()
{
	mySensorBar = new SensorBar(0x3E);
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
	String lineData = "";
	uint8_t binary_array;
	int8_t right_shift;
	//get data
	line_byte = mySensorBar->getRaw();
	
	for (int8_t i = 0; i < BYTE_SIZE; i++){
		binary_array = line_byte;
		binary_array << i; //Remove anything to the left.
		binary_array >> (BYTE_SIZE - 1); //Move it all the way to the rightmost position.
		if (binary_array == 1){ //TOCHECK: The unsigned 8-bit int8_t is read as decimal in any non-bitwise operation, correct?
			//line_byte_array[i] = 1;
			lineData += "1";
		}
		else {
			//line_byte_array[i] = 0;
			lineData += "0";
		}
	}
	return lineData;
}
/*
void LineIntersection::convertLineByteIntoArray()
{
	uint8_t binary_array;
	int8_t right_shift;
	for (int8_t i = 0; i < BYTE_SIZE; i++){
		binary_array = line_byte;
		binary_array << i; //Remove anything to the left.
		binary_array >> (BYTE_SIZE - 1); //Move it all the way to the rightmost position.
		if (binary_array == 1){ //TOCHECK: The unsigned 8-bit int8_t is read as decimal in any non-bitwise operation, correct?
			line_byte_array[i] = 1;
		}
		else {
			line_byte_array[i] = 0;
		}
	}
}

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