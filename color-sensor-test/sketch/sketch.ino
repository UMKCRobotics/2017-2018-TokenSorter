#include <Wire.h>
#include "Adafruit_TCS34725.h"

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
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

int redMin = 35;
int redMax = 180;
int greenMin = 40;
int greenMax = 130;
int blueMin = 40;
int blueMax = 130;

const int color_size = 7;
const int diff_constraint = 45;
String color_names[color_size] = {
  "Orange",
  "Yellow",
  "Red",
  "Green",
  "Blue",
  "Purple",
  "Gray"
};

int colors[color_size][3] = {
  {220,53,2},
  {154,140,2},
  {249,11,31},
  {50,217,98},
  {10,153,235},
  {109,79,160},
  {95,133,110}
};

void setup(void) {

  Serial.begin(115200);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  // Figure out some basic hex code for visualization
  uint32_t sum = c;
  float red, green, blue;
  int redAct, greenAct, blueAct;
  red = r; red /= sum;
  green = g; green /= sum;
  blue = b; blue /= sum;
  red *= 256; green *= 256; blue *= 256;
  redAct = constrain(map((int)red,redMin,redMax,0,255),0,255);
  greenAct = constrain(map((int)green,greenMin,greenMax,0,255),0,255);
  blueAct = constrain(map((int)blue,blueMin,blueMax,0,255),0,255);

  // find closes color
  int best_color_index = 0;
  unsigned long min_diff = -1;
  for (int i = 0; i < color_size; i++) {
    unsigned long current_diff = 0;
    current_diff += abs(colors[i][0] - redAct);
    current_diff += abs(colors[i][1] - greenAct);
    current_diff += abs(colors[i][2] - blueAct);
    if (current_diff < min_diff) {
      best_color_index = i;
      min_diff = current_diff;
    }
  }
  if (min_diff < diff_constraint) {
    Serial.print(color_names[best_color_index]);
  }
  else {
    Serial.print("Unknown");
  }
  Serial.print("\t");
  Serial.println(min_diff);

  Serial.print("\t");
  Serial.print(redAct, DEC); Serial.print("\t"); Serial.print(greenAct, DEC); Serial.print("\t"); Serial.print(blueAct, DEC);
  Serial.println();
  Serial.println(" ");
}
