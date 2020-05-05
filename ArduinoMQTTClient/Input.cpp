// 
// 
// 

#include "Input.h"



Input::Input(const MQTTDevice::DEVICE_TYPE deviceType) : MQTTDevice(deviceType) {
}



bool Input::debounce() {
	unsigned long currentMillis = millis();
	if ((currentMillis - lastProcessedMillis) > DEBOUNCE_TIME_MILLIS) {
		lastProcessedMillis = currentMillis;
		return true;
	}
	return false;
}