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


void doBoiling(void);
void doKeepWarm(int);
void switchKeepWarmMode(void);
int culHeaterPid(float, float);


#endif
