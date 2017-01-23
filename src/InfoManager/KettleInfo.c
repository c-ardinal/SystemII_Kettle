/* 
 * ------------------------------------------------------ * 
 * @file	: KettleInfo.c
 * @brief	: センサ値やシステムの状態を保持する
 * ------------------------------------------------------ * 
 */
#include "KettleInfo.h"


/* 
 * ------------------------------------------------------ * 
 * @brief	: システムの状態や情報を管理する
 * @sa		: 内訳はKettleInfo.hに定義
 * ------------------------------------------------------ * 
 */
static info_t this = {0, 0, 0.0, 0, 0, 0, 0, 0.0};


/* 
 * ------------------------------------------------------ * 
 * @function: 加熱状態を保持する
 * @param	: 加熱状態(NONE, BOIL, KEEP_WARM)
 * @sa		: 加熱状態はconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setHeatState(int heatState){
	this.heatState = heatState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ポンプの状態を保持する
 * @param	: ポンプ状態(SUPPLY_NO, SUPPLY_NOW)
 * @sa		: ポンプ状態はconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setPumpState(int pumpState){
	this.pumpState = pumpState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水温情報を保持する
 * @param	: 水温(int)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setWaterTemperature(float waterTemperature){
	this.waterTemperature = waterTemperature;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ふたの状態を保持する
 * @param	: ふたの状態(CLOSE, OPEN)
 * @sa		: ふたの状態はconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setLidState(int lidState){
	this.lidState = lidState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水位情報を保持する
 * @param	: 水位(0:空、1〜4:正常、5:満水)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setWaterLevel(int waterLevel){
	this.waterLevel = waterLevel;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 給湯ロックの状態を保持する
 * @param	: 給湯ロックの状態(UNLOCK, LOCK)
 * @sa		: 給湯ロックの状態はconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setLockState(int lockState){
	this.lockState = lockState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマ残り時間を保持する
 * @param	: キッチンタイマ残り時間(0〜KITCHEN_TIMER_MAX_TIME)
 * @sa		: KITCHEN_TIMER_MAX_TIMEはconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setRemainingTime(int remainigTime){
	this.remainingTime = remainigTime;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 目標温度を保持
 * @param	: 目標温度(HIGH_TEMPERATURE_MODE, SAVING_MODE, MILK_MODE)
 * @sa		: 目標温度はconstant.hに定義
 * @return	: void
 * ------------------------------------------------------ * 
 */
void setTargetTemperature(float targetTemperature){
	this.targetTemperature = targetTemperature;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 加熱状態を取得する
 * @param	: void
 * @sa		: 加熱状態はconstant.hに定義
 * @return	: 加熱状態(NONE, BOIL, KEEP_WARM)
 * ------------------------------------------------------ * 
 */
int getHeatState(void){
	return this.heatState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ポンプ状態を取得する
 * @param	: void
 * @sa		: ポンプ状態はconstant.hに定義
 * @return	: ポンプ状態(SUPPLY_NO, SUPPLY_NOW)
 * ------------------------------------------------------ * 
 */
int getPumpState(void){
	return this.pumpState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水温情報を取得する
 * @param	: void
 * @return	: 水温(int)
 * ------------------------------------------------------ * 
 */
float getWaterTemperature(void){
	return this.waterTemperature;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ふたの状態を取得する
 * @param	: void
 * @sa		: ふたの状態はconstant.hに定義
 * @return	: ふたの状態(CLOSE, OPEN)
 * ------------------------------------------------------ * 
 */
int getLidState(void){
	return this.lidState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水位情報を取得する
 * @param	: void
 * @return	: 水位(0:空、1〜4:正常、5:満水)
 * ------------------------------------------------------ * 
 */
int getWaterLevel(void){
	return this.waterLevel;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 給湯ロックの状態を取得する
 * @param	: void
 * @sa		: 給湯ロックの状態はconstant.hに定義
 * @return	: 給湯ロックの状態(UNLOCK, LOCK)
 * ------------------------------------------------------ * 
 */
int getLockState(void){
	return this.lockState;
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマ残り時間を取得する
 * @param	: void
 * @sa		: 加熱状態はconstant.hに定義
 * @return	: キッチンタイマ残り時間(0〜KITCHEN_TIMER_MAX_TIME)
 * ------------------------------------------------------ * 
 */
int getRemainingTime(void){
	return this.remainingTime;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 目標温度を取得する
 * @param	: void
 * @sa		: 目標温度はconstant.hに定義
 * @return	: 目標温度(HIGH_TEMPERATURE_MODE, SAVING_MODE, MILK_MODE)
 * ------------------------------------------------------ * 
 */
float getTargetTemperature(void){
	return this.targetTemperature;
}
