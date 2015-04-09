# Simple Sensor Library

This project is an object-oriented Arduino library for reading sensor values and outputting them to other systems. 

Sensors are configured with metadata, such as a short id, a name, type and the units of measurement used.  Sensors are gathered into a SensorCollection, which also has its own short id and name. SensorStreamers then read the values of the sensors and output them to a serial or network connection.

## Object Model 

The root abstract class is `SimpleSensor` and has the following properties:

- `id`: short machine readable identifier, suitable for lookups or queries
- `name`: name that could be displayed to a user
- `type`: type of data the sensor is reading, such as temperature, humidity, motion, etc
- `units`: unit of measurement, such as volts, lumens, degrees-F, degrees-C, etc (optional)

SimpleSensors also have the following methods:

- `readRaw()`: returns the raw value from the sensor as an integer
- `read()`: returns the calculated meaurement (eg: temperature, distance) from the sensor as a float
- `convertRaw(int raw)`: Converts the raw value into a calculated measurement. This is used internally by read() and also used to report both raw and calculated values for a sensor withotu having to read the data twice, which is more efficient and prevents inconsistency if the sensor value changed between the two reads.
- `setup()`: Initializes a sensor, such as setting the pinMode

There are `AnalogSensor` and `DigitalSensor` subclasses, for reading values from analog or digital pins respectively. Each has a `pin` property. There are also subclasses for specific sensor hardware (eg: TMP36) .

The `SensorCollection` object contains an array of SimpleSensors, along with a short `id` and human-readable `name`. (Future idea: Add optional "location" property.) It also has the following methods:

- `setup()`: Calls the `setup` method of each sensor.
- `addSensor(SimpleSensor& sensor)`: Adds a sensor to the collection
- `getSensor(int index)`: Gets a sensor by its index in the array. Useful for looping over the sensors in the collection.
- `getSensor(char* id)`: Gets a sensor by its short id.

Sensor data is read and output via SensorStreamers. The library currently includers two streamer implementations: One that outputs plain text and one that outputs JSON. Both use the Arduino "Print" interface which is supported by Serial connections and other libraries.

A separate project will support streaming sensor data over Ethernet and WiFi.

##JSON Format

The JSON representation of a SensorCollection is all on one line, without extra whitespace. This keeps it compact and a clien can simply do a readLine to read an entire record. The library doesn't do any escaping of JSON fields, so sensor ids, names, etc should not include double-quotes, slashes or other special characters.

This is an example, passed through a pretty-printer for legibility:

	{
	  "id": "example",
	  "name": "Example Sensor Collection",
	  "sensors": [
	    {
	      "id": "light",
	      "name": "Light",
	      "type": "light",
	      "value": 0.14,
	      "raw_value": 28
	    },
	    {
	      "id": "temp",
	      "name": "Temperature",
	      "type": "temperature",
	      "value": 0.14,
	      "raw_value": 28
	    }
	  ]
	}

## Limitations

SimpleSensors return a single floating-point value, which is fine for things like temperature, humidity or baromatric pressure. This does not work well for more complex sensors where a reading is comprised of multiple values, such as accelerometer that returns X,Y and Z values. A workaround would be to create three sensor objects, one for each axis.

Likewise floating-point numbers aren't an intuitive data type for sensors that report on/off values such as buttons, switches or motion sensors.

The SensorCollection uses a hardcoded MAX_SENORS constant for the maximum number of sensors, which is then used to create its internal array of sensors.
##Future Improvements

- More documentation and source code comments
- More sensor subtypes
- Support for I2C sensors
- Triggers (so sensor data in transmitted when values change, instead of using timed intervals)
- XML output format
- Make MAX_SENSORS configurable or dynamic.

I envision SimpleSensors as being part of a larger framework for building sensor devices and collecting their data. I hope to build libraries for transmitting sensor data over HTTP, XBee, MQTT, etc. There will also need to be code for consuming the sensor data, storing it, graphing it, sending it to the cloud, etc. 

