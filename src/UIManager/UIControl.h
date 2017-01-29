/* 
 * ------------------------------------------------------ * 
 * @file	: UIControl.h
 * @brief	: UIControl.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _UI_CONTROL_H_
#define _UI_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"
#include "../General/Timer.h"


//LED識別ID
typedef enum{
	BOIL_LAMP,
	K_W_LAMP,
	LOCK_LAMP
}LampId_t;


//LCD制御用
void initLcd(void);
void write8bitLcd(int, int);
void write4bitLcd(int, int);
int readBusyFlag(void);
void waitLcd(void);
void drawStringToLcd(char *, int);
void draw3NumToLcd(int, int);
void drawNumToLcd(int, int);
void drawTemperature(int);
void drawKeepWarmMode(int);


//7segLED制御用
void init7SegLed(void);
void draw7SegLed(int);
void drawLeftOf7SegLed(int);
void drawRightOf7SegLed(int);


//単発LED制御用
void initLed(void);
void drawWaterLevel(int);
void onLamp(LampId_t);
void offLamp(LampId_t);
void revLamp(LampId_t);


#endif
