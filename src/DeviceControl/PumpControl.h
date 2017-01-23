/* 
 * ------------------------------------------------------ * 
 * @file	: PumpControl.h
 * @brief	: PumpControl.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _PUMP_CONTROL_H_
#define _PUMP_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"
#include "../InfoManager/KettleInfo.h"


void initPump(void);
void doPump(void);
void stopPump(void);


#endif
