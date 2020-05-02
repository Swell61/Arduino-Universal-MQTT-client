// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <IPAddress.h>
#include "Output.h"
#include "Input.h"

/*
	Author: Samuel Bailey
	Date: 30/07/2019
	Purpose: Holds the current configuration for the system
*/

class Configuration {

private:
	char* const *const controllerName; // Name of controller for MQTT topic
	IPAddress* const controllerIPAddress; // Static IP to remove UDP code (for DHCP) from library to save on flash
	IPAddress* const brokerIPAddress;
	byte* const *const macAddress;
	Output* const *const outputs; // Constant pointer to an array of constant Output pointers
	Input* const *const inputs; // Constant pointer to an array of constant Input pointers
	byte const numOfOutputs; // Constant pointer to a constant byte
	byte const numOfInputs; // Constant pointer to a constant byte

public:
	Configuration(char* const* const controllerName, IPAddress* const controllerIPAddress, IPAddress* const brokerIPAddress, byte* const* const macAddress,
		Output* const* const outputs, Input* const* const inputs, byte const numOfOutputs, byte const numOfInputs);
	char* const* const getControllerName() { return controllerName; }
	IPAddress* const getControllerIPAddress() { return controllerIPAddress;  }
	byte* const *const getMACAddress() { return macAddress; }
	Output* const* const getOutputs() { return outputs; }
	Input* const* const getInputs() { return inputs; }
	byte const getNumOfOuputs() { return numOfOutputs; }
	byte const getNumOfInputs() { return numOfInputs; }
};

#endif

