#include "Arduino.h"
#include "SimpleSensors.h"
#include "utility/JsonPrinter.h"

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

//-------------------------------------------

TMP36TemperatureSensor::TMP36TemperatureSensor(int pin, char* id, char* name) : AnalogSensor(pin, id, name, "temperature", "f") {}

float TMP36TemperatureSensor::convertRaw(int rawValue) {
	
	float voltage = rawValue * _referenceVoltage / 1024;
    float temperatureC = (voltage - 0.5) * 100;
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32;
	return temperatureF;
}
	
//-------------------------------------------

SensorCollection::SensorCollection(char* id, char* name) {
  _id = id;
  _name = name;
  _size = 0;
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

void SensorCollection::addSensor(SimpleSensor& sensor) {
    _sensors[_size] = &sensor;
    _size++;
}

SimpleSensor* SensorCollection::getSensor(int index) {
  return _sensors[index];
}

void SensorCollection::dumpValues(Print &printer) {
  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];

    printer.print(sensor->getId());
    printer.print("=");
    printer.println(sensor->readRaw());
  }
}

void SensorCollection::dumpValuesAsJson(Print &printer) {

  JsonPrinter jsonPrinter(printer);
  
  jsonPrinter.startObject();
  
  jsonPrinter.property("id");  
  jsonPrinter.stringValue(_id);
  jsonPrinter.comma();
  
  jsonPrinter.property("name");
  jsonPrinter.stringValue(_name);
  jsonPrinter.comma();
  
  jsonPrinter.property("sensors");
  jsonPrinter.startArray();
  
  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];
	
	dumpValueAsJson(jsonPrinter, sensor);
	
    if (i < _size - 1) {
      jsonPrinter.comma();
    }
  }
  
  jsonPrinter.endArray();
  jsonPrinter.endObject();
  jsonPrinter.newline();
}

void SensorCollection::dumpValueAsJson(JsonPrinter& jsonPrinter, SimpleSensor* sensor) {

	int rawValue = sensor->readRaw();
	float value = sensor->convertRaw(rawValue);

	jsonPrinter.startObject();
	
	jsonPrinter.stringProperty("id", sensor->getId());
	jsonPrinter.comma();
	
	jsonPrinter.stringProperty("name", sensor->getName());
	jsonPrinter.comma();
	
	jsonPrinter.stringProperty("type", sensor->getType());
	jsonPrinter.comma();
	
	jsonPrinter.floatProperty("value", value);
	jsonPrinter.comma();	
	
	jsonPrinter.intProperty("raw_value", rawValue);
	jsonPrinter.comma();
	
	if (sensor->getUnits() != NULL) {
		jsonPrinter.stringProperty("units", sensor->getUnits());			
	}
	
	jsonPrinter.endObject();	
}


