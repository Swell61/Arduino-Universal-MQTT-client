// 
// 
// 

#include "Configurator.h"
#include <EEPROM/src/EEPROM.h>

void Configurator::setup() {
	
	// Get Arduino MAC address

	// Get Arduino IP Address

	// Get MQTT broker IP address

	// Get number of inputs

	// Get inputs

	// Get num of outputs

	// Get outputs

}

Configurator::Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input* inputs, byte* numOfOutputs, Output* outputs) : MACAddress(MACAddress),
arduinoIP(arduinoIP), MQTTBrokerIP(MQTTBrokerIP), numOfInputs(numOfInputs), inputs(inputs), numOfOutputs(numOfOutputs), outputs(outputs) {

}

/*
	Get all 6 bytes of the MAC address and set the values in the array of the pointer
	
	Parameters:
	EEPROMPointer: Location of first byte of 6 MAC address bytes
	MACAddress: Pointer to MAC address array held in configuration
*/
void Configurator::setMACAddress(byte EEPROMPointer, byte* MACAddress) {
	*(MACAddress) = EEPROM.read(EEPROMPointer++); // Read first byte of MAC address and increment pointer for next byte
	*(MACAddress + 1) = EEPROM.read(EEPROMPointer++); // Read second byte of MAC address and increment pointer for next byte
	*(MACAddress + 2) = EEPROM.read(EEPROMPointer++); // Read third byte of MAC address and increment pointer for next byte
	*(MACAddress + 3) = EEPROM.read(EEPROMPointer++); // Read fourth byte of MAC address and increment pointer for next byte
	*(MACAddress + 4) = EEPROM.read(EEPROMPointer++); // Read fifth byte of MAC address and increment pointer for next byte
	*(MACAddress + 5) = EEPROM.read(EEPROMPointer++); // Read sixth byte of MAC address and increment pointer for next item read
}

/*
	Get all 4 bytes of the arduinos IP address and set the values in the array of the pointer

	Parameters:
	EEPROMPointer: Location of first byte of 4 arduino IP address bytes
	arduinoIP: Pointer to arduino IP address array held in configuration
*/
void Configurator::setArduinoIP(byte EEPROMPointer, byte* arduinoIP) {
	*(arduinoIP) = EEPROM.read(EEPROMPointer++); // Read first byte of arduino IP address and increment pointer for next byte
	*(arduinoIP) = EEPROM.read(EEPROMPointer++); // Read second byte of arduino IP address and increment pointer for next byte
	*(arduinoIP) = EEPROM.read(EEPROMPointer++); // Read third byte of arduino IP address and increment pointer for next byte
	*(arduinoIP) = EEPROM.read(EEPROMPointer++); // Read fourth byte of arduino IP address and increment pointer for next item read
}

/*
	Get the number of inputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of input devices
	numOfInputs: Pointer to the byte that stores number of inptus in configuration
*/
void Configurator::setNumOfInputs(byte EEPROMPointer, byte* numOfInputs) {
	*(numOfInputs) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Get the number of outputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of output devices
	numOfInputs: Pointer to the byte that stores number of outputs in configuration
*/
void Configurator::setNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs) {
	*(numOfOutputs) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPoitnter, then increment EEPROMPointer
}
