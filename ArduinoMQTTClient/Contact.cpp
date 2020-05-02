// 
// 
// 

#include "Contact.h"
#include "Controller.h"
static unsigned long lastMillis = 0;
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(const char* deviceMQTTTopic, const byte pinNum) : Input(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::CONTACT, pinNum) {
	inputs[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
	pinMode(pinNum, INPUT);
	digitalWrite(pinNum, HIGH);
}

void Contact::handleInput(PubSubClient mqttClient) {
	// If the input changed since last check
	unsigned long currentMillis = millis();
	if (true) {
		delay(100);
		lastMillis = currentMillis;
		strncpy_P(Controller::topicBuffer, getDeviceMQTTTopic(), sizeof(Controller::topicBuffer));
		Serial.println("sending");
		switch (inputChange.pinChangedTo) {
		case (HIGH):
			mqttClient.publish(Controller::topicBuffer, MQTTDevice::actionStringsToTypes[1].string, false); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		case (LOW):
			Serial.println(mqttClient.publish(Controller::topicBuffer, MQTTDevice::actionStringsToTypes[0].string)); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		}
	}
}