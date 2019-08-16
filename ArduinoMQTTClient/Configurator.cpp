// 
// 
// 

#include "Configurator.h"
#include "Alarm.h"
#include "Switch.h"
#include "Contact.h"
#include "Relay.h"
#include <EEPROM.h>

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
	*(inputs) = (Input*)calloc(sizeof(Input), *(numOfInputs));
	readInputs(EEPROMPointer, inputs, *(numOfInputs));
	// Read num of outputs
	readNumOfOutputs(EEPROMPointer, numOfOutputs);
	// Read outputs
	*(outputs) = (Output*)calloc(sizeof(Output), *(numOfOutputs));
	readOutputs(EEPROMPointer, outputs, *(numOfOutputs));

}

Configurator::Configurator(byte* MACAddress, byte* arduinoIP, byte* MQTTBrokerIP, byte* numOfInputs, Input** inputs, byte* numOfOutputs, Output** outputs) : MACAddress(MACAddress),
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
	numOfInputs: Pointer to the byte that stores number of inputs in configuration
*/
void Configurator::readNumOfInputs(byte EEPROMPointer, byte* numOfInputs) {
	*(numOfInputs) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Read the inputs stored in EEPROM
	The data is stored with the input type stored infront of the input object. This way, the correct
	case can be done when passing EEPROM.get the object to fill.

	Parameters:
	EEPROMPointer: Location of the first byte for inputs stored in EEPROM
	inputs: Pointer to block of memory to store inputs in
	numOfInputs: Number of inputs stored in EEPROM
*/
void Configurator::readInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs) {
	// TODO: Read each input, check its type variable and cast to the correct type
	for (byte inputIndex = 0; inputIndex < numOfInputs; inputIndex += 2) { // Loop through all inputs stored in EEPROM
		switch ((Input::DEVICE_TYPE)EEPROM.read(EEPROMPointer++ + inputIndex)) // Read the input type and cast to Input type
		{
		case Input::DEVICE_TYPE::CONTACT:
			*(inputs) = new Contact();
			break;
		case Input::DEVICE_TYPE::SWITCH:
			*(inputs) = new Switch();
			break;
		}
		EEPROM.get(EEPROMPointer, **(inputs + inputIndex + 1)); // Retrieve each input and store in the array
		EEPROMPointer += sizeof(**(inputs + inputIndex + 1)); // Increment the pointer by the correct value
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
void Configurator::readOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs) {
	// TODO: Read each output, check its type variable and cast to the correct type
	for (byte outputIndex = 0; outputIndex < numOfOutputs; outputIndex += 2) { // Loop through all outputs stored in EEPROM
		switch ((Output::DEVICE_TYPE)EEPROM.read(EEPROMPointer++))
		{
		case Output::DEVICE_TYPE::ALARM:
			*(outputs) = new Alarm();
			break;
		case Output::DEVICE_TYPE::RELAY:
			*(outputs) = new Relay();
			break;
		default:
			break;
		}
		
		EEPROM.get(EEPROMPointer, **(outputs + outputIndex + 1)); // Retrieve each output and store in the array
		EEPROMPointer += sizeof(**(outputs + outputIndex + 1)); // Increment the pointer by the correct amount
	}
}



/*
	Write all 6 bytes of the MAC address from the array into EEPROM, if changed

	Parameters:
	EEPROMPointer: Location of first byte of 6 MAC address bytes
	MACAddress: Pointer to MAC address array held in configuration
*/
void Configurator::writeMACAddress(byte EEPROMPointer, byte* MACAddress) {
	EEPROM.update(EEPROMPointer++, *(MACAddress)); // Write first byte of MAC address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MACAddress + 1)); // Write second byte of MAC address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MACAddress + 2)); // Write third byte of MAC address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MACAddress + 3)); // Write fourth byte of MAC address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MACAddress + 4)); // Write fifth byte of MAC address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MACAddress + 5)); // Write sixth byte of MAC address and increment pointer for next item write
}

/*
	Write all 4 bytes of the arduinos IP address to EEPROM, if changed

	Parameters:
	EEPROMPointer: Location of first byte of 4 arduino IP address bytes
	arduinoIP: Pointer to arduino IP address array held in configuration
*/
void Configurator::writeArduinoIP(byte EEPROMPointer, byte* arduinoIP) {
	EEPROM.update(EEPROMPointer++, *(arduinoIP)); // Write first byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(arduinoIP + 1)); // Write second byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(arduinoIP + 2)); // Write third byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(arduinoIP + 3)); // Write fourth byte of arduino IP address and increment pointer for next item write
}

/*
	Write all 4 bytes of the MQTT broker IP address to EEPROM, if changed

	Parameters:
	EEPROMPointer: Location of first byte of 4 MQTT broker IP address bytes
	MQTTBrokerIP: Pointer to MQTT broker IP address array held in configuration
*/
void Configurator::writeMQTTBrokerIP(byte EEPROMPointer, byte* MQTTBrokerIP) {
	EEPROM.update(EEPROMPointer++, *(MQTTBrokerIP)); // Write first byte of MQTT broker IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MQTTBrokerIP + 1)); // Write second byte of MQTT broker IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MQTTBrokerIP + 2)); // Write third byte of MQTT broker IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(MQTTBrokerIP + 3)); // Write fourth byte of MQTT broker IP address and increment pointer for next item Write
}

/*
	Write the number of inputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of input devices
	numOfInputs: Pointer to the byte that stores number of inputs in configuration
*/
void Configurator::writeNumOfInputs(byte EEPROMPointer, byte* numOfInputs) {
	EEPROM.update(EEPROMPointer++, *(numOfInputs)); // Write the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Write the inputs stored in EEPROM

	Parameters:
	EEPROMPointer: Location of the first byte for inputs stored in EEPROM
	inputs: Pointer to block of memory to store inputs in
	numOfInputs: Number of inputs stored in EEPROM
*/
void Configurator::writeInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs) {
	for (byte inputIndex = 0; inputIndex < numOfInputs; inputIndex++) { // Loop through all inputs stored in EEPROM
		EEPROM.put(EEPROMPointer++, **(inputs + inputIndex)); // Retrieve each input and store in the array
	}
}

/*
	Write the number of outputs devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of output devices
	numOfInputs: Pointer to the byte that stores number of outputs in configuration
*/
void Configurator::writeNumOfOutputs(byte EEPROMPointer, byte* numOfOutputs) {
	EEPROM.update(EEPROMPointer++, *(numOfOutputs)); // Write the EEPROM at address EEPROMPoitnter, then increment EEPROMPointer
}

/*
	Write the outputs stored in EEPROM

	Parameters:
	EEPROMPointer: Location of first byte for the outputs stored in EEPROM
	outputs: Pointer to block of memory to store inputs in
	numOfOutputs: Number of outputs stored in EEPROM
*/
void Configurator::writeOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs) {
	for (byte outputIndex = 0; outputIndex < numOfOutputs; outputIndex++) { // Loop through all outputs stored in EEPROM
		EEPROM.put(EEPROMPointer++, *(outputs + numOfOutputs)); // Retrieve each output and store in the array
	}
}
