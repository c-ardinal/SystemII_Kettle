/* 
 * ------------------------------------------------------ * 
 * @file	: KettleControl.c
 * @brief	: システムの処理の中枢を担う
 * ------------------------------------------------------ * 
 */
#include "KettleControl.h"


/* 
 * ------------------------------------------------------ * 
 * @function: システムの初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initSystem(void){
	//各処理の初期化関数呼び出し
	initTimer();
	initLcd();
	init7SegLed();
	initLed();
	initButton();
	initBuzzer();
	initSensor();
	initTempControl();
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
	offBuzzer();
	
	//内部値の初期化
	hasCannotHeatingError(getWaterTemperature(), 0);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 時間制約のないシステム処理を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void executeSystem(void){
	drawWaterLevel(getWaterLevel());
	drawTemperature((int)getWaterTemperature());
	drawKeepWarmMode((int)getTargetTemperature());
}


/* 
 * ------------------------------------------------------ * 
 * @function: 時間制約のあるシステム処理を行う(1周1[ms])
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
#pragma interrupt
void int_imia1(void){
	static int countMsec=0, countSec=0;		
	static int cannotHeatingErrorFlag=0, 
			   highTemperatureErrorFlag=0,
			   errorBuzzerCount=0;
	
	countMsec++;
	
	// 1msごとに7segの点灯を切り替え
	if(countMsec%2==0)
		drawLeftOf7SegLed(convertSecondToMinute(getRemainingTime()));
	else if(countMsec%2==1)
		drawRightOf7SegLed(convertSecondToMinute(getRemainingTime()));
	
	// 100ms経った時の処理
	if(countMsec%100==0){
	
		//ふたの状態更新
		checkLidState();
	
		//沸騰ボタン押下時処理 
		if(isPressed(BOIL_BUTTON)==PRESS_START){
			if(isHeatable()==TRUE 
				&& getHeatState()!=BOIL 
				&& cannotHeatingErrorFlag==FALSE 
				&& highTemperatureErrorFlag==FALSE){
				playBuzzer(20);
				setHeatState(BOIL);
			}
		}
		
		//キッチンタイマボタン押下時処理
		if(isPressed(TIMER_BUTTON)==PRESS_START){
			playBuzzer(20);
			setRemainingTime(kitchenTimerCountUp(getRemainingTime()));
		}
		
		//給湯ボタン押下時処理
		if(isPressed(SUPPLY_BUTTON)==PRESS_NOW){
			if(getLockState()==UNLOCK){
				setPumpState(SUPPLY_NOW);
				doPump();
			}
			else{
				setPumpState(SUPPLY_NO);
				stopPump();
			}
			if(WATER_LV_MIN<=getWaterLevel() 
				&& getWaterLevel()<=WATER_LV_MAX){
				onHeaterSource();
			}
		}
		else{
			setPumpState(SUPPLY_NO);
			stopPump();
		}
		
		//ロックボタン押下時処理
		if(isPressed(LOCK_BUTTON)==PRESS_START){
			if(getPumpState()==SUPPLY_NO){
				playBuzzer(20);
				if(getLockState()==UNLOCK)
					setLockState(LOCK);
				else
					setLockState(UNLOCK);
			}
		}
		
		//保温ボタン押下時処理
		if(isPressed(K_W_BUTTON)==PRESS_START){
			playBuzzer(20);
			setTargetTemperature(switchKeepWarmMode(getTargetTemperature()));
			if(isHeatable() 
				&& cannotHeatingErrorFlag==FALSE 
				&& highTemperatureErrorFlag==FALSE)
				setHeatState(BOIL);
		}
		
		//ふたの状態によって変化する処理
		static int pastLidState = CLOSE;
		if(isHeatable()==TRUE 
			&& pastLidState==OPEN 
			&& cannotHeatingErrorFlag==FALSE 
			&& highTemperatureErrorFlag==FALSE){
			setHeatState(BOIL);
			onHeaterSource();
		}
		pastLidState = getLidState();
		
		//ロック状態によって変化する処理
		if(getLockState() == LOCK)
			onLamp(LOCK_LAMP);
		else
			offLamp(LOCK_LAMP);
		
		//加熱状態によって変化する処理
		if(getHeatState() == BOIL){
			onLamp(BOIL_LAMP);
			offLamp(K_W_LAMP);
		}
		else if(getHeatState() == KEEP_WARM 
			|| getHeatState() == BOIL_END){
			offLamp(BOIL_LAMP);
			onLamp(K_W_LAMP);
		}
		else{
			offLamp(BOIL_LAMP);
			offLamp(K_W_LAMP);
		}
	}//..... 100ms経った時の処理ここまで .....
	
	
	// 1000ms経った時の処理
	if(countMsec>=1000){
		//水温更新
		checkWaterTemperature();
		//水位更新
		setWaterLevel(gainWaterLevel());
		//加熱処理
		if(getHeatState()==BOIL)
			doBoiling(getWaterTemperature());
		else if(getHeatState()==BOIL_END){
			doCooling();
			if(getWaterTemperature()<=getTargetTemperature()){
				onHeaterSource();
				setHeatState(KEEP_WARM);
			}
		}
		else if(getHeatState()==KEEP_WARM){
			doKeepWarm(getTargetTemperature(), getWaterTemperature());
		}
		//キッチンタイマカウントダウン処理
		setRemainingTime(kitchenTimerCountDown(getRemainingTime()));
		//カウントリセット
		countMsec = 0;
		countSec++;
		//エラー時のブザーカウントアップ
		if(cannotHeatingErrorFlag==TRUE 
			|| highTemperatureErrorFlag==TRUE)
			errorBuzzerCount++;
	}//..... 1000ms経った時の処理ここまで .....
		
	// 水位が低すぎるとき、もしくは満水だったとき
	if(getWaterLevel()<WATER_LV_MIN 
		|| WATER_LV_MAX<getWaterLevel()){
		setHeatState(NONE);
		offHeaterSource();
	}
	
	// 常に行う処理(高温エラーチェック)
	if(hasHighTemperatureError(getWaterTemperature())==TRUE)
		highTemperatureErrorFlag = TRUE;
		
	// 60秒ごとに処理(加熱不能エラー)
	if(countSec>=60
		&& getLidState()==CLOSE){
		if(getHeatState()==NONE
			|| getHeatState()==BOIL_END){
			cannotHeatingErrorFlag 
			= hasCannotHeatingError(getWaterTemperature(), getTargetTemperature());
		}
		countSec = 0;
	}
	
	// エラー発生時の処理
	if(cannotHeatingErrorFlag==TRUE 
		|| highTemperatureErrorFlag==TRUE){
		setHeatState(NONE);
		offHeaterSource();
		onBuzzer();
	}
	
	// エラー発生時のブザーが鳴って30秒経った後の処理
	if(errorBuzzerCount>=30){
		offBuzzer();
		errorBuzzerCount=0;
		cannotHeatingErrorFlag=FALSE;
		highTemperatureErrorFlag=FALSE;
		onHeaterSource();
		if(isHeatable()==TRUE)
			setHeatState(BOIL);
	}
	
	ITU1.TSR.BIT.IMFA = 0;			//フラグリセット
}
