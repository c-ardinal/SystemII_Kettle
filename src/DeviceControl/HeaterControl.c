/* 
 * ------------------------------------------------------ * 
 * @file	: HeaterControl.c
 * @brief	: ヒーターの制御を行う
 * ------------------------------------------------------ * 
 */
#include "HeaterControl.h"


/* 
 * ------------------------------------------------------ * 
 * @function: ヒータの初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initHeater(void){
	P6.DDR = 0x70;
	DA.DR0 = 0x00;
	DA.CR.BIT.DAOE0 = 1;
	controlSource(ON);
}
           

/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターの加熱量を制御する
 * @param	: ヒーター加熱量(0〜255)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setHeaterPower(int power){
	DA.DR0 = (power*2000)/256;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターの電源を制御する
 * @param	: 電源操作(ON, OFF)
 * @sa		: ON, OFFはconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void controlSource(int state){
	P6.DR.BIT.B6 = state;
}
