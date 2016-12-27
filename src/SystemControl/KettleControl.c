#include "KettleControl.h"


/* システムの初期化 */
void initSystem(void){
	//各処理の初期化関数呼び出し
	initTimer();
	initLcd();
	init7SegLed();
	initLed();
	initButton();
	initBuzzer();
	initSensor();
	initHeater();
	initPump();
	
	//初期値の設定
	checkWaterTemperature();
	checkLidState();
	setHeatState(NONE);
	setWaterLevel(gainWaterLevel());
	setLockState(LOCK);
	setRemainingTime(0);
	setTargetTemperature(HIGH_TEMPERATURE_MODE);
	setPumpState(SUPPLY_NO);	
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
	static int count=0, heaterPower=0;;
	count++;
	
	// 1msごとに7segの点灯を切り替え
	if(count%2==0)
		drawLeftOf7SegLed(getRemainingTime());
	else if(count%2==1)
		drawRightOf7SegLed(getRemainingTime());
	
	// 100ms経った時の処理
	if(count%100==0){
	
		//ふたの状態更新
		checkLidState();
	
		//沸騰ボタン押下時処理 
		if(isPressed(BOIL_BUTTON)==PRESS_START){
			if(getLidState()==CLOSE && getHeatState()!=BOIL){
				playBuzzer(20);
				onLamp(BOIL_LAMP);
				controlSource(ON);
				heaterPower = 255;
				setHeatState(BOIL);
			}
		}
		
		//キッチンタイマボタン押下時処理
		if(isPressed(TIMER_BUTTON)==PRESS_START){
			playBuzzer(20);
			setRemainingTime(getRemainingTime()+1);
		}
		
		//給湯ボタン押下時処理
		if(isPressed(SUPPLY_BUTTON)==PRESS_NOW){
			if(getLockState()==UNLOCK)
				doPump();
			else
				stopPump();
		}
		else
			stopPump();
		
		//ロックボタン押下時処理
		if(isPressed(LOCK_BUTTON)==PRESS_START){
			if(getPumpState()==SUPPLY_NO){
				playBuzzer(20);
				if(getLockState()==UNLOCK){
					setLockState(LOCK);
				}
				else{
					setLockState(UNLOCK);
				}
			}
		}
		
		//保温ボタン押下時処理
		if(isPressed(K_W_BUTTON)==PRESS_START){
			playBuzzer(20);
			switch(getTargetTemperature()){
				case HIGH_TEMPERATURE_MODE:
					setTargetTemperature(SAVING_MODE);
				break;
				case SAVING_MODE:
					setTargetTemperature(MILK_MODE);
				break;
				case MILK_MODE:
					setTargetTemperature(HIGH_TEMPERATURE_MODE);
				break;
			}
		}
		
		//ふたの状態によって変化する処理
		if(getLidState()==OPEN)
			controlSource(OFF);
			
		//ロック状態によって変化する処理
		if(getLockState() == LOCK)
			onLamp(LOCK_LAMP);
		else
			offLamp(LOCK_LAMP);
		
		//加熱状態によって変化する処理
		if(getHeatState() == NONE){
			offLamp(BOIL_LAMP);
			offLamp(K_W_LAMP);
		}
		else if(getHeatState() == BOIL){
			onLamp(BOIL_LAMP);
			offLamp(K_W_LAMP);
		}
		else if(getHeatState() == KEEP_WARM){
			offLamp(BOIL_LAMP);
			onLamp(K_W_LAMP);
		}
	}
	
	// 1000ms経った時の処理
	if(count%1000==0){
		setHeaterPower(heaterPower);
		checkWaterTemperature();
		setWaterLevel(gainWaterLevel());
	}
	
	// 1000ms以上経った時の処理
	if(count>1000)
		count = 0;
	
	ITU1.TSR.BIT.IMFA = 0;			//フラグリセット
}
