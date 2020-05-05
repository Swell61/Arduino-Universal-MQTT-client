// 
// 
// 

#include "MQTTDevice.h"

const actionStringToType MQTTDevice::actionStringsToTypes[7] = { {OFF_TEXT, MQTTDevice::ACTION::OFF}, { ON_TEXT, MQTTDevice::ACTION::ON },
{OPEN_TEXT, MQTTDevice::ACTION::OPEN}, {CLOSE_TEXT, MQTTDevice::ACTION::CLOSE}, {INFO_TEXT, MQTTDevice::ACTION::INFO}, {CAUTION_TEXT, MQTTDevice::ACTION::CAUTION}, 
{WARNING_TEXT, MQTTDevice::ACTION::WARNING} };

const char* getProgmemString(const char* progmemStringLocation) {
	return strncpy_P(progmemBuffer, progmemStringLocation, sizeof(progmemBuffer));
}

MQTTDevice::MQTTDevice(const char* deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : deviceMQTTTopic(deviceMQTTTopic), pinNum(pinNum), deviceType(deviceType) { }