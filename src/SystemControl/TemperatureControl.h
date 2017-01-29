/* 
 * ------------------------------------------------------ * 
 * @file	: TemperatureControl.h
 * @brief	: TemperatureControl.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _TEMPERATURE_CONTROL_H_
#define _TEMPERATURE_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"
#include "../DeviceControl/HeaterControl.h"
#include "../UIManager/Buzzer.h"


void initTempControl(void);
void doBoiling(float);
void doCooling(void);
void doKeepWarm(float, float);
float switchKeepWarmMode(float);
int culHeaterPid(float, float);
void onHeaterSource(void);
void offHeaterSource(void);


#endif
