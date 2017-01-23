#include "ErrorCheck.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


KettleInfo kettleInfo;


void initErrorCheck(void){
    kettleInfo = newKettleInfo();
}


/* 高温エラー */
int hasHighTemperatureError(void){
	if((int)kettleInfo.getWaterTemperature()>=110){
		return TRUE;
	}
	return FALSE;
}


/* 加熱不能エラー */
int hasCannotHeatingError(void){
	static float pastTemp=0.0;
	if(kettleInfo.getWaterTemperature()<=(kettleInfo.getTargetTemperature()-5.0) 
	    && kettleInfo.getWaterTemperature()<pastTemp){
		return TRUE;
	}
	pastTemp = kettleInfo.getTargetTemperature();
	return FALSE;
}
