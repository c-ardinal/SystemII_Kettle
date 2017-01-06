#include "TemperatureControl.h"
#include "../DeviceControl/HeaterControl.h"
#include "../InfoManager/KettleInfo.h"


int doBoiling(void){
	setHeaterPower(culHeaterPid(getTargetTemperature(), getWaterTemperature()));
	return 0;
}



void doKeepWarm(void){

}



void switchKeepWarmMode(void){

}


int culHeaterPid(float target, float now){
	static float nowD=0.0, pastD=0.0, integral=0.0;
	
	pastD = nowD;
	nowD = (target - now);
	integral += ((nowD + pastD) / 2.0 * TIME);
	
	float tP = KP * nowD;
	float tI = KI * integral;
	float tD = KD * ((nowD - pastD) / TIME);
	
	float result = (tP + tI + tD)*100;
	if(result>=255.0)
		result = 255.0;
	else if(result<=0.0)
		result = 0.0;
	
	return (int)result;
}

