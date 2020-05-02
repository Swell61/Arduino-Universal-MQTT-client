/*
 Name:		ArduinoMQTTClient.ino
 Created:	7/29/2019 7:26:03 PM
 Author:	Samuel
*/

// the setup function runs once when you press reset or power the board

#include <SPI.h>
#include <EEPROM.h>
#include <PubSubClient.h>
#include <UIPEthernet.h>
#include "Controller.h"
#define DEBUG
void setup() {
#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Setting up");
#endif

	Controller controller = Controller();
	controller.setup();
	controller.run();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	
}
