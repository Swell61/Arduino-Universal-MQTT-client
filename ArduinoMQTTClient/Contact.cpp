// 
// 
// 

#include "Contact.h"
Contact::Contact(const MQTTDevice& mqttDevice) : Input(mqttDevice) {}

Contact::Contact(char const *const deviceName, const byte pinNum) : Input(deviceName, MQTTDevice::DEVICE_TYPE::CONTACT, pinNum) {}

void Contact::sendMessage() {}