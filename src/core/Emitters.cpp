#include "Arduino.h"
#include "SimpleSensors.h"
#include "utility/JsonPrinter.h"

PlainTextSensorEmitter::PlainTextSensorEmitter(Print &printer) {
    _printer = &printer;
}

void PlainTextSensorEmitter::emitSensor(SimpleSensor* sensor) {

    _printer->print(sensor->getId());
    _printer->print("=");
    _printer->println(sensor->readRaw());
}

void PlainTextSensorEmitter::emitSensorCollection(SensorCollection& sensors) {

    for (int i = 0; i < sensors.getSize(); i++) {
        SimpleSensor* sensor = sensors.getSensor(i);
        emitSensor(sensor);
    }	
}

//-------------------------------------------

JsonSensorEmitter::JsonSensorEmitter(Print &printer) : _jsonPrinter(printer) {}

void JsonSensorEmitter::emitSensorCollection(SensorCollection& sensors) {

    _jsonPrinter.startObject();
  
    _jsonPrinter.stringProperty("id", sensors.getId());
    _jsonPrinter.comma();

    _jsonPrinter.stringProperty("name", sensors.getName());
    _jsonPrinter.comma();

    _jsonPrinter.property("sensors");
    _jsonPrinter.startArray();

    int numSensors = sensors.getSize();
    for (int i = 0; i < numSensors; i++) {
        SimpleSensor* sensor = sensors.getSensor(i);

        emitSensor(sensor);

        if (i < numSensors - 1) {
            _jsonPrinter.comma();
        }
    }

    _jsonPrinter.endArray();
    _jsonPrinter.endObject();
    _jsonPrinter.newline();
}

void JsonSensorEmitter::emitSensor(SimpleSensor* sensor) {

    int rawValue = sensor->readRaw();
    float value = sensor->convertRaw(rawValue);

    _jsonPrinter.startObject();

    _jsonPrinter.stringProperty("id", sensor->getId());
    _jsonPrinter.comma();

    _jsonPrinter.stringProperty("name", sensor->getName());
    _jsonPrinter.comma();

    _jsonPrinter.stringProperty("type", sensor->getType());
    _jsonPrinter.comma();

    _jsonPrinter.floatProperty("value", value);
    _jsonPrinter.comma();	

    _jsonPrinter.intProperty("raw_value", rawValue);

    if (sensor->getUnits() != NULL) {
        _jsonPrinter.comma();
        _jsonPrinter.stringProperty("units", sensor->getUnits());
    }

    _jsonPrinter.endObject();
}