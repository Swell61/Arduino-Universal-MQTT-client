// Relay.h

#ifndef _RELAY_h
#define _RELAY_h
#include <Arduino.h>

#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for a relay output
*/
class Relay : public Output {
public:
	Relay(const char* mqttStateTopic, const char* mqttRespondTopic, const uint8_t pinNum, const bool activeHigh);

	void action(MQTTDevice::ACTION action, PubSubClient& mqttClient);
private:
	const uint8_t pinNum;
	const bool activeHigh = 1; // Some devices are active high, some are active low (internal pullup resistor used)
};

#endif

