// Controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <UIPEthernet.h>
#include <PubSubClient.h>
#include "Input.h"
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Control class for running the system. Governs the running of the system.
*/
class Controller {

private:
	const IPAddress controllerIP = IPAddress(192, 168, 0, 170);
	const IPAddress MQTTBrokerIP = IPAddress(192, 168, 0, 57);
	const byte mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	EthernetClient ethConnection;
	PubSubClient MQTTClient;
	char const controllerName[6] = "MQTT1";

	Input* inputDevices[10];
	byte numOfInputs = 0;
	Output* outputDevices[5];
	byte numOfOutputs = 0;

	static Controller* callbackControllerPointer;
	static void callbackHandler(char* topic, byte* payload, unsigned int length);
	void callback(char* topic, byte* payload, unsigned int length);
	Output* const getOutputDeviceFromTopic(char* const topic);
	MQTTDevice::ACTION const getActionFromPayload(byte *const payload, unsigned int length);
	void setupMQTT();
	void setup();
	void processInputs();

public:
	Controller();
	void subscribeToOutputs();
	void run();
};
#endif

