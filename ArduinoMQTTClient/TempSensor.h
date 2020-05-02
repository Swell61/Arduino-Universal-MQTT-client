// TempSensor.h

#ifndef _TEMPSENSOR_h
#define _TEMPSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for a temperature sensor input
*/
class TempSensor : public Input {
public:
	TempSensor(const MQTTDevice& mqttDevice);
	TempSensor(char const *const deviceName, const byte pinNum);
	void handleInput() override;
};

#endif

