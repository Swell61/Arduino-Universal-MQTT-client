// MQTTDevice.h

#ifndef _MQTTDEVICE_h
#define _MQTTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "IMQTTDevice.h"
/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Class represents any MQTT device hosted by this system
*/

class MQTTDevice : public IMQTTDevice {

public:
	enum DEVICE_TYPE {
		RELAY,
		SWITCH,
		CONTACT,
		ALARM
	};

	enum ACTION {
		OFF,
		ON,
		OPEN,
		CLOSE,
		INFO,
		CAUTION,
		WARNING,
	};

	byte getPinNum();
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents

protected:
	byte pinNum; // Pin number device is on
	char* deviceName;
};


#endif

