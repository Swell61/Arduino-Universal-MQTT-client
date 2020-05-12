// 
// 
// 
#include "Controller.h"
#include "Relay.h"
#include "Contact.h"
#include "AlarmMotionSensor.h"
#include <../UIPEthernet/UIPEthernet.h>

/* Store ALL topic strings with PROGMEM to keep them out of SRAM.
 * Ensure progmemBuffer is large enough to accommodate the largest topic string.
 * The logic behind this is you only ever read one topic string at once, so keep
 * them all in PROGMEM and read them into the progmemBuffer when they are needed. Memory
 * usage is more important than speed ;). */
const char PROGMEM alarmSensorMotion[] = { "stat/ard1/mot" };
const char PROGMEM alarmSensorTamper[]{ "stat/ard1/tamp" };

Controller* Controller::callbackControllerPointer = NULL; // Initial callback controller pointer definition. Changed in Controller constructor to point to correct Controller (there will only be 1)
Controller::Controller() {
	// Setup an input and output devices
	inputDevices[0] = new AlarmMotionSensor(alarmSensorMotion, alarmSensorTamper, 6, 7, MOTION_TEXT, NO_MOTION_TEXT, TAMPERED_TEXT, NORMAL_TEXT);
	++numOfInputs;

	// Initialise controller callback to point to current controller
	if (Controller::callbackControllerPointer == NULL) {
		Controller::callbackControllerPointer = this;
	}

	// Setup MQTTClient ready for connection to broker
	MQTTClient = PubSubClient(ethConnection);
	MQTTClient.setServer(MQTTBrokerIP, 1883);
	MQTTClient.setCallback(callbackHandler);
}

void Controller::setupEthernet() {
	Ethernet.begin(mac, controllerIP); // Start the ethernet connection
	delay(500); // Give hardware time to react
}

void Controller::setupMQTT() {
	
	MQTTClient.connect(controllerName, "mqtt", "^3r92444@K!MJM!g"); // Temp username and pw for testing (broker will never be opened to internet anyway)
	
	if (MQTTClient.connected()) { // If last connection attempt was successful, need to subscribe to all output topics
		subscribeToOutputs();
	}
}

void Controller::subscribeToOutputs() {
	// Subscribe to all output device topics
	for (byte outputDeviceIndex = 0; outputDeviceIndex < numOfOutputs; ++outputDeviceIndex) {
		MQTTClient.subscribe(outputDevices[outputDeviceIndex]->getMQTTListenTopic());
	}
}

// Called once per main loop. Allows input devices to process any pending changes (e.g. change in pin state, timer lapse for temperature report, etc)
void Controller::processInputs() {
	for (byte inputIndex = 0; inputIndex < numOfInputs; ++inputIndex) {
		inputDevices[inputIndex]->handleInput(MQTTClient);
	}
}

void Controller::run() {
	while (true) {

		if (Ethernet.linkStatus() == LinkOFF || Ethernet.linkStatus() == Unknown) { // If ethernet becomes disconnected
			setupEthernet();
		}
		else if (!MQTTClient.connected()) { // If MQTT client becomes disconnected
			setupMQTT();
		}
		else {
			processInputs(); // Allow all input devices to process any updates
			MQTTClient.loop();
			Ethernet.maintain();
		}
	}
}

void Controller::callback(char* topic, byte* payload, unsigned int length) {
	// Passes the new ACTION to the correct output device, along with MQTTClient to allow it to respond with the change
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

// Finds the corresponding ACTION enum for the payload send by broker
MQTTDevice::ACTION const Controller::getActionFromPayload(byte* const payload, unsigned int payloadLength) {
	for (byte actionTypeIndex = 0; actionTypeIndex < sizeof(MQTTDevice::actionStringsToTypes) / sizeof(actionStringToType); ++actionTypeIndex) {
		
		// Compare the payload to each string representation of each ACTION enum
		if (memcmp(payload, getProgmemString(MQTTDevice::actionStringsToTypes[actionTypeIndex].string), payloadLength) == 0) {
			return MQTTDevice::actionStringsToTypes[actionTypeIndex].type;
		}
	}
	return MQTTDevice::ACTION::INFO;
}

void Controller::callbackHandler(char* topic, byte* payload, unsigned int length) {
	// Gives callback to correct Controller instance
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

