// 
// 
// 

#include "MQTTDevice.h"

MQTTDevice::MQTTDevice(const MQTTDevice& mqttDevice) : deviceName(mqttDevice.deviceName), pinNum(mqttDevice.pinNum), deviceType(mqttDevice.deviceType) { }

MQTTDevice::MQTTDevice(const char* const deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : deviceName(deviceName), pinNum(pinNum), deviceType(deviceType) { }

byte MQTTDevice::getPinNum() {
	return pinNum;
}
