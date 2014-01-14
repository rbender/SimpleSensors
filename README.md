Simple Sensor Library
=====================

This project is an object-oriented Arduino library for
reading sensor values and outputting them over a serial port
as JSON (or other formats).

Each SimpleSensor object has a sub-type (AnalogSensor or DigitalSensor),
pin number and a short name

SimpleSensors are collected into a SensorCollection object
which performs batch operations on the sensors (setup, reading, etc)

To-Do
-----
- Documentation
- More sensor subtypes
- Conversion of raw sensor data
- Handle external AREF