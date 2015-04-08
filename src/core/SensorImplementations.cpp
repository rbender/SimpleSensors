#include "Arduino.h"
#include "SimpleSensors.h"

TMP36TemperatureSensor::TMP36TemperatureSensor(int pin, char* id, char* name) : AnalogSensor(pin, id, name, "temperature", "f") {}

float TMP36TemperatureSensor::convertRaw(int rawValue) {

    float voltage = rawValue * _referenceVoltage / 1024;
    float temperatureC = (voltage - 0.5) * 100;
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32;
    return temperatureF;
}