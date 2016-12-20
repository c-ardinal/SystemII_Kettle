#include "KettleInfo.h"


/* 情報保存用構造体 */
static info_t this = {0, 0, 0, 0, 0, 0};


/* 水温保存関数 */
void setWaterTemperature(int waterTemperature){
	this.waterTemperature = waterTemperature;
}


/* ふたの状態保存関数 */
void setLidState(int lidState){
	this.lidState = lidState;
}


/* 水位保存関数 */
void setWaterLevel(int waterLevel){
	this.waterLevel = waterLevel;
}


/* 給湯ロック状態保存関数 */
void setLockState(int lockState){
	this.lockState = lockState;
}


/* キッチンタイマ残り時間保存関数 */
void setRemainingTime(int remainigTime){
	this.remainingTime = remainigTime;
}


/* 目標温度保存関数 */
void setTargetTemperature(int targetTemperature){
	this.targetTemperature = targetTemperature;
}


/* 水温確認関数 */
int getWaterTemperature(void){
	return this.waterTemperature;
}


/* ふたの状態確認関数 */
int getLidState(void){
	return this.lidState;
}


/* 水位確認関数 */
int getWaterLevel(void){
	return this.waterLevel;
}


/* 給湯ロック状態確認関数 */
int getLockState(void){
	return this.lockState;
}


/* キッチンタイマ残り時間確認関数 */
int getRemainingTime(void){
	return this.remainingTime;
}


/* 目標温度確認関数 */
int getTargetTemperature(void){
	return this.targetTemperature;
}


