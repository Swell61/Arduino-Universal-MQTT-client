// Configurator.h

#ifndef _CONFIGURATOR_h
#define _CONFIGURATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Logic for the user conguration of the system on boot up
*/
class Configurator {
private:
	int EEPROMpointer = 0;
	byte numOfInputs;
	byte numOfOutputs;
	Input* inputs;
	Output* outputs;
	byte macAddress[6];
	byte arduinoIP[4];
	byte MQTTBrokerIP[4];

	void setup();
	byte getNumOfInputs(byte EEPROMPointer);
	byte getNumOfOutputs(byte EEPROMPointer);
	Input* loadInputsFromEEPROM(byte EEPROMPointer);
	Output* loadOutputsFromEEPROM(byte EEPROMPointer);
};
#endif

