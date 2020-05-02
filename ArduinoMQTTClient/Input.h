// Input.h

#ifndef _INPUT_h
#define _INPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "MQTTDevice.h"


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
	Input(char const *const deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum);
	virtual void sendMessage() = 0;
	volatile inputChange inputChange = {0, 0};
	static Input* inputs[19];
	static void interruptHandler();
};


#endif

