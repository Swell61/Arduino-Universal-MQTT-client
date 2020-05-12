// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* mqttStateTopic, const char* mqttRespondTopic, const byte pinNum, const bool activeHigh) : Output(MQTTDevice::DEVICE_TYPE::RELAY, mqttStateTopic, mqttRespondTopic), 
pinNum(pinNum), activeHigh(activeHigh) {}

void Relay::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case ON:
		Serial.println(F("Relay on"));
		digitalWrite(pinNum, activeHigh); // Set correct state depending on activeHigh
		mqttClient.publish_P(getMQTTStateTopic(), ON_TEXT, strlen_P(ON_TEXT), false);
		break;
	case OFF:
		Serial.println(F("Relay off"));
		digitalWrite(pinNum, !activeHigh); // Set correct state depending on activeHigh
		mqttClient.publish_P(getMQTTStateTopic(), OFF_TEXT, strlen_P(OFF_TEXT), false);
		break;
	}
}