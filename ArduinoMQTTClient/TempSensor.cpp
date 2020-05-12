// 
// 
// 

#include "TempSensor.h"

TempSensor::TempSensor(const char* deviceMQTTTopic, const byte pinNum) : Input(MQTTDevice::DEVICE_TYPE::TEMP_SENSOR), pinNum(pinNum), mqttStateTopic(deviceMQTTTopic) {}

void TempSensor::handleInput(PubSubClient mqttClient) {
	// Not yet implemented
}