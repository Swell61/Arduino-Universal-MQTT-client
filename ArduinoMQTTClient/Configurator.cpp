// 
// 
// 

#include "Configurator.h"
#include <EEPROM/src/EEPROM.h>

/*
	Set all the values for the pointers passed from the configuration to the values read from EEPROM.
*/
void Configurator::setup() {
	
	// Read Arduino MAC address
	readMACAddress(EEPROMPointer, MACAddress);
	// Read Arduino IP Address
	readArduinoIP(EEPROMPointer, arduinoIP);
	// Read MQTT broker IP address
	readArduinoIP(EEPROMPointer, MQTTBrokerIP);
	// Read number of inputs
	readNumOfInputs(EEPROMPointer, numOfInputs);
	// Read inputs
	inputs = (Input*)calloc(sizeof(Input), *(numOfInputs));
	readInputs(EEPROMPointer, inputs, *(numOfInputs));
	// Read num of outputs
	readNumOfOutputs(EEPROMPointer, numOfOutputs);
	// Read outputs
	outputs = (Output*)calloc(sizeof(Output), *(numOfOutputs));
	readOutputs(EEPROMPointer, outputs, *(numOfOutputs));

}

Configurator::Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input* inputs, byte* numOfOutputs, Output* outputs) : MACAddress(MACAddress),
arduinoIP(arduinoIP), MQTTBrokerIP(MQTTBrokerIP), numOfInputs(numOfInputs), inputs(inputs), numOfOutputs(numOfOutputs), outputs(outputs) {

}

/*
	Read all 6 bytes of the MAC address and set the values in the array of the pointer
	
	Parameters:
	EEPROMPointer: Location of first byte of 6 MAC address bytes
	MACAddress: Pointer to MAC address array held in configuration
*/
void Configurator::readMACAddress(byte EEPROMPointer, byte* MACAddress) {
	*(MACAddress) = EEPROM.read(EEPROMPointer++); // Read first byte of MAC address and increment pointer for next byte
	*(MACAddress + 1) = EEPROM.read(EEPROMPointer++); // Read second byte of MAC address and increment pointer for next byte
	*(MACAddress + 2) = EEPROM.read(EEPROMPointer++); // Read third byte of MAC address and increment pointer for next byte
	*(MACAddress + 3) = EEPROM.read(EEPROMPointer++); // Read fourth byte of MAC address and increment pointer for next byte
	*(MACAddress + 4) = EEPROM.read(EEPROMPointer++); // Read fifth byte of MAC address and increment pointer for next byte
	*(MACAddress + 5) = EEPROM.read(EEPROMPointer++); // Read sixth byte of MAC address and increment pointer for next item read
}

/*
	Read all 4 bytes of the arduinos IP address and set the values in the array of the pointer

	Parameters:
	EEPROMPointer: Location of first byte of 4 arduino IP address bytes
	arduinoIP: Pointer to arduino IP address array held in configuration
*/
void Configurator::readArduinoIP(byte EEPROMPointer, byte* arduinoIP) {
	*(arduinoIP) = EEPROM.read(EEPROMPointer++); // Read first byte of arduino IP address and increment pointer for next byte
	*(arduinoIP + 1) = EEPROM.read(EEPROMPointer++); // Read second byte of arduino IP address and increment pointer for next byte
	*(arduinoIP + 2) = EEPROM.read(EEPROMPointer++); // Read third byte of arduino IP address and increment pointer for next byte
	*(arduinoIP + 3) = EEPROM.read(EEPROMPointer++); // Read fourth byte of arduino IP address and increment pointer for next item read
}

/*
	Read all 4 bytes of the MQTT broker IP address and set the values in the array of the pointer

	Parameters:
	EEPROMPointer: Location of first byte of 4 MQTT broker IP address bytes
	MQTTBrokerIP: Pointer to MQTT broker IP address array held in configuration
*/
void Configurator::readMQTTBrokerIP(byte EEPROMPointer, byte* MQTTBrokerIP) {
	*(MQTTBrokerIP) = EEPROM.read(EEPROMPointer++); // Read first byte of MQTT broker IP address and increment pointer for next byte
	*(MQTTBrokerIP + 1) = EEPROM.read(EEPROMPointer++); // Read second byte of MQTT broker IP address and increment pointer for next byte
	*(MQTTBrokerIP + 2) = EEPROM.read(EEPROMPointer++); // Read third byte of MQTT broker IP address and increment pointer for next byte
	*(MQTTBrokerIP + 3) = EEPROM.read(EEPROMPointer++); // Read fourth byte of MQTT broker IP address and increment pointer for next item read
}

/*
	Read the number of inputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of input devices
	numOfInputs: Pointer to the byte that stores number of inptus in configuration
*/
void Configurator::readNumOfInputs(byte EEPROMPointer, byte* numOfInputs) {
	*(numOfInputs) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Read the inputs stored in EEPROM

	Parameters:
	EEPROMPointer: Location of the first byte for inputs stored in EEPROM
	inputs: Pointer to block of memory to store inputs in
	numOfInputs: Number of inputs stored in EEPROM
*/
void Configurator::readInputs(byte EEPROMPointer, Input* inputs, byte numOfInputs) {
	for (byte inputIndex = 0; inputIndex < numOfInputs; inputIndex++) { // Loop through all inputs stored in EEPROM
		EEPROM.get(EEPROMPointer++, *(inputs + inputIndex)); // Retrieve each input and store in the array
	}
}

/*
	Read the number of outputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of output devices
	numOfInputs: Pointer to the byte that stores number of outputs in configuration
*/
void Configurator::readNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs) {
	*(numOfOutputs) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPoitnter, then increment EEPROMPointer
}

/*
	Read the outputs stored in EEPROM

	Parameters:
	EEPROMPointer: Location of first byte for the outputs stored in EEPROM
	outputs: Pointer to block of memory to store inputs in
	numOfOutputs: Number of outputs stored in EEPROM
*/
void Configurator::readOutputs(byte EEPROMPointer, Output* outputs, byte numOfOutputs) {
	for (byte outputIndex = 0; outputIndex < numOfOutputs; outputIndex++) { // Loop through all outputs stored in EEPROM
		EEPROM.get(EEPROMPointer++, *(outputs + outputIndex)); // Retrieve each output and store in the array
	}
}
