// 
// 
// 

#include "Relay.h"
Relay::Relay(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

Relay::Relay(const char* deviceMQTTTopic, const byte pinNum) : Output(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::RELAY, pinNum) {}

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