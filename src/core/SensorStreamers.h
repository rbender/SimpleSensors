#include "utility/JsonPrinter.h"

class SensorStreamer {

    public:
        virtual void streamSensor(Print &printer, SimpleSensor* sensor);
        virtual void streamSensors(Print &printer, SensorCollection& sensors);
};

class PlainTextSensorStreamer : public SensorStreamer {

    public:
        void streamSensor(Print &printer, SimpleSensor* sensor);
        void streamSensors(Print &printer, SensorCollection& sensors);
};

class JsonSensorStreamer : public SensorStreamer {

    public:
        void streamSensor(Print& printer, SimpleSensor* sensor);
        void streamSensors(Print& printer, SensorCollection& sensors);	
    
    private:
        JsonPrinter _jsonPrinter;
        void streamSensor(Print& printer, SimpleSensor* sensor, boolean standalone);
};