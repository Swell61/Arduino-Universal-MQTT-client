// 
// 
// 
#include "Controller.h"
void Controller::setup() {
	Ethernet.begin(mac, arduinoIP); // Start the ethernet connection
	
	// Subscribe to all output device topics
	for (byte outputDevice = 0; outputDevice < numOfOutputs; outputDevice++) {
		char topic[17] = "cmnd/"; // Top level command topic
		strcat(topic, arduinoName); // Second level controller topic
		strcat(topic, "/"); // Add topic separator
		strcat(topic, outputDevices[outputDevice].getDeviceName()); // Third level output device name topic
		MQTTClient.subscribe(topic);
	}
}

