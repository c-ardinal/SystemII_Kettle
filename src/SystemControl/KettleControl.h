#ifndef _KETTLE_CONTROL_H_
#define _KETTLE_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"
#include "../InfoManager/KettleInfo.h"
#include "../General/Timer.h"
#include "../DeviceControl/HeaterControl.h"
#include "../DeviceControl/PumpControl.h"
#include "../UIManager/UIControl.h"
#include "../UIManager/Button.h"
#include "../UIManager/Buzzer.h"
#include "../DeviceCheck/SensorCheck.h"
#include "../DeviceCheck/ErrorCheck.h"
#include "TemperatureControl.h"
#include "KitchenTimerControl.h"


void initSystem(void);
void executeSystem(void);
void int_imia1(void);


#endif
