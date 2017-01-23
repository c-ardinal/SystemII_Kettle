/* 
 * ------------------------------------------------------ * 
 * @file	: ErrorCheck.c
 * @brief	: システム上で何かしらのエラーが発生しているかチェックを行う
 * ------------------------------------------------------ * 
 */
#include "ErrorCheck.h"



/* 
 * ------------------------------------------------------ * 
 * @function: 水温が110度を超えているか確認する
 * @param	: void
 * @return	: エラー発生中ならTRUE、それ以外ならFALSE
 * ------------------------------------------------------ * 
 */
int hasHighTemperatureError(void){
	if((int)getWaterTemperature()>=110){
		return TRUE;
	}
	return FALSE;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 現在水温が目標値よりも5度以上低く、
 * 			  かつ、今も温度が下がり続けているか確認する
 * @param	: void
 * @return	: エラー発生中ならTRUE、それ以外ならFALSE
 * ------------------------------------------------------ * 
 */
int hasCannotHeatingError(void){
	static float pastTemp=0.0;
	if(getWaterTemperature()<=(getTargetTemperature()-5.0) 
		&& getWaterTemperature()<pastTemp){
		return TRUE;
	}
	pastTemp = getTargetTemperature();
	return FALSE;
}
