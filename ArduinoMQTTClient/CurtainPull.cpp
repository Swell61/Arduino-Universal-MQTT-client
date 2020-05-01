// 
// 
// 

#include "CurtainPull.h"
CurtainPull::CurtainPull(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

CurtainPull::CurtainPull(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Output(deviceName, deviceType, pinNum) {}

void CurtainPull::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
