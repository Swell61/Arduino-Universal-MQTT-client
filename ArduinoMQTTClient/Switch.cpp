// 
// 
// 

#include "Switch.h"
Switch::Switch(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Switch::Switch(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Input(deviceName, deviceType, pinNum) {}

void Switch::sendMessage() {}

