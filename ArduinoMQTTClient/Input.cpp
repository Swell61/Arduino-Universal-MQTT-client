// 
// 
// 

#include "Input.h"
#define EI_ARDUINO_INTERRUPTED_PIN
#include <../EnableInterrupt/EnableInterrupt.h>
Input* Input::inputs[19] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

Input::Input(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Input::Input(const char* deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceMQTTTopic, deviceType, pinNum) {
}

void Input::interruptHandler() {
	inputs[arduinoInterruptedPin]->inputChange.pinChanged = true;
	inputs[arduinoInterruptedPin]->inputChange.pinChangedTo = arduinoPinState > 0;
}