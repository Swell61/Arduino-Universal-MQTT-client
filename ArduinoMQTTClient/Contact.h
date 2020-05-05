// Contact.h

#ifndef _CONTACT_h
#define _CONTACT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for contact based input (ie a contact for a window or door to detect whether it is open or not)
*/

struct inputChange {
	uint8_t stateChangedTo : 1;
	uint8_t lastPinStateProcessed : 1;
};

class Contact : public Input {
public:
	Contact(const char* deviceMQTTTopic, const byte pinNum, const char* highMessage, const char* lowMessage);
	void handleInput(PubSubClient mqttClient) override;

	static void interruptHandler();
private:
	volatile inputChange inputChange = { 0, 0 };
	static Contact* contacts[16];

	const char* highMessage;
	const char* lowMessage;
	const byte pinNum;
	const char* mqttListenTopic;

	const char* getMQTTListenTopic();
};

#endif

