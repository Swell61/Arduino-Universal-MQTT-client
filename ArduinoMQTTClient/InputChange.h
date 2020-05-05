// InputChange.h

#ifndef _INPUTCHANGE_h
#define _INPUTCHANGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
struct InputChange {
	InputChange(const byte pinNum);
	uint8_t stateChangedTo : 1;
	uint8_t lastPinStateProcessed : 1;
};

#endif

