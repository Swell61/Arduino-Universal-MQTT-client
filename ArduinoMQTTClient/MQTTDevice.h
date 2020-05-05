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
static char progmemBuffer[15] = { '\0' };
const char* getProgmemString(const char* progmemStringLocation);
const char PROGMEM OPEN_TEXT[] = { "open" };
const char PROGMEM CLOSE_TEXT[] = { "close" };
const char PROGMEM ON_TEXT[] = { "on" };
const char PROGMEM OFF_TEXT[] = { "off" };
const char PROGMEM INFO_TEXT[] = { "info" };
const char PROGMEM CAUTION_TEXT[] = { "caution" };
const char PROGMEM WARNING_TEXT[] = { "warning" };

class MQTTDevice {

public:
	enum DEVICE_TYPE : byte {
		// Outputs
		RELAY,
		ALARM,
		CURTAIN_PULL,

		// Input
		SWITCH,
		CONTACT,
		TEMP_SENSOR,
	};

	enum ACTION : byte {
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
	
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents
	MQTTDevice(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum);
	const char* getDeviceMQTTTopic() { return getProgmemString(deviceMQTTTopic); };

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

