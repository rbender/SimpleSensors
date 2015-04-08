#include "utility/JsonPrinter.h"

class PlainTextSensorEmitter {

    public:
        void emitSensor(Print &printer, SimpleSensor* sensor);
        void emitSensorCollection(Print &printer, SensorCollection& sensors);
};

class JsonSensorEmitter {

    public:
        void emitSensor(Print& printer, SimpleSensor* sensor);
        void emitSensorCollection(Print& printer, SensorCollection& sensors);	
    
    private:
        JsonPrinter _jsonPrinter;
};