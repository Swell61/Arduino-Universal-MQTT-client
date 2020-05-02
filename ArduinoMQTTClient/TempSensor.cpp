// 
// 
// 

#include "TempSensor.h"
TempSensor::TempSensor(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

TempSensor::TempSensor(char const *const deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::TEMP_SENSOR, pinNum) {}

void TempSensor::handleInput(PubSubClient mqttClient) {}