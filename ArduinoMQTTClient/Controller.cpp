// 
// 
// 
#include "Controller.h"
#include "Relay.h"

Controller* Controller::callbackControllerPointer = NULL;
Controller::Controller() {
	Output* output = new Relay("relay", 10);
	outputDevices[0] = output;
	++numOfOutputs;

	if (Controller::callbackControllerPointer == NULL) {
		Controller::callbackControllerPointer = this;
	}
}

void Controller::setup() {
	
	Ethernet.begin(mac); // Start the ethernet connection
	Serial.println("Started eth");
	Serial.println(Ethernet.localIP());
	MQTTClient = PubSubClient(ethConnection);
	MQTTClient.setServer(MQTTBrokerIP, 1883);
	MQTTClient.setCallback(callbackHandler);
	Serial.println("Conn MQTT");
	Serial.println(MQTTClient.connect("arduino") ? "conn" : "no conn");
	subscribeToOutputs();
	Serial.println("Sub out");
}

void Controller::subscribeToOutputs() {
	// Subscribe to all output device topics
	
	for (byte outputDevice = 0; outputDevice < numOfOutputs; ++outputDevice) {
		char topic[17] = "cmnd/"; // Top level command topic
		strcat(topic, controllerName); // Second level controller topic
		strcat(topic, "/"); // Add topic separator
		strcat(topic, outputDevices[outputDevice]->getDeviceName()); // Third level output device name topic
		MQTTClient.subscribe(topic);
	}
}

void Controller::run() {
	while (true) {
		MQTTClient.loop();
	}
}

void Controller::callback(char* topic, byte* payload, unsigned int length) {
	getOutputDeviceFromTopic(topic)->action(getActionFromPayload(payload, length));
}

Output* const Controller::getOutputDeviceFromTopic(char *const topic) {
	char* const deviceName = strchr(topic, '/');

	for (int outputIndex = 0; outputIndex < numOfOutputs; ++outputIndex) {
		if (strcmp(outputDevices[outputIndex]->getDeviceName(), deviceName)) {
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
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	Serial.print("len: ");
	Serial.print(length);
	Serial.print(" ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

