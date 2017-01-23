#ifndef _KITCHEN_TIMER_CONTROL_H_
#define _KITCHEN_TIMER_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"


void initKitchenTimer(void);
void kitchenTimerCountUp(void);
void kitchenTimerCountDown(void);
int convertSecondToMinute(void);


#endif
