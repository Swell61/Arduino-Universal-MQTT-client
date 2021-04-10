// AlarmMotionSensor.h

#ifndef _ALARMMOTIONSENSOR_h
#define _ALARMMOTIONSENSOR_h

#include "Input.h"
#include "Contact.h"

/*
	Author: Samuel Bailey
	Date: 05/05/2020
	Purpose: Motion sensor that contains a PIR sensor to detect motion, and a tamper switch to detect if someone is trying to dissassemble the motion sensor while it is active. Both
				devices are 'normal' (i.e. no motion and no tamper) when the circuit is closed. If the circuit is broken, the devices trigger (this is incase the wires are cut).
*/

class AlarmMotionSensor : public Input {
public:
	AlarmMotionSensor(const char* pirSensorMQTTTopic, const char* tamperSwitchMQTTTopic, const byte pirSensorPinNum, const byte tamperSwitchPinNum, const char* pirSensorMotionMessage,
		const char* pirSensorNoMotionMessage, const char* tamperSwitchTriggeredMessage, const char* tamperSwitchUntriggeredMessage);
	void handleInput(PubSubClient& mqttClient);
private:
	Contact pirSensor;
	Contact tamperSwitch;
};

#endif

