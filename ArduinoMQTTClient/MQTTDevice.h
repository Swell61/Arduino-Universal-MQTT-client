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
struct actionStringToType;
class MQTTDevice {

public:
	PROGMEM enum DEVICE_TYPE : byte {
		// Outputs
		RELAY,
		ALARM,
		CURTAIN_PULL,

		// Input
		SWITCH,
		CONTACT,
		TEMP_SENSOR,
	};

	PROGMEM enum ACTION : byte {
		OFF,
		ON,
		OPEN,
		CLOSE,
		INFO,
		CAUTION,
		WARNING,
	};

	const static actionStringToType actionStringsToTypes[7];
	
	const byte getPinNum() { return pinNum; }
	const char* getDeviceMQTTTopic() { return deviceMQTTTopic; }
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents
	MQTTDevice(const MQTTDevice &mqttDevice);
	MQTTDevice(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum);
	

protected:
	const byte pinNum; // Pin number device is on
	const char* deviceMQTTTopic;
};

struct actionStringToType {
	actionStringToType(const char* string, MQTTDevice::ACTION type) : string(string), type(type) {}
	const char* string;
	MQTTDevice::ACTION type;
};

#endif

