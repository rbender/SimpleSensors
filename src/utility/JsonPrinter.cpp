#include "Arduino.h"

#include "JsonPrinter.h"

JsonPrinter::JsonPrinter(Print& printer) {
  _printer = &printer;  
}
  
void JsonPrinter::startObject() {
  _printer->print("{");
}

void JsonPrinter::endObject() {
  _printer->print("}");
}

void JsonPrinter::startArray() {
  _printer->print("[");
}

void JsonPrinter::endArray() {
  _printer->print("]");
}

void JsonPrinter::property(char* name) {
  _printer->print("\"");
  _printer->print(name);
  _printer->print("\":");  
}

void JsonPrinter::stringValue(char *value) {
  _printer->print("\"");
  _printer->print(value);
  _printer->print("\"");
}

void JsonPrinter::intValue(int value) {
  _printer->print(value);  
}

void JsonPrinter::floatValue(float value) {
  _printer->print(value);  
}

void JsonPrinter::booleanValue(boolean value) {
  if (value == true) {
    _printer->print("true");
  } else {
    _printer->print("false");
  }
}

void JsonPrinter::stringProperty(char* name, char*value) {
	property(name);
	stringValue(value);
}

void JsonPrinter::intProperty(char* name, int value) {
	property(name);
	intValue(value);
}

void JsonPrinter::floatProperty(char* name, float value) {
	property(name);
	floatValue(value);
}

void JsonPrinter::booleanProperty(char* name, boolean value) {
	property(name);
	booleanValue(value);
}

void JsonPrinter::comma() {
  _printer->print(",");
}

void JsonPrinter::newline() {
  _printer->println();
}
