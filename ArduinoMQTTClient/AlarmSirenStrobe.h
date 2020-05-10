// AlarmSirenStrobe.h

#ifndef _ALARMSIRENSTROBE_h
#define _ALARMSIRENSTROBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Relay.h"
#include "Contact.h"
/*
	Author: Samuel Bailey
	Date: 09/05/2020
	Purpose: This is an output and an input. An alarm siren and strobe combo is mostly thought of as an output, it has been put in the output folder, even though it has a tamper switch input.
 */
class AlarmSirenStrobe : public Input, public Output {
public:
	AlarmSirenStrobe(const char* alarmMqttCommandTopic, const char* alarmMqttStateTopic, const char* tamperMqttStateTopic, const char* tamperHighMessage, const char* tamperLowMessage, 
		const byte sirenPinNum, const byte strobePinNum, const byte tamperSwitchPinNum);
	void action(MQTTDevice::ACTION action, PubSubClient mqttClient);
	void handleInput(PubSubClient mqttClient);

private:
	const byte sirenPinNum;
	const byte strobePinNum;
	Contact tamperSwitch;
};

#endif

