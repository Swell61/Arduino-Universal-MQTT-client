// 
// 
// 
#include "Controller.h"
#include "Relay.h"
#include <../UIPEthernet/UIPEthernet.h>

const char PROGMEM relay1Topic[] = { "cmnd/ard1/test" };
char topicBuffer[15];
Controller* Controller::callbackControllerPointer = NULL;
Controller::Controller() {
	Output* output = new Relay(relay1Topic, 10);
	outputDevices[0] = output;
	++numOfOutputs;

	if (Controller::callbackControllerPointer == NULL) {
		Controller::callbackControllerPointer = this;
	}
	MQTTClient = PubSubClient(ethConnection);
	MQTTClient.setServer(MQTTBrokerIP, 1883);
	MQTTClient.setCallback(callbackHandler);
}

void Controller::setup() {
	
	Ethernet.begin(mac, controllerIP); // Start the ethernet connection
	Serial.println(Ethernet.localIP());
	delay(1500);
}

void Controller::setupMQTT() {
	while (!MQTTClient.connected()) {
		MQTTClient.connect(controllerName);
		delay(2000);
	}
		subscribeToOutputs();
	
}

void Controller::subscribeToOutputs() {
	Serial.println(F("start read"));
	// Subscribe to all output device topics
	for (byte outputDeviceIndex = 0; outputDeviceIndex < numOfOutputs; ++outputDeviceIndex) {
		strcpy_P(topicBuffer, outputDevices[outputDeviceIndex]->getDeviceMQTTTopic());
		MQTTClient.subscribe(topicBuffer);
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
			MQTTClient.loop();
			Ethernet.maintain();
		}
	}
}

void Controller::callback(char* topic, byte* payload, unsigned int length) {
	getOutputDeviceFromTopic(topic)->action(getActionFromPayload(payload, length));
}

Output* const Controller::getOutputDeviceFromTopic(char *const topic) {
	char* const deviceMQTTTopic = strchr(topic, '/');

	for (int outputIndex = 0; outputIndex < numOfOutputs; ++outputIndex) {
		if (strcmp(outputDevices[outputIndex]->getDeviceMQTTTopic(), deviceMQTTTopic)) {
			return outputDevices[outputIndex];
		}
	}
	return NULL;
}

MQTTDevice::ACTION const Controller::getActionFromPayload(byte* const payload, unsigned int length) {
	for (int actionTypeIndex = 0; actionTypeIndex < sizeof(MQTTDevice::actionStringsToTypes) / sizeof(actionStringToType); ++actionTypeIndex) {
		Serial.print("current iter: ");
		Serial.print(MQTTDevice::actionStringsToTypes[actionTypeIndex].string);
		if (memcmp(payload, MQTTDevice::actionStringsToTypes[actionTypeIndex].string, length) == 0) {
			return MQTTDevice::actionStringsToTypes[actionTypeIndex].type;
		}
	}
	return MQTTDevice::ACTION::INFO;
}

void Controller::callbackHandler(char* topic, byte* payload, unsigned int length) {
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

