#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "Adafruit_TCS34725.h"
#include "Arduino.h"
#include <Wire.h>

class ColorSensor
{
  private:
    Adafruit_TCS34725 TCS = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

    // color min/max for RGB
    const int RED_MIN = 35;
    const int RED_MAX = 180;
    const int GREEN_MIN = 40;
    const int GREEN_MAX = 130;
    const int BLUE_MIN = 40;
    const int BLUE_MAX = 130;

    const static int COLOR_ARRAY_SIZE = 8;
    
    const unsigned int DIFF_CONSTRAINT = 1000;//80;//45; // color differntial constraint
    
    const String COLOR_NAMES_STRINGS[COLOR_ARRAY_SIZE]
    {
      "Unknown",
      "Red",
      "Green",
      "Blue",
      "Yellow",
      "Magenta",
      "Cyan",
      "Gray"
    };    

    // Holds the values of the colors
    int colors[COLOR_ARRAY_SIZE][3] =
    {
      {243,24,26}, // red
      {29,195,64}, // green
      {31,110,248}, // blue
      {125,151,41}, // yellow
      {180,76,130}, // magenta
      {20,165,202}, // cyan
      {83,134,130} // gray
    };

    uint8_t multiplexerPort = 0;

    // Primes the multiplexer for a command
    void startMultiplex();

    // Retrieves the raw color data from the color sensor, passes variables by reference
    void getRawColorData(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c);

    // Starts the color sensor
    bool beginTCS(Adafruit_TCS34725& tcsref);

    // Constrains the colors to a 256 color value as the sensor can return values higher than 256
    void constrainColors(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c, int* redAct, int* blueAct, int* greenAct);
    
  public:
    // Default constructor
    ColorSensor();

    // Enum that holds the values for the different colors used
    enum COLOR_NAME
    {
      Unknown = 0,
      Red,
      Green,
      Blue,
      Yellow,
      Magenta,
      Cyan,
      Gray
    };

    // Assigns multiplexerPort variable to class variable and starts color sensor
    // Call initSensor after initializing ColorSensor variable
    // multiplexerPort should be between 0 and 7 inclusive
    void initSensor(uint8_t multiplexerPort);

    // Gets the color from the color sensor and returns the enum of the color the sensor sees
    COLOR_NAME getColor();
};

#endif