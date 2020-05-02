// 
// 
// 

#include "Switch.h"
Switch::Switch(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Switch::Switch(char const *const deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::SWITCH, pinNum) {}

void Switch::sendMessage() {}

