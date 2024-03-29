// 
// 
// 

#include "Relay.h"

Relay::Relay(const char* mqttStateTopic, const char* mqttRespondTopic, const uint8_t pinNum, const bool activeHigh) : Output(MQTTDevice::DEVICE_TYPE::RELAY, mqttStateTopic, mqttRespondTopic), 
pinNum(pinNum), activeHigh(activeHigh) {
	pinMode(pinNum, OUTPUT);
}

void Relay::action(MQTTDevice::ACTION action, PubSubClient& mqttClient) {
	switch (action) {
	case MQTTDevice::ACTION::ON:
		digitalWrite(pinNum, activeHigh); // Set correct state depending on activeHigh
		mqttClient.publish_P(getMQTTStateTopic(), (const uint8_t*)ON_TEXT, strlen_P(ON_TEXT), false);
		break;
	case MQTTDevice::ACTION::OFF:
		digitalWrite(pinNum, !activeHigh); // Set correct state depending on activeHigh
		mqttClient.publish_P(getMQTTStateTopic(), (const uint8_t*)OFF_TEXT, strlen_P(OFF_TEXT), false);
		break;
	}
}