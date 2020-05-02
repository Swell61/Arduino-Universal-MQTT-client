// 
// 
// 
#include "Controller.h"
#include "Relay.h"

Controller* Controller::callbackControllerPointer = NULL;
Controller::Controller() {
	controllerIP = new IPAddress(192, 168, 0, 170);
	mac = new byte[6]{ 0x00,0x01,0x02,0x03,0x04,0x05 }; // Randomly generated
	MQTTBrokerIP = new IPAddress(192, 168, 0, 57);


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
	MQTTClient.setServer(*MQTTBrokerIP, 1883);
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
	
	MQTTClient.publish("cmnd/sonoff/POWER", "hi");
	MQTTClient.publish("cmnd/sonoff/POWER", "hi");
}

void Controller::run() {
	while (true) {
		MQTTClient.loop();
	}
}

void Controller::callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	getOutputDeviceFromTopic(topic)->action(getActionFromPayload((char*)payload, length));
}

Output* const Controller::getOutputDeviceFromTopic(char *const topic) {
	char* const deviceName = strchr(topic, '/');

	for (int outputIndex = 0; outputIndex < numOfOutputs; ++outputIndex) {
		if (strcmp(outputDevices[outputIndex]->getDeviceName(), deviceName)) {
			return outputDevices[outputIndex];
		}
	}
}

MQTTDevice::ACTION const Controller::getActionFromPayload(char* const payload, unsigned int length) {
	for (int actionTypeIndex = 0; actionTypeIndex < sizeof(MQTTDevice::actionStringsToTypes) / sizeof(actionStringToType); ++actionTypeIndex) {
		if (strncmp(payload, MQTTDevice::actionStringsToTypes[actionTypeIndex].string, length)) {
			return MQTTDevice::actionStringsToTypes[actionTypeIndex].type;
		}
	}
}

void Controller::callbackHandler(char* topic, byte* payload, unsigned int length) {
	Controller::callbackControllerPointer->callback(topic, payload, length);
}

