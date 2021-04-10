// 
// 
// 

#include "Output.h"

Output::Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttListenTopic, const char* mqttRespondTopic) : MQTTDevice(deviceType), mqttListenTopic(mqttListenTopic), 
mqttRespondTopic(mqttRespondTopic) {}

void Output::subscribe(PubSubClient mqttClient) {
	mqttClient.subscribe(mqttListenTopic);
}

const char* Output::getMQTTListenTopic() {
	return getProgmemString(mqttListenTopic);
}

const char* Output::getMQTTStateTopic() {
	return getProgmemString(mqttRespondTopic);
}