#include "Arduino.h"

#ifndef JsonPrinter_h
#define JsonPrinter_h

class JsonPrinter {
  
  public:
  
    JsonPrinter(Print& printer);
      
    void startObject();
    void endObject();
    
    void startArray();    
    void endArray();
    
    void property(char* name);
    
    void stringValue(char *value);    
    void intValue(int value);
    void floatValue(float value);    
    void booleanValue(boolean value);
    
    void comma();
    
    void newline();
    
  private:
    
    Print* _printer;
};

#endif
