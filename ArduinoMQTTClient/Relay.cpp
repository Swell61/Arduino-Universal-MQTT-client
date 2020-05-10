// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum, const bool activeHigh) : Output(MQTTDevice::DEVICE_TYPE::RELAY, mqttListenTopic, mqttRespondTopic), 
pinNum(pinNum), activeHigh(activeHigh) {}

void Relay::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case ON:
		Serial.println(F("Relay on"));
		digitalWrite(pinNum, activeHigh);
		mqttClient.publish_P(getMQTTRespondTopic(), ON_TEXT, strlen_P(ON_TEXT), false);
		break;
	case OFF:
		Serial.println(F("Relay off"));
		digitalWrite(pinNum, !activeHigh);
		mqttClient.publish_P(getMQTTRespondTopic(), OFF_TEXT, strlen_P(OFF_TEXT), false);
		break;
	}
}