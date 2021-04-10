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
#include "Relay.h"
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
const char PROGMEM playroomMotion[] = { "stat/ds/playroom/mot" };
const char PROGMEM playroomTamper[] = { "stat/ds/playroom/tamp" };
const char PROGMEM hallMotion[] = { "stat/ds/hall/mot" };
const char PROGMEM hallTamper[] = { "stat/ds/hall/tamp" };
const char PROGMEM loungeMotion[] = { "stat/ds/lounge/mot" };
const char PROGMEM loungeTamper[] = { "stat/ds/lounge/tamp" };
const char PROGMEM kitchenMotion[] = { "stat/ds/kitchen/mot" };
const char PROGMEM kitchenTamper[] = { "stat/ds/kitchen/tamp" };

const char PROGMEM masterBedroomMotion[] = { "stat/us/m_bdroom/mot" };
const char PROGMEM masterBedroomTamper[] = { "stat/us/m_bdroom/tamp" };
const char PROGMEM landingMotion[] = { "stat/us/landing/mot" };
const char PROGMEM landingTamper[] = { "stat/us/landing/tamp" };
const char PROGMEM landingLight[] = { "stat/us/landing/light"};
const char PROGMEM landingLightCtrl[] = { "ctrl/us/landing/light" };
const char PROGMEM landingLightResp[] = { "resp/us/landing/light" };

class Controller {

private:
	const IPAddress controllerIP{192, 168, 0, 199};
	const IPAddress MQTTBrokerIP{192, 168, 0, 200};
	const byte mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	EthernetClient ethConnection;
	PubSubClient MQTTClient{MQTTBrokerIP, 1883, callbackHandler, ethConnection};
	const char controllerName[4] = "ad1";

	AlarmMotionSensor h{hallMotion, hallTamper, 2, 3, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT};
	AlarmMotionSensor l{loungeMotion, loungeTamper, 4, 5, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT};
	AlarmMotionSensor p{playroomMotion, playroomTamper, 6, 7, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT};
	AlarmMotionSensor k{kitchenMotion, kitchenTamper, 8, 9, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT};
	Contact b{masterBedroomMotion, A2, MOTION_TEXT, NO_MOTION_TEXT};
	Contact la{landingMotion, A3, MOTION_TEXT, NO_MOTION_TEXT};
	Contact ll{landingLight, A0, OFF_TEXT, ON_TEXT};
	Relay llc{landingLightCtrl, landingLightResp, A1, true};

	Input* inputDevices[7] = {&h, &l, &p, &k, &b, &la, &ll}; // Collection of all input devices on the Arduino. Adjust array size to suit
	byte numOfInputs = 7;
	Output* outputDevices[1] = {&llc}; // Collection of all output devices on the Arduino. Adjust array size to suit
	byte numOfOutputs = 1;

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

