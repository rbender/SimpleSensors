#include "Arduino.h"

#ifndef SimpleSensors_h
#define SimpleSensors_h

#include "utility/JsonPrinter.h"

const int MAX_SENSORS = 20;

class SimpleSensor {

  public:
    SimpleSensor(char* id, char* name, char* type, char* units);
    virtual void setup();

    char* getId() const;
    char* getName() const;
	char* getType() const;
	char* getUnits() const;

	float read();
    virtual int readRaw();
	virtual float convertRaw(int rawValue);

  protected:
    char* _id;
    char* _name;
	char* _type;
	char* _units;

};

//-------------------------------------------

class SimplePinSensor : public SimpleSensor {

  public:
    SimplePinSensor(int pin, char* id, char* name, char* type, char* units);
	void setup();

    int getPin() const;

  protected:
    int _pin;

};

//-------------------------------------------

class AnalogSensor : public SimplePinSensor {

  public:
    AnalogSensor(int pin, char* id, char* name, char* type, char* units);
	AnalogSensor(int pin, char* id, char* name, char* type);
	
    int readRaw();
	float convertRaw(int rawValue);	
	void setReferenceVoltage(float referenceVoltage);
	
  protected:
	float convertRawToVoltage(int rawValue);
	  
	float _referenceVoltage;
};

//-------------------------------------------

class DigitalSensor : public SimplePinSensor {

  public:
    DigitalSensor(int pin, char* id, char* name, char* type, char* units);
	DigitalSensor(int pin, char* id, char* name, char* type);
    int readRaw();
};

//-------------------------------------------

class TMP36TemperatureSensor : public AnalogSensor {

  public:
    TMP36TemperatureSensor(int pin, char* id, char* name);
	float convertRaw(int rawValue);
};

//-------------------------------------------

class SensorCollection {

  public:
    SensorCollection(char* id, char* name);
    void setup();

    char* getId() const;
		char* getName() const;
    int getSize() const;
    void addSensor(SimpleSensor& sensor);
    SimpleSensor* getSensor(int index);

  private:
    SimpleSensor* _sensors[MAX_SENSORS];
    int _size;
    char* _id;
    char* _name;
};

//-------------------------------------------

class PlainTextSensorEmitter {
	
  public:
	  PlainTextSensorEmitter(Print &printer);
		void emitSensor(SimpleSensor* sensor);
		void emitSensorCollection(SensorCollection& sensors);
		
	private:
		Print* _printer;		
};

class JsonSensorEmitter {
	
	public:
		JsonSensorEmitter(Print &printer);
		void emitSensor(SimpleSensor* sensor);
		void emitSensorCollection(SensorCollection& sensors);
		
	private:
		JsonPrinter _jsonPrinter;	
};

#endif
