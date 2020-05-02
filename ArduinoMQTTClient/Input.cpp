// 
// 
// 

#include "Input.h"
Input::Input(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Input::Input(char const *const deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceName, deviceType, pinNum) {}
