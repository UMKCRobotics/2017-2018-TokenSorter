#include "ColorSensor.h"

ColorSensor sensor1 = ColorSensor();
ColorSensor sensor2 = ColorSensor();

void setup()
{
   Serial.begin(115200);
   sensor1.initSensor(0);
   sensor2.initSensor(1);
}

void loop()
{
  Serial.println("Sensor1:");
  Serial.println(sensor1.getColor());
  Serial.println("Sensor2:");
  Serial.println(sensor2.getColor());
}
