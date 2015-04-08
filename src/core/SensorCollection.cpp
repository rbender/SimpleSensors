#include "Arduino.h"
#include "SimpleSensors.h"

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

char* SensorCollection::getId() const {
    return _id;
}

char* SensorCollection::getName() const {
    return _name;
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

SimpleSensor* SensorCollection::getSensor(char* id) {
    for (int i = 0; i < _size; i++) {
        SimpleSensor* sensor = _sensors[i];
        if (strcmp(id, sensor->getId()) == 0) {
            return sensor;
        }
    }
    return NULL;
}