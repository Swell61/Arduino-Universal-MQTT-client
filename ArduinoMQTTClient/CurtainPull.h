// CurtainPull.h

#ifndef _CURTAINPULL_h
#define _CURTAINPULL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for curtain pull (or blind roller)
*/
class CurtainPull : public Output {
public:
	CurtainPull(const char* mqttListenTopic, const char* mqttRespondTopic, const byte pinNum);
	void action(MQTTDevice::ACTION action, PubSubClient mqttClient);
private:
	const byte pinNum;
};

#endif

