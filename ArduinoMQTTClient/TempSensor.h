// TempSensor.h

#ifndef _TEMPSENSOR_h
#define _TEMPSENSOR_h

#include "Input.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for a temperature sensor input
*/
class TempSensor : public Input {
public:
	TempSensor(const char* deviceMQTTTopic, const byte pinNum);
	void handleInput(PubSubClient mqttClient) override;
private:
	const byte pinNum;
	const char* mqttStateTopic;
};

#endif

