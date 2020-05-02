// 
// 
// 

#include "Output.h"
Output::Output(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

Output::Output(char const *const deviceMQTTTopic, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : MQTTDevice(deviceMQTTTopic, deviceType, pinNum) {}
