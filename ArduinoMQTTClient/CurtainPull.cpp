// 
// 
// 

#include "CurtainPull.h"
CurtainPull::CurtainPull(const MQTTDevice& mqttDevice) : Output(mqttDevice) {}
void CurtainPull::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (OPEN):
		break;
	case (CLOSE):
		break;
	}
}
