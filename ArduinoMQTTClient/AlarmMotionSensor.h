// AlarmMotionSensor.h

#ifndef _ALARMMOTIONSENSOR_h
#define _ALARMMOTIONSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
#include "Contact.h"

/*
	Author: Samuel Bailey
	Date: 05/05/2020
	Purpose: Motion sensor that contains a PIR sensor to detect motion, and a tamper switch to detect if someone is trying to dissassemble the motion sensor while it is active.
*/

class AlarmMotionSensor : public Input {
public:
	AlarmMotionSensor(const char* pirSensorMQTTTopic, const char* tamperSwitchMQTTTopic, const byte pirSensorPinNum, const byte tamperSwitchPinNum, const char* pirSensorMotionMessage,
		const char* pirSensorNoMotionMessage, const char* tamperSwitchTriggeredMessage, const char* tamperSwitchUntriggeredMessage);
	void handleInput(PubSubClient mqttClient);
private:
	Contact pirSensor;
	Contact tamperSwitch;
};

#endif

