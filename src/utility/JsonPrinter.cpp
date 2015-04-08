#include "Arduino.h"

#include "JsonPrinter.h"
  
void JsonPrinter::startObject(Print& printer) {
    printer.print("{");
}

void JsonPrinter::endObject(Print& printer) {
    printer.print("}");
}

void JsonPrinter::startArray(Print& printer) {
    printer.print("[");
}

void JsonPrinter::endArray(Print& printer) {
    printer.print("]");
}

void JsonPrinter::property(Print& printer, char* name) {
    printer.print("\"");
    printer.print(name);
    printer.print("\":");  
}

void JsonPrinter::stringValue(Print& printer, char *value) {
    printer.print("\"");
    printer.print(value);
    printer.print("\"");
}

void JsonPrinter::intValue(Print& printer, int value) {
    printer.print(value);  
}

void JsonPrinter::floatValue(Print& printer, float value) {
    printer.print(value);  
}

void JsonPrinter::booleanValue(Print& printer, boolean value) {
    if (value == true) {
        printer.print("true");
    } else {
        printer.print("false");
    }
}

void JsonPrinter::stringProperty(Print& printer, char* name, char*value) {
    property(printer, name);
    stringValue(printer, value);
}

void JsonPrinter::intProperty(Print& printer, char* name, int value) {
    property(printer, name);
    intValue(printer, value);
}

void JsonPrinter::floatProperty(Print& printer, char* name, float value) {
    property(printer, name);
    floatValue(printer, value);
}

void JsonPrinter::booleanProperty(Print& printer, char* name, boolean value) {
    property(printer, name);
    booleanValue(printer, value);
}

void JsonPrinter::comma(Print& printer) {
    printer.print(",");
}

void JsonPrinter::newline(Print& printer) {
    printer.println();
}

