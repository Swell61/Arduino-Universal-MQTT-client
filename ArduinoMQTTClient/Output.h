// Output.h

#ifndef _OUTPUT_h
#define _OUTPUT_h

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
	Purpose: Abstract class for any MQTTDevices that are outputs for the system
*/
class Output : public MQTTDevice {

public:
	Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttListenTopic, const char* mqttRespondTopic);
	virtual void action(MQTTDevice::ACTION action, PubSubClient mqttClient) = 0;
	virtual void subscribe(PubSubClient mqttClient) = 0;
	const char* getMQTTListenTopic();
protected:
	const char* getMQTTRespondTopic();
private:
	const char* mqttListenTopic;
	const char* mqttRespondTopic;
};

#endif

