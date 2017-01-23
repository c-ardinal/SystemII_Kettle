/* 
 * ------------------------------------------------------ * 
 * @file	: SensorCheck.h
 * @brief	: SensorCheck.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
 #ifndef _SENSOR_CHECK_H_
#define _SENSOR_CHECK_H_


#include "../3048f.h"
#include "../constant.h"
#include "../UIManager/UIControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


void initSensor(void);
int isHeatable(void);
void checkWaterTemperature(void);
void checkLidState(void);
int gainWaterLevel(void);
void int_irq4(void);


#endif
