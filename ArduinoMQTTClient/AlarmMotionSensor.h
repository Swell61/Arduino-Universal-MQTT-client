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

