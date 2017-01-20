#include "ErrorCheck.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


/* 高温エラー */
int hasHighTemperatureError(void){
	if((int)getWaterTemperature()>=110){
		return 1;
	}
	return 0;
}


/* 加熱不能エラー */
int hasCannotHeatingError(void){
	static float pastTemp=0;
	if(getWaterTemperature()<=(getTargetTemperature()-5.0) && getTargetTemperature()<pastTemp){
		return 1;
	}
	pastTemp = getTargetTemperature();
	return 0;
}
