// 
// 
// 

#include "CurtainPull.h"

CurtainPull::CurtainPull(const char* deviceMQTTTopic, const byte pinNum) : Output(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::CURTAIN_PULL, pinNum) {}

void CurtainPull::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
