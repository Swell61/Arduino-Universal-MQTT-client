/*
 Name:		ArduinoMQTTClient.ino
 Created:	7/29/2019 7:26:03 PM
 Author:	Samuel
*/

#include <SPI.h>
#include <EEPROM.h>
#include <PubSubClient.h>
#include <UIPEthernet.h>
#include "Controller.h"

#define EI_ARDUINO_INTERRUPTED_PIN
#include <../EnableInterrupt/EnableInterrupt.h>
#define DEBUG
void setup() {
	Serial.begin(9600);
	Serial.println(F("starting"));
	Controller controller = Controller();
	controller.run();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	
}
