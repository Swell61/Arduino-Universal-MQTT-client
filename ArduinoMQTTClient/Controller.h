// Controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <UIPEthernet/UIPEthernet.h>
#include <pubsubclient/src/PubSubClient.h>
#include "Input.h"
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Control class for running the system. Governs the running of the system.
*/
class Controller {

private:
	IPAddress arduinoIP = IPAddress(192, 168, 0, 170);
	IPAddress MQTTBrokerIP = IPAddress(192, 168, 0, 1);
	byte mac[6] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
	EthernetClient ethConnection;
	PubSubClient MQTTClient = PubSubClient(ethConnection);
	const char * arduinoName = "MQTT1";

	Input* inputDevices;
	byte numOfInputs;
	Output* outputDevices;
	byte numOfOutputs;

public:
	Controller();
	void setup();
};

#endif

