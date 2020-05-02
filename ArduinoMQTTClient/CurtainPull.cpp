// 
// 
// 

#include "CurtainPull.h"
CurtainPull::CurtainPull(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

CurtainPull::CurtainPull(const char* deviceName, const byte pinNum) : Output(deviceName, MQTTDevice::DEVICE_TYPE::CURTAIN_PULL, pinNum) {}

void CurtainPull::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
