// MQTTDevice.h

#ifndef _MQTTDEVICE_h
#define _MQTTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Class represents any MQTT device hosted by this system
*/

class MQTTDevice {

public:
	enum DEVICE_TYPE {
		RELAY,
		SWITCH,
		CONTACT,
		ALARM
	};

	MQTTDevice(byte pinNumber, DEVICE_TYPE deviceType);

protected:
	byte pinNum; // Pin number device is on
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents
};


#endif

