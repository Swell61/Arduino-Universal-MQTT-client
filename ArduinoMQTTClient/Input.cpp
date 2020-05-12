// 
// 
// 

#include "Input.h"
Input::Input(const MQTTDevice::DEVICE_TYPE deviceType) : MQTTDevice(deviceType) {
}

bool Input::debounce() {
	unsigned long currentMillis = millis();

	if ((currentMillis - lastProcessedMillis) > DEBOUNCE_TIME_MILLIS) {
		lastProcessedMillis = currentMillis; // Debounce only called if there is a pending change. If debounce returns true, it will be processed
		return true;
	}
	return false;
}