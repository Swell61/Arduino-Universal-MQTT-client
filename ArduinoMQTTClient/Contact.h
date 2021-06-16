// Contact.h

#ifndef _CONTACT_h
#define _CONTACT_h
#include <Arduino.h>

#include "Input.h"
#include "InputChange.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for contact based input (ie a contact for a window or door to detect whether it is open or not)
*/


class Contact : public Input {
public:
	Contact(const char* deviceMQTTTopic, const uint8_t pinNum, const char* highMessage, const char* lowMessage);
	void handleInput(PubSubClient& mqttClient) override;

	static void interruptHandler();
private:
	static Contact* contacts[22]; // Stores pointer to all contact objects. Each index is a pin number, used for dirrecting an interrupt to the correct instance

	const char* highMessage; // MQTT payload for when the pin goes high
	const char* lowMessage; // MQTT payload for when the pin goes low
	const uint8_t pinNum; // Pin number the contact device is connected to
	const char* mqttStateTopic; // MQTT topic to use to report a state change
	volatile struct InputChange inputChange;
	const char* getMQTTListenTopic();
};

#endif

