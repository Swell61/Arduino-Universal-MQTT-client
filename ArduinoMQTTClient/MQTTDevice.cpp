// 
// 
// 

#include "MQTTDevice.h"

const actionStringToType MQTTDevice::actionStringsToTypes[7] = { {"off", MQTTDevice::ACTION::OFF}, { "on", MQTTDevice::ACTION::ON },
{"open", MQTTDevice::ACTION::OPEN}, {"close", MQTTDevice::ACTION::CLOSE}, {"info", MQTTDevice::ACTION::INFO}, {"caution", MQTTDevice::ACTION::CAUTION}, {"warning", MQTTDevice::ACTION::WARNING} };

MQTTDevice::MQTTDevice(const MQTTDevice& mqttDevice) : deviceMQTTTopic(mqttDevice.deviceMQTTTopic), pinNum(mqttDevice.pinNum), deviceType(mqttDevice.deviceType) { }

MQTTDevice::MQTTDevice(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : deviceMQTTTopic(deviceMQTTTopic), pinNum(pinNum), deviceType(deviceType) { }

