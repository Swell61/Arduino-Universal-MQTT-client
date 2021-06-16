#ifndef _LATCHINGRELAYTWOPOLE_h
#define _LATCHINGRELAYTWOPOLE_h

#include "Output.h"

class LatchingRelayTwoPole : public Output {
public:
    LatchingRelayTwoPole(const char* mqttStateTopic, const char* mqttRespondTopic, const unsigned short int setPoleNum, const unsigned short int resetPoleNum);
    void action(MQTTDevice::ACTION action, PubSubClient& mqttClient);

private:
    void togglePole(unsigned short int pinNum);
    void toggleOn(PubSubClient& mqttClient);
    void toggleOff(PubSubClient& mqttClient);
    unsigned short int setPoleNum;
    unsigned short int resetPoleNum;
    unsigned short int poleHoldTime = 5; // Time to hold a pole for it to register. Datasheet states 3ms.
    bool lastState = LOW;
};

#endif