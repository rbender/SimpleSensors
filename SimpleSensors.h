#include "Arduino.h"

#ifndef SimpleSensors_h
#define SimpleSensors_h

#include "utility/JsonPrinter.h"

const int MAX_SENSORS = 20;

class SimpleSensor {

  public:
    SimpleSensor(char* id, char* name, char* type);
    virtual void setup();

    char* getId() const;
    char* getName() const;
	char* getType() const;

    virtual int readRaw();

  protected:
    char* _id;
    char* _name;
	char* _type;

};

//-------------------------------------------

class SimplePinSensor : public SimpleSensor {

  public:
    SimplePinSensor(int pin, char* id, char* name, char* type);
	void setup();

    int getPin() const;

  protected:
    int _pin;

};

//-------------------------------------------

class AnalogSensor : public SimplePinSensor {

  public:
    AnalogSensor(int pin, char* id, char* name, char* type);
    int readRaw();
};

//-------------------------------------------

class DigitalSensor : public SimplePinSensor {

  public:
    DigitalSensor(int pin, char* id, char* name, char* type);
    int readRaw();
};

//-------------------------------------------

class SensorCollection {

  public:
    SensorCollection(char* id, char* name);
    void setup();

    int getSize() const;
    void addSensor(SimpleSensor& sensor);
    SimpleSensor* getSensor(int index);

    void dumpRawValues(Print &printer);
    void dumpRawValuesAsJson(Print &printer);

  private:
    SimpleSensor* _sensors[MAX_SENSORS];
    int _size;
    char* _id;
    char* _name;
	
	void dumpRawValueAsJson(JsonPrinter& jsonPrinter, SimpleSensor* sensor);
};

#endif
