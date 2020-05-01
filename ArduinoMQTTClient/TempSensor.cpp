// 
// 
// 

#include "TempSensor.h"
TempSensor::TempSensor(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

TempSensor::TempSensor(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Input(deviceName, deviceType, pinNum) {}

void TempSensor::sendMessage() {}