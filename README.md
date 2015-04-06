# Simple Sensor Library

This project is an object-oriented Arduino library for reading sensor values and outputting them to other systems.

The root datatype is SimpleSensor, with subclasses for generic analog and digital sensors as well as subclasses for specific sensor hardware (eg: TMP36) 

Each SimpleSensor has the following properties:
- short identifier
- name
- type (eg: "temperature", "light", "humidity", etc)
- pin number
- units (eg: "volts", "lumens", "F", etc)

SimpleSensors are collected into a SensorCollection object which performs batch operations on the sensors (setup, reading, etc). SensorCollections also have an id and name.

Sensor data is read and output via Emitters. The library currently includers two emitter implementations: One that outputs plain text and one that outputs JSON. Both use the Arduino "Print" interface which is supported by Serial connections and other libraries.

A separate project will support emitting over Ethernet and WiFi.

##To-Do

- More documentation
- More sensor subtypes
- Support for sending values over a network (HTTP, MQTT, etc)
- Support for sending values via XBee
- Support for I2C sensors
- Break the code for emitting sensor values out from SensorCollection