// 
// 
// 

#include "TempSensor.h"
TempSensor::TempSensor(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

TempSensor::TempSensor(char const *const deviceMQTTTopic, const byte pinNum) : Input(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::TEMP_SENSOR, pinNum) {}

void TempSensor::handleInput(PubSubClient mqttClient) {}