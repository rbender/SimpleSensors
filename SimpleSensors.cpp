#include "Arduino.h"
#include "SimpleSensors.h"
#include "utility/JsonPrinter.h"

SimpleSensor::SimpleSensor(char* id, char* name, char* type) {
  _id = id;
  _name = name;
  _type = type;
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

//-------------------------------------------

SimplePinSensor::SimplePinSensor(int pin, char* id, char* name, char* type) : SimpleSensor(id, name, type) {
  _pin = pin;
}

void SimplePinSensor::setup() {
  pinMode(_pin, INPUT);
}

int SimplePinSensor::getPin() const {
  return _pin;
}

//-------------------------------------------

AnalogSensor::AnalogSensor(int pin, char* id, char* name, char* type) : SimplePinSensor(pin, id, name, type) {}

int AnalogSensor::readRaw() {
  return analogRead(_pin);
}

//-------------------------------------------

DigitalSensor::DigitalSensor(int pin, char* id, char* name, char* type) : SimplePinSensor(pin, id, name, type) {}

int DigitalSensor::readRaw() {
  return digitalRead(_pin);
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

void SensorCollection::dumpRawValues(Print &printer) {
  for (int i = 0; i < _size; i++) {
    SimpleSensor* sensor = _sensors[i];

    printer.print(sensor->getId());
    printer.print("=");
    printer.println(sensor->readRaw());
  }
}

void SensorCollection::dumpRawValuesAsJson(Print &printer) {

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
	
	dumpRawValueAsJson(jsonPrinter, sensor);
	
    if (i < _size - 1) {
      jsonPrinter.comma();
    }
  }
  
  jsonPrinter.endArray();
  jsonPrinter.endObject();
  jsonPrinter.newline();
}

void SensorCollection::dumpRawValueAsJson(JsonPrinter& jsonPrinter, SimpleSensor* sensor) {

	jsonPrinter.startObject();
	
	jsonPrinter.property("id");
	jsonPrinter.stringValue(sensor->getId());
	jsonPrinter.comma();
	
	jsonPrinter.property("name");
	jsonPrinter.stringValue(sensor->getName());
	jsonPrinter.comma();
	
	jsonPrinter.property("type");
	jsonPrinter.stringValue(sensor->getType());
	jsonPrinter.comma();
	
	jsonPrinter.property("raw_value");
	jsonPrinter.intValue(sensor->readRaw());
	
	jsonPrinter.endObject();	
}


