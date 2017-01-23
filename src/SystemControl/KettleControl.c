#include "KettleControl.h"


KettleInfo kettleInfo;
UIControl uiControl;
Button button;
Buzzer buzzer;


/* システムの初期化 */
void initSystem(void){
    //オブジェクトの生成
    kettleInfo = newKettleInfo();
    uiControl = newUiControl();
    button = newButton();
	buzzer = newBuzzer();
    
	//各処理の初期化関数呼び出し
	initErrorCheck();
	initTimer();
	initKitchenTimer();
	uiControl.initLcd();
	uiControl.init7SegLed();
	uiControl.initLed();
	button.initButton();
	buzzer.initBuzzer();
	initSensor();
	initHeater();
	initPump();
	
	//初期値の設定
	checkWaterTemperature();
	checkLidState();
	kettleInfo.setHeatState(NONE);
	kettleInfo.setWaterLevel(gainWaterLevel());
	kettleInfo.setLockState(LOCK);
	kettleInfo.setRemainingTime(0);
	kettleInfo.setTargetTemperature(HIGH_TEMPERATURE_MODE);
	kettleInfo.setPumpState(SUPPLY_NO);	
	buzzer.offBuzzer();
}


/* システム実行 */
void executeSystem(void){
	uiControl.drawWaterLevel(kettleInfo.getWaterLevel());
	uiControl.drawTemperature((int)kettleInfo.getWaterTemperature());
	uiControl.drawKeepWarmMode((int)kettleInfo.getTargetTemperature());
}


/* 1msごとに発生するタイマ割り込み */
#pragma interrupt
void int_imia1(void){
	static int countMsec=0, countSec=0;		
	static int cannotHeatingErrorFlag=0, highTemperatureErrorFlag=0, errorBuzzerCount=0;
	
	countMsec++;
	
	// 1msごとに7segの点灯を切り替え
	if(countMsec%2==0)
		uiControl.drawLeftOf7SegLed(convertSecondToMinute());
	else if(countMsec%2==1)
		uiControl.drawRightOf7SegLed(convertSecondToMinute());
	
	// 100ms経った時の処理
	if(countMsec%100==0){
	
		//ふたの状態更新
		checkLidState();
	
		//沸騰ボタン押下時処理 
		if(button.isPressed(BOIL_BUTTON)==PRESS_START){
			if(isHeatable()==TRUE 
			    && kettleInfo.getHeatState()!=BOIL 
			    && cannotHeatingErrorFlag==FALSE 
				&& highTemperatureErrorFlag==FALSE){
				buzzer.playBuzzer(20);
				kettleInfo.setHeatState(BOIL);
		}
		}
		
		//キッチンタイマボタン押下時処理
		if(button.isPressed(TIMER_BUTTON)==PRESS_START){
			buzzer.playBuzzer(20);
			kitchenTimerCountUp();
		}
		
		//給湯ボタン押下時処理
		if(button.isPressed(SUPPLY_BUTTON)==PRESS_NOW){
			if(kettleInfo.getLockState()==UNLOCK)
				doPump();
			else
				stopPump();
		}
		else
			stopPump();
		
		//ロックボタン押下時処理
		if(button.isPressed(LOCK_BUTTON)==PRESS_START){
			if(kettleInfo.getPumpState()==SUPPLY_NO){
				buzzer.playBuzzer(20);
				if(kettleInfo.getLockState()==UNLOCK)
					kettleInfo.setLockState(LOCK);
				else
					kettleInfo.setLockState(UNLOCK);
			}
		}
		
		//保温ボタン押下時処理
		if(button.isPressed(K_W_BUTTON)==PRESS_START){
			buzzer.playBuzzer(20);
			switchKeepWarmMode();
			if(isHeatable() 
			    && cannotHeatingErrorFlag==FALSE 
				&& highTemperatureErrorFlag==FALSE)
				kettleInfo.setHeatState(BOIL);
		}
		
		//ふたの状態によって変化する処理
		static int pastLidState = CLOSE;
		if(isHeatable()==TRUE 
		    && pastLidState==OPEN 
		    && cannotHeatingErrorFlag==FALSE 
		    && highTemperatureErrorFlag==FALSE){
			kettleInfo.setHeatState(BOIL);
			controlSource(ON);
		}
		pastLidState = kettleInfo.getLidState();
		
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
		else if(getHeatState() == KEEP_WARM){
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
		kettleInfo.setWaterLevel(gainWaterLevel());
		//加熱処理
		if(kettleInfo.getHeatState()==BOIL)
			doBoiling();
		else if(kettleInfo.getHeatState()==KEEP_WARM)
			doKeepWarm();
		//キッチンタイマカウントダウン処理
		kitchenTimerCountDown();
		countMsec = 0;
		countSec++;
		if(cannotHeatingErrorFlag==TRUE || highTemperatureErrorFlag==TRUE)
			errorBuzzerCount++;
	}//..... 1000ms経った時の処理ここまで .....
		
	// 水位が低すぎるとき、もしくは満水だったとき
	if(kettleInfo.getWaterLevel()<WATER_LV_MIN
	    || WATER_LV_MAX<kettleInfo.getWaterLevel()){
		kettleInfo.setHeatState(NONE);
		controlSource(OFF);
	}
	
	// 常に行う処理(高温エラーチェック)
	if(hasHighTemperatureError()==TRUE)
		highTemperatureErrorFlag = TRUE;
		
	// 60秒ごとに処理(加熱不能エラー)
	if(countSec>=60){
		if(hasCannotHeatingError()==TRUE)
			cannotHeatingErrorFlag = TRUE;
		countSec = 0;
	}
	
	// エラー発生時の処理
	if(cannotHeatingErrorFlag==1 
	    || highTemperatureErrorFlag==1){
		kettleInfo.setHeatState(NONE);
		controlSource(OFF);
		buzzer.onBuzzer();
	}
	
	// エラー発生時のブザー処理
	if(errorBuzzerCount>=30){
		buzzer.offBuzzer();
		errorBuzzerCount=0;
		cannotHeatingErrorFlag=0;
		highTemperatureErrorFlag=0;
	}
	
	ITU1.TSR.BIT.IMFA = 0;			//フラグリセット
}
