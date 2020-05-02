// 
// 
// 

#include "Alarm.h"
Alarm::Alarm(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

Alarm::Alarm(const char* deviceMQTTTopic, const byte pinNum) : Output(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::ALARM, pinNum) {}

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
