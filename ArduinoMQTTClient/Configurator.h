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
#include "MQTTDevice.h"
#include <UIPEthernet.h>
/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Logic for the user conguration of the system on boot up
*/
class Configurator {
private:
	int EEPROMPointer = 1; // First byte used to detect first configuration or not so start from second
	byte* MACAddress; // Always 6 bytes
	byte* controllerIP; // IPv4 always 4 bytes
	byte* MQTTBrokerIP; // IPv4 always 4 bytes
	byte* numOfInputs;
	byte* numOfOutputs;
	Input** inputs;
	Output** outputs;

	const char* ENTER_CONTROLLER_IP = "Ctrlr name:\0";
	const char* ENTER_BROKER_IP = "Ctrlr IP:\0";
	const char* ENTER_CONTROLLER_MAC = "Crtlr MAC:\0";
	const char* DEVICE_TYPE = "Dev type:\0";
	const char* DEVICE_NAME = "Dev name (8 chars):\0";
	const char* DEVICE_PIN = "Dev pin:\0";
	
	Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input** inputs, byte* numOfOutputs, Output** outputs);
	void setup();
	void readMemory();

	void readMACAddress(byte EEPROMPointer, byte* MACAddress); //  Always 6 bytes
	void readIP(byte EEPROMPointer, byte* IP); // IPv4 always 4 bytes
	void readNum(byte EEPROMPointer, byte* numO);
	void readInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs);
	void readOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs);

	void writeMACAddress(byte EEPROMPointer, byte* MACAddress); //  Always 6 bytes
	void writeIP(byte EEPROMPointer, byte* IP); // IPv4 always 4 bytes
	void writeNum(byte EEPROMPointer, byte* numOfInputs);
	void writeMQTTDevices(byte EEPROMPointer, MQTTDevice** devices, byte numOfDevices);

	void initialConfiguration(IPAddress& controllerIP, IPAddress& brokerIP, byte* controllerMAC);
	void addDevice(Output** outputs, byte* numOfOutputs, Input** inputs, byte* numOfInputs);
};
#endif

