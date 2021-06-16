// 
// 
// 

#include "InputChange.h"

InputChange::InputChange(const uint8_t pinNum) {
	/* Physical devices like switches won't start in a known position. Find the current position and inputChange so it will fire on first change. Without this, if a switch starts
		in the opposite position to the default start position, the second change state will the first change to be processed (it will miss the first change)
	*/
	stateChangedTo = lastPinStateProcessed = digitalRead(pinNum) == HIGH;
}

