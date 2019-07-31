// Input.h

#ifndef _INPUT_h
#define _INPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Input : public MQTTDevice {

};

#endif

