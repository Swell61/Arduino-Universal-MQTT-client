// Contact.h

#ifndef _CONTACT_h
#define _CONTACT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Input.h"
/*
	Author: Samuel Bailey
	Date: 31/07/2019
	Purpose: Logic for contact based input (ie a contact for a window or door to detect whether it is open or not)
*/
class Contact : public Input {
	void sendMessage() override;
};

#endif

