// 
// 
// 
#include "Controller.h"
#include "Relay.h"
#include "Contact.h"
#include "AlarmMotionSensor.h"
#include <../UIPEthernet/UIPEthernet.h>
#include <MemoryFree.h>

/* Store ALL topic strings with PROGMEM to keep them out of SRAM.
 * Ensure progmemBuffer is large enough to accommodate the largest topic string.
 * The logic behind this is you only ever read one topic string at once, so keep
 * them all in PROGMEM and read them into the progmemBuffer when they are needed. Memory
 * usage is more important than speed ;). */
const char PROGMEM alarmSensorMotion[] = { "stat/ard1/mot" };
const char PROGMEM alarmSensorTamper[]{ "stat/ard1/tamp" };

Controller* Controller::callbackControllerPointer = NULL;
Controller::Controller() {

	inputDevices[0] = new AlarmMotionSensor(alarmSensorMotion, alarmSensorTamper, 6, 7, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT);
	++numOfInputs;

	if (Controller::callbackControllerPointer == NULL) {
		Controller::callbackControllerPointer = this;
	}
	MQTTClient = PubSubClient(ethConnection);
	MQTTClient.setServer(MQTTBrokerIP, 1883);
	MQTTClient.setCallback(callbackHandler);
}

void Controller::setup() {
	
	Ethernet.begin(mac, controllerIP); // Start the ethernet connection
	delay(1500);
}

void Controller::setupMQTT() {
	
	MQTTClient.connect(controllerName, "mqtt", "^3r92444@K!MJM!g");
	
	if (MQTTClient.connected()) {
		subscribeToOutputs();
	}
	
}

void Controller::subscribeToOutputs() {
	// Subscribe to all output device topics
	for (byte outputDeviceIndex = 0; outputDeviceIndex < numOfOutputs; ++outputDeviceIndex) {
		MQTTClient.subscribe(outputDevices[outputDeviceIndex]->getMQTTListenTopic());
	}
}

void Controller::processInputs() {
	for (byte inputIndex = 0; inputIndex < numOfInputs; ++inputIndex) {
		inputDevices[inputIndex]->handleInput(MQTTClient);
	}
}

void Controller::run() {
	while (true) {
		if (Ethernet.linkStatus() == LinkOFF || Ethernet.linkStatus() == Unknown) {
			setup();
		}
		else if (!MQTTClient.connected()) {
			MQTTClient.connected();
			setupMQTT();
		}
		else {
			processInputs();
			MQTTClient.loop();
			Ethernet.maintain();
		}
	}
}

void Controller::callback(char* topic, byte* payload, unsigned int length) {
	getOutputDeviceFromTopic(topic)->action(getActionFromPayload(payload, length), MQTTClient);
}

Output* const Controller::getOutputDeviceFromTopic(char *const topic) {
	for (byte outputIndex = 0; outputIndex < numOfOutputs; ++outputIndex) {
		if (strncmp(outputDevices[outputIndex]->getMQTTListenTopic(), topic, sizeof(topic)) == 0) {
			return outputDevices[outputIndex];
		}
	}
	return NULL;
}

MQTTDevice::ACTION const Controller::getActionFromPayload(byte* const payload, unsigned int length) {
	for (byte actionTypeIndex = 0; actionTypeIndex < sizeof(MQTTDevice::actionStringsToTypes) / sizeof(actionStringToType); ++actionTypeIndex) {
		if (memcmp(payload, getProgmemString(MQTTDevice::actionStringsToTypes[actionTypeIndex].string), length) == 0) {
			return MQTTDevice::actionStringsToTypes[actionTypeIndex].type;
		}
	}
	return MQTTDevice::ACTION::INFO;
}

void Controller::callbackHandler(char* topic, byte* payload, unsigned int length) {
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

