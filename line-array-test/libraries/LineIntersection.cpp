//Originally contained more functions, but removed for simplicity.

#include "Wire.h"
#include "sensorbar.h"

#define BYTE_SIZE 8

#define NO_LINE -1
#define VERTICAL_LINE 0
#define DIAGONAL_LINE 1
#define HORIZONTAL_LINE 2
#define SENSOR_ERROR 99

const uint8_t SX1509_ADDRESS = /*Line array address needs to be defined*/;

class LineIntersection{
	private:
		//Class type pulled from example code.
		SensorBar mySensorBar(SX1509_ADDRESS);
		uint_8 line_byte;
		int line_byte_array[8];
		
		
	public:
		LineIntersection();
		int checkIntersection();
		int determineHalf(string left_or_right);
		int countOnes(int start, int end);
		void setLineByte();
		void convertLineByteIntoArray();
		//void bitwiseShiftByte(int); Replaced by convertLineByteIntoArray().
};

LineIntersection::LineIntersection()
{
	mySensorBar.clearBarStrobe();
	mySensorBar.clearInvertBits();
	mySensorBar.begin();
	setLineByte();
}

//NOTE: For diagonal lines, the sensor cannot differentiate between y=x and y=-x diagonals, so we will need a workaround.

int LineIntersection::determineHalf(string left_or_right)
{
	int sensor_line_count;
	if (left_or_right == "left"){
		sensor_line_count = countOnes(0, BYTE_SIZE/2);
	}
	else {
		sensor_line_count = countOnes(BYTE_SIZE/2, BYTE_SIZE);
	}
	
	//NOTE: It would be better to implement a switch statement here.
	if (sensor_line_count == 0){
		return NO_LINE;
	}
	else if (sensor_line_count == 2){
		return DIAGONAL_LINE; 
	}
	else if (sensor_line_count == 4){
		return HORIZONTAL_LINE; 
	}
	else if (sensor_line_count == 1){
		//TOFIX: This could be a diagonal or vertical line.
		//moveALittleBitForward() then call again to see if vertical or diagonal?
		return ;
	}
	else {
		return SENSOR_ERROR; //It is physically impossible for three sensors to be ones with 1.5" lines.
	}
}

//TODO: Add all different intersection types.

int LineIntersection::checkIntersection()
{
	setLineByte(); //Update the values first.
	int left_line, right_line;
	left_line = determineHalf("left");
	right_line = determineRightHalf("right");
	if (left_line == HORIZONTAL_LINE && right_line == HORIZONTAL_LINE){
		//This occurs when the robot first gets on the line.
	}
	else if (left_line == HORIZONTAL_LINE){
		//Return left (or default direction).
	}
	else if (){
		//
	}
	else {
		//
	}
}

void LineIntersection::setLineByte()
{
	line_byte = mySensorBar.getRaw(); //Gets the 8 values as a uint_8 (binary form).
	convertLineByteIntoArray();
}

void LineIntersection::convertLineByteIntoArray()
{
	uint_8 binary_array;
	int right_shift;
	for (int i = 0; i < BYTE_SIZE; i++){
		binary_array = line_byte;
		binary_array << i; //Remove anything to the left.
		binary_array >> (BYTE_SIZE - 1); //Move it all the way to the rightmost position.
		if (binary_array == 1){ //TOCHECK: This is the main part I am unsure of. Is the unsigned 8-bit int read as decimal in any non-bitwise operation? 
			line_byte_array[i] = 1;
		}
		else {
			line_byte_array[i] = 0;
		}
	}
}

int LineIntersection::countOnes(int start, int end) //Non-inclusive of end.
{
	int ones_counter;
	ones_counter = 0;
	for (int i = start; i < end; i++){
		if (line_byte_array[i] == 1){ones_counter++;}
	}
	return ones_counter;
}
