// 
// 
// 

#include "Contact.h"
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(const char* deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::CONTACT, pinNum) {}

void Contact::sendMessage() {}