// 
// 
// 

#include "CurtainPull.h"

CurtainPull::CurtainPull(const char* mqttStateTopic, const char* mqttRespondTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::CURTAIN_PULL, mqttStateTopic, mqttRespondTopic), pinNum(pinNum) {}

void CurtainPull::action(MQTTDevice::ACTION action, PubSubClient& mqttClient) {
	// Not yet implemented
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
