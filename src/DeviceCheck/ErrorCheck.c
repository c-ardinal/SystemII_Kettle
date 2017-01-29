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
 * @param	: 現在水温
 * @return	: エラー発生中ならTRUE、それ以外ならFALSE
 * ------------------------------------------------------ * 
 */
int hasHighTemperatureError(float NowTemperature){
	if(NowTemperature>=110.0){
		return TRUE;
	}
	return FALSE;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 現在水温が目標値よりも5度以上低く、
 * 			  かつ、今も温度が下がり続けているか確認する
 * @param	: 現在水温、目標水温
 * @return	: エラー発生中ならTRUE、それ以外ならFALSE
 * ------------------------------------------------------ * 
 */
int hasCannotHeatingError(float NowTemperature, float TargetTemperature){
	static float PastTemperature=0.0;
	int result = FALSE;
	if(NowTemperature<=(TargetTemperature-5.0)
		&& NowTemperature<PastTemperature){
		result = TRUE;
	}
	PastTemperature = NowTemperature;
	return result;
}
