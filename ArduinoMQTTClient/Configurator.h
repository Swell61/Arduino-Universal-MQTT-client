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
	Input** inputs;
	Output** outputs;
	
	Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input** inputs, byte* numOfOutputs, Output** outputs);
	void setup();
	void readMACAddress(byte EEPROMPointer, byte* MACAddress); //  Always 6 bytes
	void readIP(byte EEPROMPointer, byte* IP); // IPv4 always 4 bytes
	void readNum(byte EEPROMPointer, byte* numO);
	void readNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs);
	void readInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs);
	void readOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs);

	void writeMACAddress(byte EEPROMPointer, byte* MACAddress); //  Always 6 bytes
	void writeIP(byte EEPROMPointer, byte* IP); // IPv4 always 4 bytes
	void writeNumOfInputs(byte EEPROMPointer, byte* numOfInputs);
	void writeNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs);
	void writeInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs);
	void writeOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs);
};
#endif

