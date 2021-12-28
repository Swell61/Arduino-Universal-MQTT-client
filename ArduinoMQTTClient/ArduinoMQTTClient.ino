/*
 Name:		ArduinoMQTTClient.ino
 Created:	7/29/2019 7:26:03 PM
 Author:	Samuel
*/

#include "Controller.h"

#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>
#define DEBUG
Controller controller;
void setup() {
	controller.run();
}

// the loop function runs over and over again until power down or reset
void loop() {

}
