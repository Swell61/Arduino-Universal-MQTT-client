// 
// 
// 

#include "Contact.h"
#include "Controller.h"
#include "MQTTDevice.h"
void enableInterrupt(uint8_t pinNumber, void (*userFunction)(void), uint8_t mode); // Forward declare
const char* getProgmemString(const char* progmemStringLocation);

static unsigned long lastMillis = 0;

Contact::Contact(const char* deviceMQTTTopic, const byte pinNum, const char* highMessage, const char* lowMessage) : Input(MQTTDevice::DEVICE_TYPE::CONTACT), pinNum(pinNum), mqttTopic(deviceMQTTTopic),
highMessage(highMessage), lowMessage(lowMessage) {
	inputs[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
	pinMode(pinNum, INPUT_PULLUP);
	Serial.print("Added contact to pin ");
	Serial.println(pinNum);
	enableInterrupt(pinNum, Input::interruptHandler, CHANGE);
}

void Contact::handleInput(PubSubClient mqttClient) {
	// If the input changed since last check

	if (inputChange.stateChangedTo != inputChange.lastPinStateProcessed && debounce()) {
		Serial.println("sending");
		inputChange.lastPinStateProcessed = inputChange.stateChangedTo;
		switch (inputChange.stateChangedTo) {
		case (HIGH):
			mqttClient.publish(getMQTTTopic(), getProgmemString(highMessage));
			break;
		case (LOW):
			mqttClient.publish(getMQTTTopic(), getProgmemString(lowMessage));
			break;
		}
	}
}

const char* Contact::getMQTTTopic() {
	return getProgmemString(mqttTopic);
}