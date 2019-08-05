// Configurator.h

#ifndef _CONFIGURATOR_h
#define _CONFIGURATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
#include "Output.h"
/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Logic for the user conguration of the system on boot up
*/
class Configurator {
private:
	int EEPROMPointer = 0;
	byte* MACAddress; // Always 6 bytes
	byte* arduinoIP; // IPv4 always 4 bytes
	byte* MQTTBrokerIP; // IPv4 always 4 bytes
	byte* numOfInputs;
	byte* numOfOutputs;
	Input* inputs;
	Output* outputs;
	
	Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input* inputs, byte* numOfOutputs, Output* outputs);
	void setup();
	void setMACAddress(byte EEPROMPointer, byte* MACAddress); //  Always 6 bytes
	void setArduinoIP(byte EEPROMPointer, byte* arduinoIP); // IPv4 always 4 bytes
	void setMQTTBrokerIP(byte EEPROMPointer, byte* MQTTBrokerIP); // IPV4 always 4 bytes
	void setNumOfInputs(byte EEPROMPointer, byte* numOfInputs);
	void setNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs);
	void setInputs(byte EEPROMPointer, Input* inputs, byte numOfInputs);
	void setOutputs(byte EEPROMPointer, Output* outputs, byte numOfOutputs);

};
#endif

