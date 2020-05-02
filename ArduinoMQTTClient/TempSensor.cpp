// 
// 
// 

#include "TempSensor.h"
TempSensor::TempSensor(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

TempSensor::TempSensor(const char* deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::TEMP_SENSOR, pinNum) {}

void TempSensor::sendMessage() {}