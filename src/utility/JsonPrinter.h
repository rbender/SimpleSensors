#include "Arduino.h"

#ifndef JsonPrinter_h
#define JsonPrinter_h

class JsonPrinter {

public:
      
    void startObject(Print& printer);
    void endObject(Print& printer);

    void startArray(Print& printer);    
    void endArray(Print& printer);

    void property(Print& printer, char* name);

    void stringValue(Print& printer, char *value);    
    void intValue(Print& printer, int value);
    void floatValue(Print& printer, float value);    
    void booleanValue(Print& printer, boolean value);

    void stringProperty(Print& printer, char* name, char*value);
    void intProperty(Print& printer, char* name, int value);
    void floatProperty(Print& printer, char* name, float value);    
    void booleanProperty(Print& printer, char* name, boolean value);

    void comma(Print& printer);

    void newline(Print& printer);
};

#endif
