#include "utility/JsonPrinter.h"

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