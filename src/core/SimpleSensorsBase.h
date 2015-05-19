class SimpleSensor {

    public:
        SimpleSensor(char* id, char* name, char* type, char* units);
        virtual void setup();

        char* getId() const;
        char* getName() const;
        char* getType() const;
        char* getUnits() const;
        virtual boolean hasRaw() const;

        virtual float read();
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
