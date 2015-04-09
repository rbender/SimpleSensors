#include "utility/JsonPrinter.h"

class PlainTextSensorStreamer {

    public:
        void streamSensor(Print &printer, SimpleSensor* sensor);
        void streamSensors(Print &printer, SensorCollection& sensors);
};

class JsonSensorStreamer {

    public:
        void streamSensor(Print& printer, SimpleSensor* sensor);
        void streamSensors(Print& printer, SensorCollection& sensors);	
    
    private:
        JsonPrinter _jsonPrinter;
				void streamSensor(Print& printer, SimpleSensor* sensor, boolean standalone);
};