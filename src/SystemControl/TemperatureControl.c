/* 
 * ------------------------------------------------------ * 
 * @file	: TemperatureControl.c
 * @brief	: 保温や沸騰機能に関する処理
 * ------------------------------------------------------ * 
 */
#include "TemperatureControl.h"
#include "../DeviceControl/HeaterControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../UIManager/Buzzer.h"


/* 
 * ------------------------------------------------------ * 
 * @function: 沸騰を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void doBoiling(void){
	static int tempMaxFlag=0, count=0, buzzerCount=0;
	setHeaterPower(255);
	// 水温が100度に達したらフラグON
	if(getWaterTemperature()>=100)
		tempMaxFlag = 1;
	// 100度に達した後3分計測
	if(tempMaxFlag==1)
		count++;
	// 3分経ったら終了
	if(count>=5){
		if(buzzerCount++<3){
			playBuzzer(100);
		}
		else{
			tempMaxFlag = 0;
			count = 0;
			buzzerCount=0;
			setHeatState(KEEP_WARM);
		}
	}
}


/* 
 * ------------------------------------------------------ * 
 * @function: 保温を行う
 * @param	: mode(PREPARATION::自然冷却、START::保温開始)
 * @sa		: PREPARATION, STARTはconstant.hに宣言
 * @return	: void
 * ------------------------------------------------------ * 
 */
void doKeepWarm(int mode){
	switch(mode){
		case PREPARATION:
			setHeaterPower(0);
		break;
		case START:
			setHeaterPower(
				culHeaterPid(
					getTargetTemperature(), getWaterTemperature()
				)
			);
		break;
		default:
		break;
	}
}


/* 
 * ------------------------------------------------------ * 
 * @function: 保温モードの切り替えを行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void switchKeepWarmMode(void){
	switch((int)getTargetTemperature()){
		case (int)HIGH_TEMPERATURE_MODE:
			setTargetTemperature(SAVING_MODE);
		break;
		case (int)SAVING_MODE:
			setTargetTemperature(MILK_MODE);
		break;
		case (int)MILK_MODE:
			setTargetTemperature(HIGH_TEMPERATURE_MODE);
		break;
	}
}


/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターのPID制御量を算出する
 * @param	: target::目標水温、now::現在水温
 * @return	: ヒータ制御量(int)
 * ------------------------------------------------------ * 
 */
int culHeaterPid(float target, float now){
	static float nowD=0.0, pastD=0.0, integral=0.0;
	
	float kP = 0.6 * KC;
	float kI = kP / (0.5 * PU);
	float kD = kP * (0.125 * PU);
	
	pastD = nowD;
	nowD = (target - now);
	integral += ((nowD + pastD) / 2.0);
	
	float tP = kP * nowD;
	float tI = kI * integral;
	float tD = kD * (nowD - pastD);
	
	int result = (int)(tP + tI + tD);
	
	if(result>=255)
		result = 255;
	else if(result<=0)
		result = 0;
	
	return result;
}

