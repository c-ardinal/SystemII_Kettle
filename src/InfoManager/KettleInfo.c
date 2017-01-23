#include "KettleInfo.h"


KettleInfo kettleInfo = {
	setHeatState, setPumpState, setWaterTemperature, setLidState,
	setWaterLevel, setLockState, setRemainingTime, setTargetTemperature,
	getHeatState, getPumpState, getWaterTemperature, getLidState,
	getWaterLevel, getLockState, getRemainingTime, getTargetTemperature
};


/* 情報保存用構造体 */
static info_t this = {0, 0, 0.0, 0, 0, 0, 0, 0.0};


/* 加熱状態保存関数 */
void setHeatState(int heatState){
	this.heatState = heatState;
}


/* ポンプ状態保存関数 */
void setPumpState(int pumpState){
	this.pumpState = pumpState;
}


/* 水温保存関数 */
void setWaterTemperature(float waterTemperature){
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
void setTargetTemperature(float targetTemperature){
	this.targetTemperature = targetTemperature;
}


/* 加熱状態確認関数 */
int getHeatState(void){
	return this.heatState;
}


/* ポンプ状態確認関数 */
int getPumpState(void){
	return this.pumpState;
}


/* 水温確認関数 */
float getWaterTemperature(void){
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
float getTargetTemperature(void){
	return this.targetTemperature;
}
