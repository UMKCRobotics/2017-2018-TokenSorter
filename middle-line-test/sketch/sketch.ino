#define LINE_SENSOR 33

void setup() {
	pinMode(LINE_SENSOR,INPUT);
	Serial.begin(9600);
}

void loop() {
	Serial.println(analogRead(LINE_SENSOR));
	delay(250);
}
