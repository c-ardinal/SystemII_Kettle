//#ifndef _GENERAL_TIMER_H_
//#define _GENERAL_TIMER_H_


#include "../3048f.h"


/* 割り込み許可マクロ */
#define STI() asm volatile ("andc.b #0x7f, ccr")


void initTimer(void);
void timer250ns(void);
void timer10us(int);
void timer1ms(int);


//#endif
