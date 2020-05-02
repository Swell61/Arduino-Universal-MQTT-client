// 
// 
// 

#include "Contact.h"
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(char const *const deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::CONTACT, pinNum) {
	inputs[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
}

void Contact::handleInput(PubSubClient mqtttClient) {
	// If the input changed since last check
	if (inputChange.pinChanged) {
		switch (inputChange.pinChangedTo) {
		case (HIGH):

		case (LOW):
			break;
		}
	}
}