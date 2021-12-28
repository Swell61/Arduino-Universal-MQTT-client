#include "LatchingRelayTwoPole.h"
#include <Arduino.h>

LatchingRelayTwoPole::LatchingRelayTwoPole(const char* mqttStateTopic, const char* mqttRespondTopic, const uint8_t setPoleNum,
     const uint8_t resetPoleNum) : Output(MQTTDevice::DEVICE_TYPE::LATCHING_RELAY, mqttStateTopic, mqttRespondTopic), setPoleNum(setPoleNum), 
     resetPoleNum(resetPoleNum)
     {
         pinMode(setPoleNum, OUTPUT);
         pinMode(resetPoleNum, OUTPUT);
     }

void LatchingRelayTwoPole::action(MQTTDevice::ACTION action, PubSubClient& mqttClient) {
	switch (action) {
	case MQTTDevice::ACTION::ON:
		toggleOn(mqttClient);
		break;
	case MQTTDevice::ACTION::OFF:
		toggleOff(mqttClient);
		break;
    case MQTTDevice::ACTION::TOGGLE:
        switch (lastState) {
            case LOW:
                toggleOn(mqttClient);
                break;
            case HIGH:
                toggleOff(mqttClient);
                break;
        }
        break;
    }
}

void LatchingRelayTwoPole::toggleOn(PubSubClient& mqttClient) {
    togglePole(setPoleNum);
	mqttClient.publish_P(getMQTTStateTopic(), (const uint8_t*)ON_TEXT, strlen_P(ON_TEXT), false);
    lastState = HIGH;
}

void LatchingRelayTwoPole::toggleOff(PubSubClient& mqttClient) {
    togglePole(resetPoleNum);
	mqttClient.publish_P(getMQTTStateTopic(), (const uint8_t*)OFF_TEXT, strlen_P(OFF_TEXT), false);
    lastState = LOW;
}

void LatchingRelayTwoPole::togglePole(uint8_t pinNum) {
    digitalWrite(pinNum, HIGH);
    delay(poleHoldTime); // Better to use interrupt but this is a quick implementation and (probably) uses less memory
    digitalWrite(pinNum, LOW);
}