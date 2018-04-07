#include "LineIntersection.h"

LineIntersection::LineIntersection()
{


}


LineIntersection::LineIntersection(int pin) {
	mySensorBar = new SensorBar(SX1509_ADDRESS);
	mySensorBar->clearBarStrobe();
	mySensorBar->clearInvertBits();
	mySensorBar->begin();
	// set middlePin
	middlePin = pin;
	// get a first reading
	read();
}


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


String LineIntersection::getFullArrayInString() {
	String lineData = "";
	density = 0;
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();
	bool state = getMiddleState();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		lineData += (bit_value ? ON_LINE : OFF_LINE);
		density += bit_value;
		if (i == 4) {
			lineData += (state ? ON_LINE : OFF_LINE);
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
		if (lastFullReading[3] == ON_LINE) position -= 4;//1;
		if (lastFullReading[5] == ON_LINE) position += 4;//1;
	}
	else {
		// otherwise, worry about all
		if (lastFullReading[3] == ON_LINE || lastFullReading[5] == ON_LINE) {
			if (lastFullReading[3] == ON_LINE) position -= 4;//4;
			if (lastFullReading[5] == ON_LINE) position += 4;//4;
		}
		else if (lastFullReading[2] == ON_LINE || lastFullReading[6] == ON_LINE) {
			if (lastFullReading[2] == ON_LINE) position -= 6;//8;
			if (lastFullReading[6] == ON_LINE) position += 6;//8;
		}
		else if (lastFullReading[1] == ON_LINE || lastFullReading[7] == ON_LINE) {
			if (lastFullReading[1] == ON_LINE) position -= 8;//12;
			if (lastFullReading[7] == ON_LINE) position += 8;//12;
		}
		else if (lastFullReading[0] == ON_LINE || lastFullReading[8] == ON_LINE) {
			if (lastFullReading[0] == ON_LINE) position -= 10;//16;
			if (lastFullReading[8] == ON_LINE) position += 10;//16;
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


bool LineIntersection::getIfAtPerpendicular() {
	int required_density = 5;
	return getDensity() >= required_density;
}


bool LineIntersection::getIfAtSeparatingY() {
	return (lastFullReading[2] == ON_LINE && lastFullReading[6] == ON_LINE)
			|| (lastFullReading[1] == ON_LINE && lastFullReading[7] == ON_LINE)
			|| (lastFullReading[2] == ON_LINE && lastFullReading[7] == ON_LINE)
			|| (lastFullReading[1] == ON_LINE && lastFullReading[6] == ON_LINE);
}


bool LineIntersection::getIfAtCrossingY() {
	return getIfAtSeparatingY();
}


bool LineIntersection::getIfAtRightY() {
	return getIfAtPerpendicular();
}


bool LineIntersection::getIfAtLeftY() {
	return getIfAtPerpendicular();
}

