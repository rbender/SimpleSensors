# Simple Sensor Library

This project is an object-oriented Arduino library for reading sensor values and outputting them over a serial port as JSON (or other formats).

The root datatype is SimpleSensor, with subclasses for generic analog and digital sensors as well as subclasses for specific sensor hardware (eg: TMP36) 

Each SimpleSensor has the following properties:
- short identifier
- name
- type (eg: "temperature", "light", "humidity", etc)
- pin number
- units (eg: "volts", "lumens", "F", etc)

SimpleSensors are collected into a SensorCollection object which performs batch operations on the sensors (setup, reading, etc).

##To-Do

- More documentation
- More sensor subtypes
- Support for sending values over a network (HTTP, MQTT, etc)
- Support for sending values via XBee
- Support for I2C sensors
- Break the code for emitting sensor values out from SensorCollection