// 
// 
// 

#include "CurtainPull.h"

CurtainPull::CurtainPull(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::CURTAIN_PULL, mqttListenTopic, mqttRespondTopic), pinNum(pinNum) {}

void CurtainPull::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
