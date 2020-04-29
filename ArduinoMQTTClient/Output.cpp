// 
// 
// 

#include "Output.h"
Output::Output(const MQTTDevice& mqttDevice) : MQTTDevice(mqttDevice) {}

char* Output::getDeviceName() {
	return deviceName;
}
