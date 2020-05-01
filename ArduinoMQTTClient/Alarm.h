// Alarm.h

#ifndef _ALARM_h
#define _ALARM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Provides alarm specific functionality as an output MQTT device
*/
class Alarm : public Output {
public:
	Alarm(const MQTTDevice& mqttDevice);
	Alarm(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum);
	void action(MQTTDevice::ACTION action);
};

#endif

