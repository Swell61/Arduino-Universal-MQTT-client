// 
// 
// 

#include "Contact.h"
#include "Controller.h"
#include "MQTTDevice.h"
void enableInterrupt(uint8_t pinNumber, void (*userFunction)(void), uint8_t mode); // Forward declare
const char* getProgmemString(const char* progmemStringLocation);
extern volatile uint8_t arduinoInterruptedPin;
extern volatile uint8_t arduinoPinState;

Contact* Contact::contacts[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
void Contact::interruptHandler() {
	contacts[arduinoInterruptedPin]->inputChange.stateChangedTo = arduinoPinState > 0;
}


Contact::Contact(const char* deviceMQTTTopic, const byte pinNum, const char* highMessage, const char* lowMessage) : Input(MQTTDevice::DEVICE_TYPE::CONTACT), pinNum(pinNum), mqttListenTopic(deviceMQTTTopic),
highMessage(highMessage), lowMessage(lowMessage) {
	contacts[pinNum] = this; // Record that this object has pin 'pinNum' for use in callback
	pinMode(pinNum, INPUT_PULLUP);
	Serial.print("Added contact to pin ");
	Serial.println(pinNum);
	enableInterrupt(pinNum, Contact::interruptHandler, CHANGE);
}

void Contact::handleInput(PubSubClient mqttClient) {
	// If the input changed since last check

	if (inputChange.stateChangedTo != inputChange.lastPinStateProcessed && debounce()) {
		Serial.println("sending");
		inputChange.lastPinStateProcessed = inputChange.stateChangedTo;
		switch (inputChange.stateChangedTo) {
		case (HIGH):
			mqttClient.publish_P(getMQTTListenTopic(), highMessage, strlen_P(highMessage), false);
			break;
		case (LOW):
			mqttClient.publish_P(getMQTTListenTopic(), lowMessage, strlen_P(lowMessage), false);
			break;
		}
	}
}

const char* Contact::getMQTTListenTopic() {
	return getProgmemString(mqttListenTopic);
}