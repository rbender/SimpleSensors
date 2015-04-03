#include <TinkerKitPins.h>
#include <SimpleSensors.h>

AnalogSensor sensor1(I0, "light", "Light", "light");
//AnalogSensor sensor1(I0, "temp", "Temperature", "temperature");

SensorCollection sensors("example", "Example Sensor Collection");

void setup() {

  sensors.addSensor(sensor1);
  //sensors.addSensor(sensor2);
  sensors.setup();

  Serial.begin(9600);
}

void loop() {

  sensors.dump
}
