// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <IPAddress.h>

class Configuration {

private:
	char* controllerName; // Name of controller for MQTT topic
	IPAddress ipAddress; // Static IP to remove UDP code from library to save on flash
	byte macAddress[6];
	byte deviceCount;

public:
	Configuration(char* controllerName, IPAddress ipAddress, byte macAddress, byte deviceCount);

};

#endif

