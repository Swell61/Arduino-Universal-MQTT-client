// 
// 
// 

#include "Contact.h"
#include "Controller.h"
#include "MQTTDevice.h"
void enableInterrupt(uint8_t pinNumber, void (*userFunction)(void), uint8_t mode); // Forward declare
const char* getProgmemString(const char* progmemStringLocation); // Forward declare
extern volatile uint8_t arduinoInterruptedPin; // Forward declare
extern volatile uint8_t arduinoPinState; // Forward declare

Contact* Contact::contacts[22] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }; // 16 available pins on ATmega 3228p

// Sets the correct contact instance's stateChangedTo that it will check on the next round of updates (and process if debounce time has passed)
void Contact::interruptHandler() {
	contacts[arduinoInterruptedPin]->inputChange.stateChangedTo = arduinoPinState > 0;
}


Contact::Contact(const char* deviceMQTTTopic, const uint8_t pinNum, const char* highMessage, const char* lowMessage) : Input(MQTTDevice::DEVICE_TYPE::CONTACT), 
	pinNum(pinNum), mqttStateTopic(deviceMQTTTopic), highMessage(highMessage), lowMessage(lowMessage), inputChange(pinNum) {
	contacts[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
	pinMode(pinNum, INPUT_PULLUP);
	enableInterrupt(pinNum, Contact::interruptHandler, CHANGE); // Enable interrup for current pin on level change so as not to miss a change
}

void Contact::handleInput(PubSubClient& mqttClient) {
	// If the input changed since last check and we're not in a debounce. Note, debounce check only done if there is a pending input change
	if (inputChange.stateChangedTo != inputChange.lastPinStateProcessed && debounce()) {
		inputChange.lastPinStateProcessed = inputChange.stateChangedTo;
		switch (inputChange.stateChangedTo) {
		case (HIGH):
			mqttClient.publish_P(getMQTTListenTopic(), (const uint8_t*)highMessage, strlen_P(highMessage), false);
			break;
		case (LOW):
			mqttClient.publish_P(getMQTTListenTopic(), (const uint8_t*)lowMessage, strlen_P(lowMessage), false);
			break;
		}
	}
}

const char* Contact::getMQTTListenTopic() {
	return getProgmemString(mqttStateTopic);
}