// Output.h

#ifndef _OUTPUT_h
#define _OUTPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "MQTTDevice.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Abstract class for any MQTTDevices that are outputs for the system
*/
class Output : public MQTTDevice {

public:
	char* getDeviceName();
};

#endif

