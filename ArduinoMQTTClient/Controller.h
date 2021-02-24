// Controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h
#include <Arduino.h>

#include <UIPEthernet.h>
#include <PubSubClient.h>
#include "Input.h"
#include "Output.h"
#include "AlarmMotionSensor.h"
#include "MQTTDevice.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Control class for running the system. Governs the running of the system.
*/

/* Store ALL topic strings with PROGMEM to keep them out of SRAM.
 * Ensure progmemBuffer is large enough to accommodate the largest topic string.
 * The logic behind this is you only ever read one topic string at once, so keep
 * them all in PROGMEM and read them into the progmemBuffer when they are needed. Memory
 * usage is more important than speed ;). */
const char PROGMEM alarmSensorMotion[] = { "stat/ard1/mot" };
const char PROGMEM alarmSensorTamper[]{ "stat/ard1/tamp" };

class Controller {

private:
	const IPAddress controllerIP = IPAddress(192, 168, 0, 170);
	const IPAddress MQTTBrokerIP = IPAddress(192, 168, 0, 80);
	const byte mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	EthernetClient ethConnection;
	PubSubClient MQTTClient;
	const char controllerName[6] = "MQTT1";

	//AlarmMotionSensor test{alarmSensorMotion, alarmSensorTamper, 6, 7, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT};

	Input* inputDevices[1];// = {&test}; // Collection of all input devices on the Arduino. Adjust array size to suit
	byte numOfInputs = 0;
	Output* outputDevices[5]; // Collection of all output devices on the Arduino. Adjust array size to suit
	byte numOfOutputs = 0;

	static Controller* callbackControllerPointer; // Callback pointer will direct the MQTT message callback method to the correct instance of controller (there will only ever be 1 on any Arduino)
	static void callbackHandler(char* topic, byte* payload, unsigned int length); // Callback method given to PubSubClient library
	void callback(char* topic, byte* payload, unsigned int length); // Implementation specific callback method
	Output* getOutputDeviceFromTopic(const char* topic); // Returns a pointer to the output device found in the MQTT topic from the broker
	MQTTDevice::ACTION getActionFromPayload(const byte* payload, unsigned int length); // Converts an MQTT payload into an ACTION enum

	void setupMQTT(); // Connects to MQTT broker
	void subscribeToOutputs(); // Subscribes to all output device command/listen topics
	void setupEthernet(); // Connects the Arduino to the LAN
	void processInputs(); // Method called once every main loop for allowing all input devices to process any pending actions (e.g. change in input or timer lapse)

public:
	Controller();
	void run();
};
#endif

