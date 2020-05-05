// 
// 
// 

#include "Input.h"
extern volatile uint8_t arduinoInterruptedPin;
extern volatile uint8_t arduinoPinState;


Input* Input::inputs[19] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

Input::Input(const char* deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceMQTTTopic, deviceType, pinNum) {
}

void Input::interruptHandler() {
	inputs[arduinoInterruptedPin]->inputChange.stateChangedTo = arduinoPinState > 0;
}

bool Input::debounce() {
	unsigned long currentMillis = millis();
	if ((currentMillis - lastProcessedMillis) > DEBOUNCE_TIME_MILLIS) {
		lastProcessedMillis = currentMillis;
		return true;
	}
	return false;
}