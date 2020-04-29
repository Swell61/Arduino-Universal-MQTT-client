// 
// 
// 

#include "MQTTDevice.h"

MQTTDevice::MQTTDevice(const MQTTDevice& mqttDevice) {
	this->pinNum = mqttDevice.pinNum;
	strncpy(this->deviceName, mqttDevice.deviceName, 8);
	this->deviceType = mqttDevice.deviceType;
}

byte MQTTDevice::getPinNum() {
	return pinNum;
}
