#include "KettleControl.h"


/* システムの初期化 */
void initSystem(void){
	//各処理の初期化関数呼び出し
	initTimer();
	initLcd();
	init7SegLed();
	initLed();
	initButton();
	initSensor();
	
	//初期値の設定
	setWaterTemperature(checkWaterTemperature());
	setLidState(checkLidState());
	setWaterLevel(checkWaterLevel());
	setLockState(0);
	setRemainingTime(0);
	setTargetTemperature(HIGH_TEMPERATURE_MODE);
	
}


/* システム実行 */
void executeSystem(void){
	drawWaterLevel(getWaterLevel());
	drawTemperature(getWaterTemperature());
	drawKeepWarmMode(getTargetTemperature());
}


/* 1msごとに発生するタイマ割り込み */
#pragma interrupt
void int_imia1(void){
	static int count=0;
	count++;
	
	// 1msごとに7segの点灯を切り替え
	if(count%2==0)
		drawLeftOf7SegLed(getRemainingTime());
	else if(count%2==1)
		drawRightOf7SegLed(getRemainingTime());
	
	// 100ms経った時の処理
	if(count%100){
		if(isState(BOIL_BUTTON)==1)
			setRemainingTime(40);
		
		if(isState(TIMER_BUTTON)==1)
			setRemainingTime(20);
			
		if(isState(SUPPLY_BUTTON)==1)
			setRemainingTime(80);
		
		if(isState(LOCK_BUTTON)==1)
			setRemainingTime(60);
		
		if(isState(K_W_BUTTON)==1)
			setRemainingTime(0);
			
		if(checkLidState()==1)
			offLamp(LOCK_LAMP);
	}
	
	// 1000ms経った時の処理
	if(count%1000){
		setWaterLevel(checkWaterLevel());
	}
	
	// 1000ms以上経った時の処理
	if(count>1000)
		count = 0;
	
	ITU1.TSR.BIT.IMFA = 0;			//フラグリセット
}
