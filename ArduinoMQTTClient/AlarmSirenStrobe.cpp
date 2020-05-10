// 
// 
// 

#include "AlarmSirenStrobe.h"
#include "MQTTDevice.h"

AlarmSirenStrobe::AlarmSirenStrobe(const char* alarmMqttCommandTopic, const char* alarmMqttStateTopic, const char* tamperMqttStateTopic, const char* tamperHighMessage, const char* tamperLowMessage,
	const byte sirenPinNum, const byte strobePinNum, const byte tamperSwitchPinNum)
	: Input(MQTTDevice::DEVICE_TYPE::ALARM_SIREN_STROBE), Output(MQTTDevice::DEVICE_TYPE::ALARM_SIREN_STROBE, alarmMqttCommandTopic, alarmMqttStateTopic),
	tamperSwitch(tamperMqttStateTopic, tamperSwitchPinNum, tamperHighMessage, tamperLowMessage), sirenPinNum(sirenPinNum), strobePinNum(strobePinNum) { }

void AlarmSirenStrobe::action(MQTTDevice::ACTION action, PubSubClient mqttClient) {
	switch (action) {
	case MQTTDevice::ACTION::OFF:
		digitalWrite(sirenPinNum, LOW);
		digitalWrite(strobePinNum, LOW);
		mqttClient.publish_P(getMQTTRespondTopic(), OFF_TEXT, strlen_P(OFF_TEXT), false);
		break;
	case MQTTDevice::ACTION::WARNING:
		digitalWrite(sirenPinNum, LOW);
		digitalWrite(strobePinNum, HIGH);
		mqttClient.publish_P(getMQTTRespondTopic(), WARNING_TEXT, strlen_P(WARNING_TEXT), false);
		break;
	case MQTTDevice::ACTION::ALARM:
		digitalWrite(sirenPinNum, HIGH);
		digitalWrite(strobePinNum, HIGH);
		mqttClient.publish_P(getMQTTRespondTopic(), ALARM_TEXT, strlen_P(ALARM_TEXT), false);
		break;
	}
}

void AlarmSirenStrobe::handleInput(PubSubClient mqttClient) {
	tamperSwitch.handleInput(mqttClient);
}
