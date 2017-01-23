/* 
 * ------------------------------------------------------ * 
 * @file	: ErrorCheck.h
 * @brief	: ErrorCheck.c用のヘッダファイル
 * ------------------------------------------------------ * 
 */
#ifndef _ERROR_CHECK_H_
#define _ERROR_CHECK_H_


#include "../3048f.h"
#include "../constant.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


int hasHighTemperatureError(void);
int hasCannotHeatingError(void);


#endif
