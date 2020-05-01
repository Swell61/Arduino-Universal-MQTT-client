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

