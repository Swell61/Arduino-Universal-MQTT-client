// Switch.h

#ifndef _SWITCH_h
#define _SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for a switch input
*/
class Switch : public Input {
public:
	Switch(const MQTTDevice& mqttDevice);
	Switch(const char* deviceName, const byte pinNum);
	void sendMessage() override;
};

#endif

