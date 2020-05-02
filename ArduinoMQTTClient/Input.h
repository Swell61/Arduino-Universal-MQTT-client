// Input.h

#ifndef _INPUT_h
#define _INPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "MQTTDevice.h"
#include <../pubsubclient/src/PubSubClient.h>

/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Abstract class for an MQTT device that is an input to the system
*/

struct inputChange {
	uint8_t pinChanged : 1;
	uint8_t pinChangedTo : 1;
};

class Input : public MQTTDevice {
public:
	Input(const MQTTDevice& mqttDevice);
	Input(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum);
	virtual void handleInput(PubSubClient mqttClient) = 0;
	
	
	static void interruptHandler();
protected:
	volatile inputChange inputChange = {0, 0};
	static Input* inputs[19];
};


#endif

