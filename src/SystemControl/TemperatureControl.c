#include "TemperatureControl.h"
#include "../DeviceControl/HeaterControl.h"
#include "../InfoManager/KettleInfo.h"

static int pid = 0;

int doBoiling(void){
	pid = culHeaterPid(getTargetTemperature(), getWaterTemperature());
	setHeaterPower(pid);
	return 0;
}



int doKeepWarm(void){
	return pid;
}



void switchKeepWarmMode(void){

}


int culHeaterPid(float target, float now){
	static float nowD=0.0, pastD=0.0, integral=0.0;
	
	float kP = 0.5 * KC;
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

