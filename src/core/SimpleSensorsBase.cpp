#include "Arduino.h"
#include "SimpleSensors.h"

SimpleSensor::SimpleSensor(char* id, char* name, char* type, char* units) {
    _id = id;
    _name = name;
    _type = type;
    _units = units;
}

char* SimpleSensor::getId() const {
    return _id;
}

char* SimpleSensor::getName() const {
    return _name;
}

char* SimpleSensor::getType() const {
    return _type;
}

char* SimpleSensor::getUnits() const {
    return _units;
}

float SimpleSensor::read() {
    int rawValue = readRaw();
    return convertRaw(rawValue);
}

float SimpleSensor::convertRaw(int rawValue) {
    return (float)rawValue;
}

//-------------------------------------------

SimplePinSensor::SimplePinSensor(int pin, char* id, char* name, char* type, char* units) : SimpleSensor(id, name, type, units) {
    _pin = pin;
}

void SimplePinSensor::setup() {
    pinMode(_pin, INPUT);
}

int SimplePinSensor::getPin() const {
    return _pin;
}

//-------------------------------------------

AnalogSensor::AnalogSensor(int pin, char* id, char* name, char* type, char* units) : SimplePinSensor(pin, id, name, type, units) {
    _referenceVoltage = 5.0;
}

AnalogSensor::AnalogSensor(int pin, char* id, char* name, char* type) : SimplePinSensor(pin, id, name, type, NULL) {
    _referenceVoltage = 5.0;
}

int AnalogSensor::readRaw() {
    return analogRead(_pin);
}

float AnalogSensor::convertRaw(int rawValue) {
    return convertRawToVoltage(rawValue);
}

float AnalogSensor::convertRawToVoltage(int rawValue) {
    return rawValue * _referenceVoltage / 1024;
}

void AnalogSensor::setReferenceVoltage(float referenceVoltage) {
    _referenceVoltage = referenceVoltage;
}

//-------------------------------------------

DigitalSensor::DigitalSensor(int pin, char* id, char* name, char* type, char* units) : SimplePinSensor(pin, id, name, type, units) {}

DigitalSensor::DigitalSensor(int pin, char* id, char* name, char* type) : SimplePinSensor(pin, id, name, type, NULL) {}

int DigitalSensor::readRaw() {
    return digitalRead(_pin);
}
	