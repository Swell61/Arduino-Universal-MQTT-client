// 
// 
// 

#include "Output.h"
Output::Output(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Output::Output(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceName, deviceType, pinNum) {}
