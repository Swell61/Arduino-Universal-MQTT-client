// 
// 
// 

#include "Output.h"

Output::Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttStateTopic, const char* mqttRespondTopic) : MQTTDevice(deviceType), mqttStateTopic(mqttStateTopic), 
mqttRespondTopic(mqttRespondTopic) {}

const char* Output::getMQTTListenTopic() {
	return getProgmemString(mqttStateTopic);
}

const char* Output::getMQTTStateTopic() {
	return getProgmemString(mqttRespondTopic);
}