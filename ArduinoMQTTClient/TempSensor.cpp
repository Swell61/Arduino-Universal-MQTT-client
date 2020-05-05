// 
// 
// 

#include "TempSensor.h"

TempSensor::TempSensor(const char* deviceMQTTTopic, const byte pinNum) : Input(deviceMQTTTopic, MQTTDevice::DEVICE_TYPE::TEMP_SENSOR, pinNum) {}

void TempSensor::handleInput(PubSubClient mqttClient) {}