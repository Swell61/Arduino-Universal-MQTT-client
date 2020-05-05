// 
// 
// 

#include "Output.h"

Output::Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttTopic) : MQTTDevice(deviceType), mqttTopic(mqttTopic) {}

const char* Output::getMQTTTopic() {
	return getProgmemString(mqttTopic);
}