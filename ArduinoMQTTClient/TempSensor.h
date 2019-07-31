// TempSensor.h

#ifndef _TEMPSENSOR_h
#define _TEMPSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class TempSensor : public Input {

};

#endif

