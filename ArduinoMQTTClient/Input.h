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

	// This is called once per main loop iteration on each input device. Allows each device to process any changes of state or to send updates out after a certain time period, etc.
	virtual void handleInput(PubSubClient mqttClient) = 0;
protected:
	unsigned long lastProcessedMillis = 0; // Time (in millis) since an input was last handled by each Input device

	const static byte DEBOUNCE_TIME_MILLIS = 100; // A standard debounce time for ignoring erronious changes (e.g. in a switch with a dirty contact)

	// Returns true if debounce period is up, false otherwise.
	bool debounce();
};


#endif

