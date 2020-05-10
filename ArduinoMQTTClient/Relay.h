// Relay.h

#ifndef _RELAY_h
#define _RELAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for a relay output
*/
class Relay : public Output {
public:
	Relay(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum, const bool activeHigh);
	void action(MQTTDevice::ACTION action, PubSubClient mqttClient);
private:
	const byte pinNum;
	const bool activeHigh = 1;
};

#endif

