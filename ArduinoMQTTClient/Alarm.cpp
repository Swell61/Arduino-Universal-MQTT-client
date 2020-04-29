// 
// 
// 

#include "Alarm.h"
Alarm::Alarm(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

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
