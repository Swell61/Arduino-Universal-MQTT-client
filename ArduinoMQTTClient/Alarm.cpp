// 
// 
// 

#include "Alarm.h"

void Alarm::action(MQTTDevice::ACTION action) {
	switch (action) {
	case (INFO):
		break;
	case (CAUTION):
		break;
	case (WARNING):
		break;
	}
}
