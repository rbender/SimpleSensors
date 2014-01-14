#include <SimpleSensors.h>

AnalogSensor sensor1(A0, "sensor");

SimpleSensor *sensorArray[] = {&sensor1};
SensorCollection sensors(sensorArray, 1);

void setup() {

  sensors.setup();

  Serial.begin(9600);
}

void loop(){

  sensors.dumpRawValuesAsJson(&Serial);
  delay(500);
}
