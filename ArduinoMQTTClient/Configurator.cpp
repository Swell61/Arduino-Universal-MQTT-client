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
	readIP(EEPROMPointer, arduinoIP);
	// Read MQTT broker IP address
	readIP(EEPROMPointer, MQTTBrokerIP);
	// Read number of inputs
	readNum(EEPROMPointer, numOfInputs);
	// Read num of outputs
	readNum(EEPROMPointer, numOfOutputs);
	// Read inputs
	*(inputs) = (Input*)calloc(sizeof(Input), *(numOfInputs));
	readInputs(EEPROMPointer, inputs, *(numOfInputs));
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
	Read all 4 bytes of an IP address and set the values in the array of the pointer

	Parameters:
	EEPROMPointer: Location of first byte of 4 arduino IP address bytes
	IP: Pointer to IP address array held in configuration to write to
*/
void Configurator::readIP(byte EEPROMPointer, byte* IP) {
	*(IP) = EEPROM.read(EEPROMPointer++); // Read first byte of arduino IP address and increment pointer for next byte
	*(IP + 1) = EEPROM.read(EEPROMPointer++); // Read second byte of arduino IP address and increment pointer for next byte
	*(IP + 2) = EEPROM.read(EEPROMPointer++); // Read third byte of arduino IP address and increment pointer for next byte
	*(IP + 3) = EEPROM.read(EEPROMPointer++); // Read fourth byte of arduino IP address and increment pointer for next item read
}

/*
	Read the number of input or output devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of input devices
	num: Pointer to the byte that stores number of inputs or outputs in configuration
*/
void Configurator::readNum(byte EEPROMPointer, byte* num) {
	*(num) = EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Read the inputs stored in EEPROM
	The data is stored with the input type stored infront of the input object. This way, the correct
	case can be done when passing EEPROM.get the object to fill.

	Parameters:
	EEPROMPointer: Location of the first byte for inputs stored in EEPROM
	inputs: Pointer to block of memory that stores the inputs
	numOfInputs: Number of inputs stored in EEPROM
*/
void Configurator::readInputs(byte EEPROMPointer, Input** inputs, byte numOfInputs) {
	// TODO: Read each input, check its type variable and cast to the correct type
	for (byte inputIndex = 0; inputIndex < numOfInputs; inputIndex++) { // Loop through all inputs stored in EEPROM
		switch ((Input::DEVICE_TYPE)EEPROM.read(EEPROMPointer++)) // Read the input type and cast to Input type
		{
		case Input::DEVICE_TYPE::CONTACT:
			*(inputs) = new Contact();
			break;
		case Input::DEVICE_TYPE::SWITCH:
			*(inputs) = new Switch();
			break;
		}
		EEPROM.get(EEPROMPointer, *(*(inputs) + inputIndex)); // Retrieve each input and store in the array
		EEPROMPointer += sizeof(*(*(inputs) + inputIndex)); // Increment the pointer by the correct value
	}
}

/*
	Read the outputs stored in EEPROM

	Parameters:
	EEPROMPointer: Location of first byte for the outputs stored in EEPROM
	outputs: Pointer to block of memory that stores pointers to the outputs
	numOfOutputs: Number of outputs stored in EEPROM
*/
void Configurator::readOutputs(byte EEPROMPointer, Output** outputs, byte numOfOutputs) {
	// TODO: Read each output, check its type variable and cast to the correct type
	for (byte outputIndex = 0; outputIndex < numOfOutputs; outputIndex++) { // Loop through all outputs stored in EEPROM
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
		
		EEPROM.get(EEPROMPointer, *(*(outputs) + outputIndex)); // Retrieve each output and store in the array
		EEPROMPointer += sizeof(*(*(outputs) + outputIndex)); // Increment the pointer by the correct amount
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
	Write all 4 bytes of an IP address to EEPROM, if changed

	Parameters:
	EEPROMPointer: Location of first byte of 4 arduino IP address bytes
	IP: Pointer to arduino IP address array held in configuration
*/
void Configurator::writeIP(byte EEPROMPointer, byte* IP) {
	EEPROM.update(EEPROMPointer++, *(IP)); // Write first byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(IP + 1)); // Write second byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(IP + 2)); // Write third byte of arduino IP address and increment pointer for next byte
	EEPROM.update(EEPROMPointer++, *(IP + 3)); // Write fourth byte of arduino IP address and increment pointer for next item write
}

/*
	Write the number of input or output devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of byte in EEPROM that stores number of input devices
	num: Pointer to the byte that stores number of inputs in configuration
*/
void Configurator::writeNum(byte EEPROMPointer, byte* num) {
	EEPROM.update(EEPROMPointer++, *(numOfInputs)); // Write the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

/*
	Write the MQTT devices stored in EEPROM

	Parameters:
	EEPROMPointer: Location of the first byte for inputs stored in EEPROM
	MQTTDevices: Pointer to block of memory that stores pointers to the MQTT devices
	numOfDevices: Number of inputs stored in EEPROM
*/
void Configurator::writeMQTTDevices(byte EEPROMPointer, MQTTDevice** mqttDevice, byte numOfDevices) {
	for (byte inputIndex = 0; inputIndex < numOfDevices; inputIndex++) { // Loop through all inputs stored in EEPROM
		EEPROM.update(EEPROMPointer++, (byte)(*(mqttDevice) + inputIndex)->deviceType); // Write the device type for identification when reading
		EEPROM.put(EEPROMPointer, *(*(mqttDevice) + inputIndex)); // Retrieve each input and store in the array
		EEPROMPointer += sizeof(*(*(mqttDevice)+inputIndex)); // Increment the pointer by the correct amount
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
