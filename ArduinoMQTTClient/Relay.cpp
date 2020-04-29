// 
// 
// 

#include "Relay.h"
Relay::Relay(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

void Relay::action(MQTTDevice::ACTION action) {
	switch (action) {
	case ON:
		digitalWrite(getPinNum(), HIGH);
		break;
	case OFF:
		digitalWrite(getPinNum(), LOW);
		break;
	}
}