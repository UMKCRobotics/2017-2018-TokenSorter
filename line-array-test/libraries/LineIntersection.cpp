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
		int line_density;
		//int intersection_counter;
		
		
	public:
		LineIntersection();
		int checkIntersection();
		int determineHalf(string left_or_right);
		int countOnes(int start, int end);
		void setLineDensity();
		void setLineByte();
		void convertLineByteIntoArray();
};

LineIntersection::LineIntersection()
{
	mySensorBar.clearBarStrobe();
	mySensorBar.clearInvertBits();
	mySensorBar.begin();
	setLineByte();
}

//TODO: Add all different intersection types.

int LineIntersection::checkIntersection()
{
	//intersection_count++;
	int left_line, right_line;
	
	setLineByte(); //Update the values first.
	setLineDensity();
	if (line_density == 8){
		//Return that it is a horizontal.
	}
	else {
		left_line = determineHalf("left");
		right_line = determineHalf("right");
		setLineDensity(left_line + right_line);
		
		if (left_line == HORIZONTAL_LINE){ //The horizontal line is already accounted for, so this takes all other intersections with a left horizontal.
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
		//Possible solution: moveALittleBitForward() then call again to see if vertical or diagonal?
		return ;
	}
	else {
		return SENSOR_ERROR; //It is physically impossible for three sensors to be ones with 1.5" lines.
	}
}

void LineIntersection::setLineByte()
{
	line_byte = mySensorBar.getRaw(); //Gets the 8 values as a uint_8 (binary form).
	convertLineByteIntoArray();
}

void LineIntersection::setLineDensity(int user_density = 0)
{
	if (user_density){
		line_density = user_density;
	}
	else {
	line_density = mySensorBar.getDensity();
	}
}

void LineIntersection::convertLineByteIntoArray()
{
	uint_8 binary_array;
	int right_shift;
	for (int i = 0; i < BYTE_SIZE; i++){
		binary_array = line_byte;
		binary_array << i; //Remove anything to the left.
		binary_array >> (BYTE_SIZE - 1); //Move it all the way to the rightmost position.
		if (binary_array == 1){ //TOCHECK: The unsigned 8-bit int is read as decimal in any non-bitwise operation, correct? 
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
