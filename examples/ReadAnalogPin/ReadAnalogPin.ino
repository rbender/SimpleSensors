#include <SimpleSensors.h>

AnalogSensor sensor1(A0, "temp", "Temperature", "temperature");
AnalogSensor sensor2(A1, "light", "Light", "light");

SensorCollection sensors("example", "Example Sensor Collection");

void setup() {

  sensors.addSensor(sensor1);
  sensors.addSensor(sensor2);
  sensors.setup();

  Serial.begin(9600);
}

void loop(){

  sensors.dumpRawValuesAsJson(Serial);
  delay(1000);
}
