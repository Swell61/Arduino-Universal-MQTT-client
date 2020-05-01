// 
// 
// 

#include "Alarm.h"
Alarm::Alarm(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

Alarm::Alarm(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Output(deviceName, deviceType, pinNum) {}

void Alarm::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (INFO):
		break;
	case (CAUTION):
		break;
	case (WARNING):
		break;
	}
}
