/* 
 * ------------------------------------------------------ * 
 * @file	: TemperatureControl.c
 * @brief	: 保温や沸騰機能に関する処理
 * ------------------------------------------------------ * 
 */
#include "TemperatureControl.h"


/* 
 * ------------------------------------------------------ * 
 * @function: 沸騰を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
 void initTempControl(void){
 	initHeater();
 }


/* 
 * ------------------------------------------------------ * 
 * @function: 沸騰を行う
 * @param	: 現在水温
 * @return	: void
 * ------------------------------------------------------ * 
 */
void doBoiling(float NowTemperature){
	static int tempMaxFlag=0, count=0, buzzerCount=0;
	setHeaterPower(255);
	// 水温が100度に達したらフラグON
	if(NowTemperature>=100.0)
		tempMaxFlag = 1;
	// 100度に達した後3分計測
	if(tempMaxFlag==1)
		count++;
	// 3分(=180秒)経ったら終了
	if(count>=5){
		if(buzzerCount++<3){
			playBuzzer(100);
		}
		else{
			tempMaxFlag = 0;
			count = 0;
			buzzerCount=0;
			setHeatState(BOIL_END);
		}
	}
}


/* 
 * ------------------------------------------------------ * 
 * @function: 自然冷却を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void doCooling(void){
	setHeaterPower(0);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 保温を行う
 * @param	: 目標水温、現在水温
 * @return	: void
 * ------------------------------------------------------ * 
 */
void doKeepWarm(float TargetTemperature, float NowTemperature){
	setHeaterPower(culHeaterPid(getTargetTemperature(), getWaterTemperature()));
}


/* 
 * ------------------------------------------------------ * 
 * @function: 保温モードの切り替えを行う
 * @param	: 現在の目標水温
 * @return	: 次の目標水温
 * ------------------------------------------------------ * 
 */
float switchKeepWarmMode(float NowTargetTemperature){
	switch((int)NowTargetTemperature){
		case (int)HIGH_TEMPERATURE_MODE:
			return SAVING_MODE;
		break;
		case (int)SAVING_MODE:
			return MILK_MODE;
		break;
		case (int)MILK_MODE:
			return HIGH_TEMPERATURE_MODE;
		break;
	}
	return 0;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターのPID制御量を算出する
 * @param	: 目標水温、現在水温
 * @return	: ヒータ制御量
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


/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターの電源を入れる
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void onHeaterSource(void){
	controlSource(ON);
}


/* 
 * ------------------------------------------------------ * 
 * @function: ヒーターの電源を切る
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void offHeaterSource(void){
	controlSource(OFF);
}
