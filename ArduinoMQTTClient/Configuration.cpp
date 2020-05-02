// 
// 
// 

#include "Configuration.h"

Configuration::Configuration(char* const* const controllerName, IPAddress* const controllerIPAddress, IPAddress* const brokerIPAddress, byte* const* const macAddress,
	Output* const* const outputs, Input* const* const inputs, byte const numOfOutputs, byte const numOfInputs) : controllerName(controllerName),
	controllerIPAddress(controllerIPAddress), brokerIPAddress(brokerIPAddress), macAddress(macAddress), outputs(outputs), inputs(inputs), numOfOutputs(numOfOutputs),
	numOfInputs(numOfInputs) {}
