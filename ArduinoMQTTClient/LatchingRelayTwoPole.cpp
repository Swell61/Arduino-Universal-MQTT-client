#include "LatchingRelayTwoPole.h"
#include <Arduino.h>

LatchingRelayTwoPole::LatchingRelayTwoPole(const char* mqttStateTopic, const char* mqttRespondTopic, const unsigned short int setPoleNum,
     const unsigned short int resetPoleNum) : Output(MQTTDevice::DEVICE_TYPE::LATCHING_RELAY, mqttStateTopic, mqttRespondTopic), setPoleNum(setPoleNum), 
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
            case HIGH:
                toggleOff(mqttClient);
        }
        break;
    }
}

void LatchingRelayTwoPole::toggleOn(PubSubClient& mqttClient) {
    togglePole(setPoleNum);
	mqttClient.publish_P(getMQTTStateTopic(), ON_TEXT, strlen_P(ON_TEXT), false);
    lastState = HIGH;
}

void LatchingRelayTwoPole::toggleOff(PubSubClient& mqttClient) {
    togglePole(resetPoleNum);
	mqttClient.publish_P(getMQTTStateTopic(), OFF_TEXT, strlen_P(OFF_TEXT), false);
    lastState = LOW;
}

void LatchingRelayTwoPole::togglePole(unsigned short int pinNum) {
    digitalWrite(setPoleNum, HIGH);
    delay(poleHoldTime); // Better to use interrupt but this is a quick implementation and (probably) uses less memory
    digitalWrite(setPoleNum, LOW);
}