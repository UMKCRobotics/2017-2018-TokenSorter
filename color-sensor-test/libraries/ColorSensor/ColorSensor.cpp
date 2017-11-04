#include "ColorSensor.h"

#define multiplexer_addr 0x70 // needs to be changed if using a different mulitplexer

  /* Example code for the Adafruit TCS34725 breakout library */

  /* Connect SCL    to analog 5
     Connect SDA    to analog 4
     Connect VDD    to 3.3V DC
     Connect GROUND to common ground */
   
  /* Initialise with default values (int time = 2.4ms, gain = 1x) */
  // Adafruit_TCS34725 tcs = Adafruit_TCS34725();

  // our RGB -> eye-recognized gamma color

  /* Initialise with specific int time and gain values */
  // TCS34725_INTEGRATIONTIME_700MS
  // TCS34725_INTEGRATIONTIME_154MS

    // Primes the multiplexer for a command
    void ColorSensor::startMultiplex()
    {
      Wire.beginTransmission(multiplexer_addr);
      Wire.write(1 << multiplexerPort);
      Wire.endTransmission();
    } // end startMultiplex

    // Retrieves the raw color data from the color sensor, passes variables by reference
    void ColorSensor::getRawColorData(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c)
    {
      startMultiplex();
      TCS.getRawData(r,g,b,c);
    } // end getRawColorData

    // Starts the color sensor
    bool ColorSensor::beginTCS(Adafruit_TCS34725& tcsref)
    {
      startMultiplex();
      return TCS.begin();
    } // end beginTCS

    // Constrains the colors to a 256 color value as the sensor can return values higher than 256
    void ColorSensor::constrainColors(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c, int* redAct, int* blueAct, int* greenAct)
    {
      uint32_t sum = *c;
      float red, green, blue;
      red = *r;
      green = *g;
      blue = *b;
      
      red = (red / sum) * 256;
      green = (green / sum) * 256;
      blue = (blue / sum) * 256;
      
      *redAct = constrain(map(red,RED_MIN,RED_MAX,0,255),0,255);
      *greenAct = constrain(map(green,GREEN_MIN,GREEN_MAX,0,255),0,255);
      *blueAct = constrain(map(blue,BLUE_MIN,BLUE_MAX,0,255),0,255);

      Serial.print("RGB: ");
      Serial.print(*redAct);
      Serial.print(" ");
      Serial.print(*greenAct);
      Serial.print(" ");
      Serial.println(*blueAct);
    } // end constrainColors

    // Default constructor
    ColorSensor::ColorSensor()
    {
    } // end constructor

    // Assigns multiplexerPort variable to class variable and starts color sensor
    // Call initSensor after initializing ColorSensor variable
    // multiplexerPort should be between 0 and 7 inclusive
    void ColorSensor::initSensor(uint8_t multiplexerPort)
    {
      this->multiplexerPort = multiplexerPort;
      
      Wire.begin();

      startMultiplex();
      if (TCS.begin())
      {
        Serial.println("Found sensor");
      }
      else
      {
        Serial.println("No TCS34725 found ... check your connections");
        while (1);
      } // end if
    } // end initSensor

    // Gets the color from the color sensor and returns the enum of the color the sensor sees
    ColorSensor::COLOR_NAME ColorSensor::getColor()
    {
      uint16_t r, g, b, c;
      int redAct, greenAct, blueAct;
  
      getRawColorData(&r, &g, &b, &c);
      constrainColors(&r, &g, &b, &c, &redAct, &blueAct, &greenAct);

      // find closest color
      COLOR_NAME best_color_enum = Unknown;
      unsigned long min_diff = -1;
      
      for (int i = Red; i <= Gray ; i++)
      {
        unsigned long current_diff = 0;
        current_diff += abs(colors[i-1][0] - redAct);
        current_diff += abs(colors[i-1][1] - greenAct);
        current_diff += abs(colors[i-1][2] - blueAct);
        
        if (current_diff < min_diff)
        {
          best_color_enum = (COLOR_NAME)i;
          min_diff = current_diff;
        } // end if
      } // end loop

      Serial.print("Error: ");
      Serial.println(min_diff);

      if (min_diff < DIFF_CONSTRAINT)
      {
        return best_color_enum;
      }
      else
      {
        return Unknown;
      } // end if
    } // end getColor