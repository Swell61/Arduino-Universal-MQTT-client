// 
// 
// 

#include "Input.h"
#define EI_ARDUINO_INTERRUPTED_PIN
#include <../EnableInterrupt/EnableInterrupt.h>
Input::Input(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Input::Input(char const *const deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceName, deviceType, pinNum) {
}

void Input::interruptHandler() {
	inputs[arduinoInterruptedPin]->inputChange.pinChanged = true;
	inputs[arduinoInterruptedPin]->inputChange.pinChangedTo = arduinoPinState > 0;
}