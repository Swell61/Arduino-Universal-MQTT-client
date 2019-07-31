// Switch.h

#ifndef _SWITCH_h
#define _SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Switch : public Input {

};

#endif

