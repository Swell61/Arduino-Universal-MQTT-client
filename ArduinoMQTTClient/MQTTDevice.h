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
const char PROGMEM ALARM_TEXT[] = { "alarm" };
const char PROGMEM MOTION_TEXT[] = { "motion" };
const char PROGMEM NO_MOTION_TEXT[] = { "noMotion" };
const char PROGMEM TAMPERED_TEXT[] = { "tampered" };
const char PROGMEM NORMAL_TEXT[] = { "normal" };

class MQTTDevice {

public:
	enum DEVICE_TYPE : byte {
		// Outputs
		RELAY,
		CURTAIN_PULL,
		ALARM_SIREN_STROBE,

		// Input
		SWITCH,
		CONTACT,
		TEMP_SENSOR,
		ALARM_MOTION_SENSOR,
	};

	enum ACTION : byte {
		OFF,
		ON,
		OPEN,
		CLOSE,
		INFO,
		CAUTION,
		WARNING,
		ALARM
	};

	const static actionStringToType actionStringsToTypes[8];
	
	
	
	MQTTDevice(const MQTTDevice::DEVICE_TYPE deviceType);
	const MQTTDevice::DEVICE_TYPE getDeviceType() { return deviceType; }

protected:
	const char* deviceMQTTTopic;
private:
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents
};

struct actionStringToType {
	actionStringToType(const char* string, MQTTDevice::ACTION type) : string(string), type(type) {}
	const char* string;
	MQTTDevice::ACTION type;
};

#endif

