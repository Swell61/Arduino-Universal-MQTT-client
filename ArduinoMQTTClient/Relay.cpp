// 
// 
// 

#include "Relay.h"
Relay::Relay(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

Relay::Relay(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Output(deviceName, deviceType, pinNum) {}

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