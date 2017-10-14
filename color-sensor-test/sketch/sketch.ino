#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define multiplexer_addr 0x70

class ColorSensor
{

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
  private:
    Adafruit_TCS34725 TCS = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

    const int RED_MIN = 35;
    const int RED_MAX = 180;
    const int GREEN_MIN = 40;
    const int GREEN_MAX = 130;
    const int BLUE_MIN = 40;
    const int BLUE_MAX = 130;

    const static int COLOR_ARRAY_SIZE = 8;
    const int DIFF_CONSTRAINT = 45;
    const String COLOR_NAMES_STRINGS[COLOR_ARRAY_SIZE] {
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
    int colors[COLOR_ARRAY_SIZE][3] = {
      {255,19,39}, // red
      {70,187,99}, // green
      {21,144,255}, // blue
      {133,155,28}, // yellow
      {180,76,130}, // magenta
      {43,175,153}, // cyan
      {91,138,116} // gray
    };

    uint8_t multiplexerPort = 0;

    void startMultiplex()
    {
      Wire.beginTransmission(multiplexer_addr);
      Wire.write(1 << multiplexerPort);
      Wire.endTransmission();
    } // end startMultiplex

    void getRawColorData(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c)
    {
      startMultiplex();
      TCS.getRawData(r,g,b,c);
    } // end getRawColorData

    bool beginTCS(Adafruit_TCS34725& tcsref)
    {
      startMultiplex();
      return TCS.begin();
    } // end beginTCS

    int constrainColors(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c, int* redAct, int* blueAct, int* greenAct)
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
    
  public:
    ColorSensor()
    {
    } // end constructor

    enum COLOR_NAME {
      Unknown = 0,
      Red,
      Green,
      Blue,
      Yellow,
      Magenta,
      Cyan,
      Gray
    };
    
    // multiplexerPort between 0 and 7 inclusive
    void initSensor(uint8_t multiplexerPort)
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

    COLOR_NAME getColor()
    {
      uint16_t r, g, b, c; //, colorTemp, lux;
      int redAct, greenAct, blueAct;
  
      getRawColorData(&r, &g, &b, &c);
      constrainColors(&r, &g, &b, &c, &redAct, &blueAct, &greenAct);

      


      // find closes color
      COLOR_NAME best_color_enum;
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
}; // end class ColorSensor


ColorSensor sensor1 = ColorSensor();
ColorSensor sensor2 = ColorSensor();

void setup(void)
{
  Serial.begin(115200);
   sensor1.initSensor(0);
   sensor1.initSensor(1);

  
  // Now we're ready to get readings!
}

void loop(void) {

  Serial.println("Sensor1:");
  Serial.println(sensor1.getColor());
  Serial.println("Sensor2:");
  Serial.println(sensor2.getColor());
  
}

