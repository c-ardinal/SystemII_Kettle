/* 
 * ------------------------------------------------------ * 
 * @file	: Buzzer.h
 * @brief	: Buzzer.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _BUZZER_H_
#define _BUZZER_H_


#include "../3048f.h"
#include "../constant.h"


void initBuzzer(void);
void playBuzzer(int);
void onBuzzer(void);
void offBuzzer(void);


#endif
