#include "ErrorCheck.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


/* 高温エラー */
int hasHighTemperatureError(void){
	if((int)getWaterTemperature()>=110){
		return TRUE;
	}
	return FALSE;
}


/* 加熱不能エラー */
int hasCannotHeatingError(void){
	static float pastTemp=0.0;
	if(getWaterTemperature()<=(getTargetTemperature()-5.0) && getWaterTemperature()<pastTemp){
		return TRUE;
	}
	pastTemp = getTargetTemperature();
	return FALSE;
}
