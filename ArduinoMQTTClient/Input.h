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
class Input : public MQTTDevice {
public:
	Input(const MQTTDevice::DEVICE_TYPE deviceType);
	virtual void handleInput(PubSubClient mqttClient) = 0;
protected:
	unsigned long lastProcessedMillis = 0;
	const static byte DEBOUNCE_TIME_MILLIS = 100;

	bool debounce();
};


#endif

