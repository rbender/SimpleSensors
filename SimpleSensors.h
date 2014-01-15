#include "Arduino.h"

#ifndef SimpleSensors_h
#define SimpleSensors_h

class SimpleSensor {

  public:
    SimpleSensor(int pin, char* shortName);
    void setup();

    int getPin() const;
    char* getShortName() const;

    virtual int readRaw();

  protected:
    int _pin;
    char* _shortName;

};

//-------------------------------------------

class AnalogSensor : public SimpleSensor {

  public:
    AnalogSensor(int pin, char* shortName);
    int readRaw();
};

//-------------------------------------------

class DigitalSensor : public SimpleSensor {

  public:
    DigitalSensor(int pin, char* shortName);
    int readRaw();
};

//-------------------------------------------

class SensorCollection {

  public:
    SensorCollection(SimpleSensor* sensors[], int size);
    void setup();

    int getSize() const;
    SimpleSensor* getSensor(int index);

    void dumpRawValues(Print &printer);
    void dumpRawValuesAsJson(Print &printer);

  private:
    SimpleSensor** _sensors;
    int _size;
};

#endif
