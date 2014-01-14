#include "Arduino.h"
#include "SimpleSensors.h"

SimpleSensor::SimpleSensor(int pin, char* shortName) {

  _pin = pin;
  _shortName = shortName;
}

void SimpleSensor::setup() {
  pinMode(_pin, INPUT);
}

int SimpleSensor::getPin() const {
  return _pin;
}

char* SimpleSensor::getShortName() const {
  return _shortName;
}

//-------------------------------------------

AnalogSensor::AnalogSensor(int pin, char* shortName) : SimpleSensor(pin, shortName) {}

int AnalogSensor::readRaw() {
  return analogRead(_pin);
}

//-------------------------------------------

DigitalSensor::DigitalSensor(int pin, char* shortName) : SimpleSensor(pin, shortName) {}

int DigitalSensor::readRaw() {
  return digitalRead(_pin);
}

//-------------------------------------------

SensorCollection::SensorCollection(SimpleSensor* sensors[], int size) {
  _sensors = sensors;
  _size = size;
}

void SensorCollection::setup() {
  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];
    sensor->setup();
  }
}

int SensorCollection::getSize() const {
  return _size;
}

SimpleSensor* SensorCollection::getSensor(int index) {
  return _sensors[index];
}

void SensorCollection::dumpRawValues(Print* printer) {
  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];

    printer->print(sensor->getShortName());
    printer->print("=");
    printer->println(sensor->readRaw());
  }
}

void SensorCollection::dumpRawValuesAsJson(Print* printer) {

  printer->print("{\"sensors\":[");

  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];

    printer->print("{\"name\":\"");
    printer->print(sensor->getShortName());
    printer->print("\", \"value\":");
    printer->print(sensor->readRaw());
    printer->print("}");

    if (i < _size - 1) {
      printer->print(",");
    }
  }

  printer->println("]}");
}


