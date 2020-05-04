// 
// 
// 

#include "Contact.h"
#include "Controller.h"
#include "MQTTDevice.h"
void enableInterrupt(uint8_t pinNumber, void (*userFunction)(void), uint8_t mode); // Forward declare
const char* getProgmemString(const char* progmemStringLocation);

static unsigned long lastMillis = 0;
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(const char* deviceMQTTTopic, const byte pinNum) : Input(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::CONTACT, pinNum) {
	inputs[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
	pinMode(pinNum, INPUT_PULLUP);
	Serial.print("Added contact to pin ");
	Serial.println(pinNum);
	enableInterrupt(pinNum, Input::interruptHandler, CHANGE);
}

void Contact::handleInput(PubSubClient mqttClient) {
	// If the input changed since last check
	if (inputChange.pinChanged) {
		Serial.println("Change");
	}
	if (inputChange.pinChanged && inputChange.stateChangedTo != inputChange.lastPinStateProcessed && debounce()) {
		Serial.println("sending");
		inputChange.lastPinStateProcessed = inputChange.stateChangedTo;
		inputChange.pinChanged = false;
		switch (inputChange.stateChangedTo) {
		case (HIGH):
			mqttClient.publish(getDeviceMQTTTopic(), getProgmemString(ON_TEXT)); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		case (LOW):
			mqttClient.publish(getDeviceMQTTTopic(), getProgmemString(OFF_TEXT)); // Could do with changing. Accessing the array manually was done to conserve SRAM
			break;
		}
	}
}