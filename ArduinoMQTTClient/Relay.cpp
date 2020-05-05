// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* deviceMQTTTopic, const byte pinNum) : Output(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::RELAY, pinNum) {}

void Relay::action(MQTTDevice::ACTION action) {
	switch (action) {
	case ON:
		Serial.println(F("Relay on"));
		digitalWrite(getPinNum(), HIGH);
		break;
	case OFF:
		Serial.println(F("Relay off"));
		digitalWrite(getPinNum(), LOW);
		break;
	}
}