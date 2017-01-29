/* 
 * ------------------------------------------------------ * 
 * @file	: KitchenTimerControl.c
 * @brief	: キッチンタイマ関連の処理
 * ------------------------------------------------------ * 
 */
#include "KitchenTimerControl.h"


static int kitchenTimerEnableFlag = 0,
		   kitchenTimerBuzzerCount = 0;


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマのカウントアップを行う
 * @param	: 現時点での残り時間
 * @return	: カウントアップした残り時間
 * ------------------------------------------------------ * 
 */
int kitchenTimerCountUp(int RemianingTime){
	int setTime = RemianingTime+60;
	if(setTime>KITCHEN_TIMER_MAX_TIME)
		setTime = KITCHEN_TIMER_MAX_TIME;
	kitchenTimerEnableFlag = 1;
	return setTime;
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマのカウントダウンを行う
 * @param	: 現時点での残り時間
 * @return	: カウントダウンした残り時間
 * ------------------------------------------------------ * 
 */
int kitchenTimerCountDown(int RemianingTime){
	int setTime = RemianingTime;
	if(kitchenTimerEnableFlag==1 
		&& RemianingTime>0){
		setTime = RemianingTime-1;
	}
	else if(kitchenTimerEnableFlag==1 
		&& getRemainingTime()<=0 
		&& kitchenTimerBuzzerCount<3){
		playBuzzer(100);
		kitchenTimerBuzzerCount++;
	}
	else{
		kitchenTimerBuzzerCount = 0;
		kitchenTimerEnableFlag = 0;
	}
	return setTime;
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマ残り秒数を7seg用に分単位に変換
 * @param	: 残り時間(秒)
 * @return	: 残り時間(分)
 * ------------------------------------------------------ * 
 */
int convertSecondToMinute(int RemainingTime){
	if(RemainingTime%60>0 
		&& RemainingTime/60<60)
		return RemainingTime/60+1;
	else
		return RemainingTime/60;
}
