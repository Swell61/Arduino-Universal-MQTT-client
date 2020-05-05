// 
// 
// 

#include "Output.h"

Output::Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttListenTopic, const char* mqttRespondTopic) : MQTTDevice(deviceType), mqttListenTopic(mqttListenTopic), 
mqttRespondTopic(mqttRespondTopic) {}

const char* Output::getMQTTListenTopic() {
	return getProgmemString(mqttListenTopic);
}

const char* Output::getMQTTRespondTopic() {
	return getProgmemString(mqttRespondTopic);
}