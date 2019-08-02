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



byte Configurator::getNumOfInputs(byte EEPROMPointer) {
	return EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPointer, then increment EEPROMPointer
}

byte Configurator::getNumOfOutputs(byte EEPROMPointer) {
	return EEPROM.read(EEPROMPointer++); // Read the EEPROM at address EEPROMPoitnter, then increment EEPROMPointer
}
