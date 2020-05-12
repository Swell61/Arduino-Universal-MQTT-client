// InputChange.h

#ifndef _INPUTCHANGE_h
#define _INPUTCHANGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Keeps track of current pin status vs last processed state. If they are different, the associated input probably needs to be processed (unless something like a debounce is running)
*/
struct InputChange {
	InputChange(const byte pinNum); // Initialises input change to correct state when booting
	uint8_t stateChangedTo : 1; // Only requires one bit of the byte
	uint8_t lastPinStateProcessed : 1; // Only requires one bit of the byte
};

#endif

