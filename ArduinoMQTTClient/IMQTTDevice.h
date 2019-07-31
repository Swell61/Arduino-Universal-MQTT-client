// IMQTTDevice.h
#ifndef _IMQTTDEVICE_h
#define _IMQTTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Interface for any MQTT device
*/

class IMQTTDevice {
private:
	byte pinNumber; // Pin number device is on
	MQTTDevice::DEVICE_TYPE deviceType; // Type of device this instance represents

public:
	virtual void action() = 0;

};

#endif

