#ifndef LINEINTERSECTION_H
#define LINEINTERSECTION_H

#include "Wire.h"
#include "sensorbar.h"
#include "Arduino.h"

//#define BYTE_SIZE 8


class LineIntersection{
	private:
		//Class type pulled from example code.
		uint8_t SX1509_ADDRESS = 0x3E;
		SensorBar* mySensorBar;
		uint8_t line_byte;
		const int BYTE_SIZE = 8;
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
		int getDensity() { return density; };

		bool getMiddleState();
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
