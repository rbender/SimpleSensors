class TMP36TemperatureSensor : public AnalogSensor {

    public:
        TMP36TemperatureSensor(int pin, char* id, char* name);
        float convertRaw(int rawValue);
};