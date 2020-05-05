// 
// 
// 

#include "Alarm.h"

Alarm::Alarm(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::ALARM, mqttListenTopic, mqttRespondTopic), pinNum(pinNum) {}

void Alarm::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case (INFO):
		break;
	case (CAUTION):
		break;
	case (WARNING):
		break;
	}
}
