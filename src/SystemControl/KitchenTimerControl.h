/* 
 * ------------------------------------------------------ * 
 * @file	: KitchenTimer.h
 * @brief	: KitchenTimer.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _KITCHEN_TIMER_CONTROL_H_
#define _KITCHEN_TIMER_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"
#include "../UIManager/Buzzer.h"


int kitchenTimerCountUp(int);
int kitchenTimerCountDown(int);
int convertSecondToMinute(int);


#endif
