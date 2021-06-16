// MQTTDevice.h

#ifndef _MQTTDEVICE_h
#define _MQTTDEVICE_h
#include <Arduino.h>

/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Class represents any MQTT device hosted by this system
*/

struct actionStringToType; // forward declare
static char progmemBuffer[22] = { '\0' }; // Buffer to use when reading from program flash memory
const char* getProgmemString(const char* progmemStringLocation); // Takes in a progmem address for a string and returns the start address of a null-terminated buffer containing the string

// String representations of actions
const char PROGMEM OPEN_TEXT[] = { "open" };
const char PROGMEM CLOSE_TEXT[] = { "close" };
const char PROGMEM ON_TEXT[] = { "on" };
const char PROGMEM OFF_TEXT[] = { "off" };
const char PROGMEM TOGGLE_TEXT[] = { "toggle" };
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
	enum DEVICE_TYPE : uint8_t {
		// Outputs
		RELAY,
		CURTAIN_PULL,
		ALARM_SIREN_STROBE,
		LATCHING_RELAY,

		// Input
		SWITCH,
		CONTACT,
		TEMP_SENSOR,
		ALARM_MOTION_SENSOR,
	};

	enum ACTION : uint8_t {
		OFF,
		ON,
		OPEN,
		CLOSE,
		INFO,
		CAUTION,
		WARNING,
		ALARM,
		TOGGLE
	};

	const static actionStringToType actionStringsToTypes[9]; // Needs to be updated when a new action type is added
	
	MQTTDevice(const MQTTDevice::DEVICE_TYPE deviceType);
	const MQTTDevice::DEVICE_TYPE getDeviceType() { return deviceType; }

private:
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents
};

// Points a string to its equivelant enum
struct actionStringToType {
	actionStringToType(const char* string, MQTTDevice::ACTION type) : string(string), type(type) {}
	const char* string;
	MQTTDevice::ACTION type;
};


#endif

