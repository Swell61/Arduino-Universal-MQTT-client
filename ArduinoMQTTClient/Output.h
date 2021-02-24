// Output.h

#ifndef _OUTPUT_h
#define _OUTPUT_h
#include <Arduino.h>

#include "MQTTDevice.h"
#include <PubSubClient.h>
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Abstract class for any MQTTDevices that are outputs for the system
*/
class Output : public MQTTDevice {

public:
	Output(const MQTTDevice::DEVICE_TYPE deviceType, const char* mqttStateTopic, const char* mqttRespondTopic);
	virtual void action(MQTTDevice::ACTION action, PubSubClient mqttClient) = 0;
	virtual void subscribe(PubSubClient mqttClient) = 0;
	const char* getMQTTListenTopic(); // Reads MQTT listen topic from program flash memory
protected:
	const char* getMQTTStateTopic(); // Reads the MQTT state topic from program flash memory
private:
	const char* mqttStateTopic;
	const char* mqttRespondTopic;
};

#endif

