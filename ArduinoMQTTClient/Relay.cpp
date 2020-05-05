// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum) : Output(MQTTDevice::DEVICE_TYPE::ALARM, mqttListenTopic, mqttRespondTopic), pinNum(pinNum) {}

void Relay::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case ON:
		Serial.println(F("Relay on"));
		digitalWrite(pinNum, HIGH);
		mqttClient.publish_P(getMQTTRespondTopic(), ON_TEXT, sizeof(ON_TEXT), false);
		break;
	case OFF:
		Serial.println(F("Relay off"));
		digitalWrite(pinNum, LOW);
		mqttClient.publish_P(getMQTTRespondTopic(), OFF_TEXT, sizeof(OFF_TEXT), false);
		break;
	}
}