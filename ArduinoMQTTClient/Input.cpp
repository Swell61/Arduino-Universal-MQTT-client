// 
// 
// 

#include "Input.h"
#define EI_ARDUINO_INTERRUPTED_PIN
#define EI_NOTEXTERNAL  
#define EI_NOTPORTB 
#include <../EnableInterrupt/EnableInterrupt.h>
Input::Input(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Input::Input(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceMQTTTopic, deviceType, pinNum) {
}

void Input::interruptHandler() {
	inputs[arduinoInterruptedPin]->inputChange.pinChanged = true;
	inputs[arduinoInterruptedPin]->inputChange.pinChangedTo = arduinoPinState > 0;
}