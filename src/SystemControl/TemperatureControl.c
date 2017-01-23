#include "TemperatureControl.h"
#include "../DeviceControl/HeaterControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../UIManager/Buzzer.h"


/* 沸騰実行関数 */
int doBoiling(void){
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
			setHeatState(KEEP_WARM);
			return 1;
		}
	}
	return 0;
}


/* 保温実行関数 */
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


/* 保温モード切り替え関数 */
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


/* 保温用PID制御値算出関数 */
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

