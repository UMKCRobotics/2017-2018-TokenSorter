#ifndef LINEINTERSECTION_H
#define LINEINTERSECTION_H

#include "Wire.h"
#include "sensorbar.h"
#include "Arduino.h"

#define BYTE_SIZE 8

// #define INTERSECTION_I 10
// #define INTERSECTION_II 20
// #define INTERSECTION_III 30
// #define INTERSECTION_IV 40
// #define INTERSECTION_V 50
//
// #define NO_LINE -1
// #define VERTICAL_LINE 0
// #define DIAGONAL_LINE 1
// #define VERT_AND_DIAG_LINE 2
// #define HORIZONTAL_LINE 3
// #define SENSOR_ERROR 99

//#define SX1509_ADDRESS 0x3E

class LineIntersection{
	private:
		//Class type pulled from example code.
		uint8_t SX1509_ADDRESS = 0x3E;
		SensorBar* mySensorBar;
		uint8_t line_byte;

		String lastFullReading = "000000000";
		int lastPosition = 0;
		int density = 0;
		int middlePin;
		int middleThreshold = 850;
		const char ON_LINE = '1';
		const char OFF_LINE = '0';
		// int8_t line_byte_array[8];
		// int8_t line_density;
		//int8_t intersection_counter;


	public:
		LineIntersection();
		LineIntersection(int pin);
		// int8_t checkIntersection();
		// int8_t determineHalf(String left_or_right);
		// int8_t countOnes(int8_t start, int8_t end);
		// void setLineDensity();
		// void setLineByte();
		// void convertLineByteIntoArray();
		int getDensity() { return density; };

		bool getMiddleState();
		int8_t getArrayDataSum();
		String getArrayDataInString();
		String getFullArrayInString();
		int getLinePosition(bool getNewData = false);
		// Line Intersection Detection functions
		bool getIfAtPerpendicular();
		bool getIfAtSeparatingY();
		bool getIfAtCrossingY();
		bool getIfAtRightY();
		bool getIfAtLeftY();
};

#endif
