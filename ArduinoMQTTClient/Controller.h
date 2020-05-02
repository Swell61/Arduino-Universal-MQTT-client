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
	IPAddress *controllerIP;
	IPAddress *MQTTBrokerIP;
	byte *mac;
	EthernetClient ethConnection;
	PubSubClient MQTTClient;
	char const controllerName[6] = "MQTT1";

	Input** inputDevices;
	byte numOfInputs = 0;
	Output** outputDevices;
	byte numOfOutputs = 0;
	static Controller* callbackControllerPointer;
	static void callbackHandler(char* topic, byte* payload, unsigned int length);
	void callback(char* topic, byte* payload, unsigned int length);
	Output* const getOutputDeviceFromTopic(char* const topic);
	MQTTDevice::ACTION const getActionFromPayload(char *const payload, unsigned int length);
public:
	Controller();
	void setup();
	void subscribeToOutputs();
	void run();
};
#endif

