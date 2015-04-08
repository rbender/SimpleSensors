#include <SimpleSensors.h>

AnalogSensor sensor1(A0, "light", "Light", "light");
AnalogSensor sensor2(A1, "temp", "Temperature", "temperature");

SensorCollection sensors("example", "Example Sensor Collection");

JsonSensorEmitter emitter;

void setup() {

  sensors.addSensor(sensor1);
  sensors.addSensor(sensor2);
  sensors.setup();

  Serial.begin(9600);
}

void loop(){

  emitter.emitSensorCollection(Serial, sensors);
  delay(500);
}