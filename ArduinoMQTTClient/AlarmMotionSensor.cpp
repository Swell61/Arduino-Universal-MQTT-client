// 
// 
// 

#include "AlarmMotionSensor.h"

AlarmMotionSensor::AlarmMotionSensor(const char* pirSensorMQTTTopic, const char* tamperSwitchMQTTTopic, const byte pirSensorPinNum, const byte tamperSwitchPinNum, const char* pirSensorMotionMessage,
	const char* pirSensorNoMotionMessage, const char* tamperSwitchTriggeredMessage, const char* tamperSwitchUntriggeredMessage) : 
	Input(MQTTDevice::DEVICE_TYPE::ALARM_MOTION_SENSOR),
	pirSensor(pirSensorMQTTTopic, pirSensorPinNum, pirSensorMotionMessage, pirSensorNoMotionMessage),
	tamperSwitch(tamperSwitchMQTTTopic, tamperSwitchPinNum, tamperSwitchTriggeredMessage, tamperSwitchUntriggeredMessage) {}

void AlarmMotionSensor::handleInput(PubSubClient& mqttClient) {
	pirSensor.handleInput(mqttClient);
	tamperSwitch.handleInput(mqttClient);
}
