// 
// 
// 

#include "InputChange.h"
InputChange::InputChange(const byte pinNum) {
	bool initialState = digitalRead(pinNum) == HIGH;
	stateChangedTo = initialState;
	lastPinStateProcessed = initialState;
}

