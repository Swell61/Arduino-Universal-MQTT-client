// 
// 
// 

#include "Alarm.h"

Alarm::Alarm(const char* deviceMQTTTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::ALARM, deviceMQTTTopic), pinNum(pinNum) {}

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
