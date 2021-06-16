// 
// 
// 

#include "MQTTDevice.h"

const actionStringToType MQTTDevice::actionStringsToTypes[9] = { {OFF_TEXT, MQTTDevice::ACTION::OFF}, {ON_TEXT, MQTTDevice::ACTION::ON},
{OPEN_TEXT, MQTTDevice::ACTION::OPEN}, {CLOSE_TEXT, MQTTDevice::ACTION::CLOSE}, {INFO_TEXT, MQTTDevice::ACTION::INFO}, {CAUTION_TEXT, MQTTDevice::ACTION::CAUTION}, 
{WARNING_TEXT, MQTTDevice::ACTION::WARNING}, {ALARM_TEXT, MQTTDevice::ACTION::ALARM}, {TOGGLE_TEXT, MQTTDevice::ACTION::TOGGLE} };

// Returns a pointer to a null-terminated string (char array) of the string contained in the given memory location in program flash memory
const char* getProgmemString(const char* progmemStringLocation) {
	return strcpy_P(progmemBuffer, progmemStringLocation); // Will be null terminated as strings in PROGMEM are all literal, which have null terminators
}

MQTTDevice::MQTTDevice(const MQTTDevice::DEVICE_TYPE deviceType) : deviceType(deviceType) { }