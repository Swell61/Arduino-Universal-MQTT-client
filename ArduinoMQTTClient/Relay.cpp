// 
// 
// 

#include "Relay.h"
Relay::Relay(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}

Relay::Relay(char const *const deviceName, const byte pinNum) : Output(deviceName, MQTTDevice::DEVICE_TYPE::RELAY, pinNum) {}

void Relay::action(MQTTDevice::ACTION action) {
	switch (action) {
	case ON:
		digitalWrite(getPinNum(), HIGH);
		Serial.println("Relay on");
		break;
	case OFF:
		digitalWrite(getPinNum(), LOW);
		Serial.println("Relay off");
		break;
	}
}