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
	if (inputChange.pinChanged && inputChange.stateChangedTo != inputChange.lastPinStateProcessed && debounce()) {
		Serial.println("sending");
		inputChange.lastPinStateProcessed = inputChange.stateChangedTo;
		switch (inputChange.stateChangedTo) {
		case (HIGH):
			mqttClient.publish(getDeviceMQTTTopic(), MQTTDevice::actionStringsToTypes[1].string); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		case (LOW):
			mqttClient.publish(getDeviceMQTTTopic(), MQTTDevice::actionStringsToTypes[0].string); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		}
	}
	inputChange.pinChanged = false;
}