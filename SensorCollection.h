const int MAX_SENSORS = 20;

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