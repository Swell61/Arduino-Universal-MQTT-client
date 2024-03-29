// 
// 
// 
#include "Controller.h"
#include <EthernetENC.h>


Controller* Controller::callbackControllerPointer = NULL; // Initial callback controller pointer definition. Changed in Controller constructor to point to correct Controller (there will only be 1)
Controller::Controller() {
	Ethernet.init(10);
	// Initialise controller callback to point to current controller
	if (Controller::callbackControllerPointer == NULL) {
		Controller::callbackControllerPointer = this;
	} 
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
	for (uint8_t outputDeviceIndex = 0; outputDeviceIndex < numOfOutputs; ++outputDeviceIndex) {
		outputDevices[outputDeviceIndex]->subscribe(MQTTClient);
	}
}

// Called once per main loop. Allows input devices to process any pending changes (e.g. change in pin state, timer lapse for temperature report, etc)
void Controller::processInputs() {
	for (uint8_t inputIndex = 0; inputIndex < numOfInputs; ++inputIndex) {
		inputDevices[inputIndex]->handleInput(MQTTClient);
	}
}

void Controller::run() {
	setupEthernet();
	while (true) {
		if (!MQTTClient.connected()) { // If MQTT client becomes disconnected
			setupMQTT();
		}
		else {
			processInputs(); // Allow all input devices to process any updates
			MQTTClient.loop();
			Ethernet.maintain();
		}
	}
}

void Controller::callback(char* topic, uint8_t* payload, unsigned int length) {
	// Passes the new ACTION to the correct output device, along with MQTTClient to allow it to respond with the change
	Output *output = getOutputDeviceFromTopic(topic);
	if (output != NULL) {
		getOutputDeviceFromTopic(topic)->action(getActionFromPayload(payload, length), MQTTClient);
	}
}

Output* Controller::getOutputDeviceFromTopic(const char* topic) {
	for (uint8_t outputIndex = 0; outputIndex < numOfOutputs; ++outputIndex) {
		const char *currentDeviceTopic = outputDevices[outputIndex]->getMQTTListenTopic();
		if (strncmp(currentDeviceTopic, topic, sizeof(currentDeviceTopic)) == 0) {
			return outputDevices[outputIndex];
		}
	}
	return NULL;
}

// Finds the corresponding ACTION enum for the payload send by broker
MQTTDevice::ACTION Controller::getActionFromPayload(const uint8_t* payload, unsigned int payloadLength) {
	for (uint8_t actionTypeIndex = 0; actionTypeIndex < sizeof(MQTTDevice::actionStringsToTypes) / sizeof(actionStringToType); ++actionTypeIndex) {
		// Compare the payload to each string representation of each ACTION enum
		if (memcmp(payload, getProgmemString(MQTTDevice::actionStringsToTypes[actionTypeIndex].string), payloadLength) == 0) {
			return MQTTDevice::actionStringsToTypes[actionTypeIndex].type;
		}
	}
	return MQTTDevice::ACTION::INFO;
}

void Controller::callbackHandler(char* topic, uint8_t* payload, unsigned int length) {
	// Gives callback to correct Controller instance
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

