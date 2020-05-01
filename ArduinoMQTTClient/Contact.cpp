// 
// 
// 

#include "Contact.h"
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(const char* deviceName, const MQTTDevice::DEVICE_TYPE deviceType, const byte pinNum) : Input(deviceName, deviceType, pinNum) {}

void Contact::sendMessage() {}