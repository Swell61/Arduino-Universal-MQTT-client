// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* deviceMQTTTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::RELAY, deviceMQTTTopic), pinNum(pinNum) {}

void Relay::action(MQTTDevice::ACTION action) {
	switch (action) {
	case ON:
		Serial.println(F("Relay on"));
		digitalWrite(pinNum, HIGH);
		break;
	case OFF:
		Serial.println(F("Relay off"));
		digitalWrite(pinNum, LOW);
		break;
	}
}