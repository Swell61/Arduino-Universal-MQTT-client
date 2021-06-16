#ifndef _LATCHINGRELAYTWOPOLE_h
#define _LATCHINGRELAYTWOPOLE_h

#include "Output.h"

/*
    Author: Samuel Bailey
    Date: 15/06/21
    Purpose: Latching relay that has 2 pole control (set and reset)
*/

class LatchingRelayTwoPole : public Output {
public:
    LatchingRelayTwoPole(const char* mqttStateTopic, const char* mqttRespondTopic, const uint8_t setPoleNum, const uint8_t resetPoleNum);
    void action(MQTTDevice::ACTION action, PubSubClient& mqttClient);

private:
    void togglePole(uint8_t pinNum);
    void toggleOn(PubSubClient& mqttClient);
    void toggleOff(PubSubClient& mqttClient);
    uint8_t setPoleNum;
    uint8_t resetPoleNum;
    uint8_t poleHoldTime = 5; // Time to hold a pole for it to register. Datasheet states 3ms.
    bool lastState = LOW;
};

#endif