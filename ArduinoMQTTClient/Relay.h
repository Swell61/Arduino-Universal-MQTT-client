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
	Relay(const char* deviceMQTTTopic, const byte pinNum);
	void action(MQTTDevice::ACTION action);
};

#endif

