// MQTTDevice.h

#ifndef _MQTTDEVICE_h
#define _MQTTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MQTTDevice {

	enum DEVICE_TYPE {
		RELAY,
		SWITCH,
		CONTACT,
		ALARM
	};

private:
	byte pinNumber; // Pin number device is on
	DEVICE_TYPE deviceType; // Type of device this instance represents

public:
	MQTTDevice(byte pinNumber, DEVICE_TYPE deviceType);

};

#endif

