#include "Arduino.h"
#include "SimpleSensors.h"
#include "utility/JsonPrinter.h"

void PlainTextSensorEmitter::emitSensor(Print &printer, SimpleSensor* sensor) {

    printer.print(sensor->getId());
    printer.print("=");
    printer.println(sensor->readRaw());
}

void PlainTextSensorEmitter::emitSensorCollection(Print &printer, SensorCollection& sensors) {

    for (int i = 0; i < sensors.getSize(); i++) {
        SimpleSensor* sensor = sensors.getSensor(i);
        emitSensor(printer, sensor);
    }	
}

//-------------------------------------------

void JsonSensorEmitter::emitSensorCollection(Print &printer, SensorCollection& sensors) {

    _jsonPrinter.startObject(printer);
  
    _jsonPrinter.stringProperty(printer, "id", sensors.getId());
    _jsonPrinter.comma(printer);

    _jsonPrinter.stringProperty(printer, "name", sensors.getName());
    _jsonPrinter.comma(printer);

    _jsonPrinter.property(printer, "sensors");
    _jsonPrinter.startArray(printer);

    int numSensors = sensors.getSize();
    for (int i = 0; i < numSensors; i++) {
        SimpleSensor* sensor = sensors.getSensor(i);

        emitSensor(printer, sensor);

        if (i < numSensors - 1) {
            _jsonPrinter.comma(printer);
        }
    }

    _jsonPrinter.endArray(printer);
    _jsonPrinter.endObject(printer);
    _jsonPrinter.newline(printer);
}

void JsonSensorEmitter::emitSensor(Print &printer, SimpleSensor* sensor) {

    int rawValue = sensor->readRaw();
    float value = sensor->convertRaw(rawValue);

    _jsonPrinter.startObject(printer);

    _jsonPrinter.stringProperty(printer, "id", sensor->getId());
    _jsonPrinter.comma(printer);

    _jsonPrinter.stringProperty(printer, "name", sensor->getName());
    _jsonPrinter.comma(printer);

    _jsonPrinter.stringProperty(printer, "type", sensor->getType());
    _jsonPrinter.comma(printer);

    _jsonPrinter.floatProperty(printer, "value", value);
    _jsonPrinter.comma(printer);	

    _jsonPrinter.intProperty(printer, "raw_value", rawValue);

    if (sensor->getUnits() != NULL) {
        _jsonPrinter.comma(printer);
        _jsonPrinter.stringProperty(printer, "units", sensor->getUnits());
    }

    _jsonPrinter.endObject(printer);
}