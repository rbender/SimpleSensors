/*

Simple Sensors Analog Pins Example

This is a basic example of using SimpleSensors to read
two sensors off analog pins and stream that data to the
serial port once a second.

*/

#include <SimpleSensors.h>

AnalogSensor sensor1(A0, "light", "Light", "light");
AnalogSensor sensor2(A1, "temp", "Temperature", "temperature");

SensorCollection sensors("example", "Example Sensor Collection");

JsonSensorStreamer streamer;

void setup() {

  sensors.addSensor(sensor1);
  sensors.addSensor(sensor2);
  sensors.setup();

  Serial.begin(9600);
}

void loop(){

  streamer.streamSensors(Serial, sensors);
  delay(1000);
}