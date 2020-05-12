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
	const IPAddress MQTTBrokerIP = IPAddress(192, 168, 0, 80);
	const byte mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	EthernetClient ethConnection;
	PubSubClient MQTTClient;
	char const controllerName[6] = "MQTT1";

	Input* inputDevices[10]; // Collection of all input devices on the Arduino. Adjust array size to suit
	byte numOfInputs = 0;
	Output* outputDevices[5]; // Collection of all output devices on the Arduino. Adjust array size to suit
	byte numOfOutputs = 0;

	static Controller* callbackControllerPointer; // Callback pointer will direct the MQTT message callback method to the correct instance of controller (there will only ever be 1 on any Arduino)
	static void callbackHandler(char* topic, byte* payload, unsigned int length); // Callback method given to PubSubClient library
	void callback(char* topic, byte* payload, unsigned int length); // Implementation specific callback method
	Output* const getOutputDeviceFromTopic(char* const topic); // Returns a pointer to the output device found in the MQTT topic from the broker
	MQTTDevice::ACTION const getActionFromPayload(byte *const payload, unsigned int length); // Converts an MQTT payload into an ACTION enum

	void setupMQTT(); // Connects to MQTT broker
	void subscribeToOutputs(); // Subscribes to all output device command/listen topics
	void setupEthernet(); // Connects the Arduino to the LAN
	void processInputs(); // Method called once every main loop for allowing all input devices to process any pending actions (e.g. change in input or timer lapse)

public:
	Controller();
	void run();
};
#endif

