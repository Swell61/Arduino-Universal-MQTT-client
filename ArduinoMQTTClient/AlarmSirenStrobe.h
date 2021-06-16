// AlarmSirenStrobe.h

#ifndef _ALARMSIRENSTROBE_h
#define _ALARMSIRENSTROBE_h
#include <Arduino.h>

#include "Relay.h"
#include "Contact.h"
/*
	Author: Samuel Bailey
	Date: 09/05/2020
	Purpose: This is an output and an input. An alarm siren and strobe combo is mostly thought of as an output, it has been put in the output folder, even though it has a tamper switch input.
 */
class AlarmSirenStrobe : public Input, public Output {
public:
	AlarmSirenStrobe(const char* alarmMqttCommandTopic, const char* alarmMqttStateTopic, const char* tamperMqttStateTopic, const char* tamperHighMessage, 
		const char* tamperLowMessage, const uint8_t sirenPinNum, const uint8_t strobePinNum, const uint8_t tamperSwitchPinNum);
	void action(MQTTDevice::ACTION action, PubSubClient& mqttClient);
	void handleInput(PubSubClient& mqttClient);

private:
	const uint8_t sirenPinNum;
	const uint8_t strobePinNum;
	Contact tamperSwitch;
};

#endif

