/* 
 * ------------------------------------------------------ * 
 * @file	: KitchenTimerControl.c
 * @brief	: キッチンタイマ関連の処理
 * ------------------------------------------------------ * 
 */
#include "KitchenTimerControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../UIManager/Buzzer.h"


static int kitchenTimerEnableFlag = 0,
		   kitchenTimerBuzzerCount = 0;


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマのカウントアップを行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void kitchenTimerCountUp(void){
	int setTime = getRemainingTime()+60;
	if(setTime>KITCHEN_TIMER_MAX_TIME)
		setTime = KITCHEN_TIMER_MAX_TIME;
	setRemainingTime(setTime);
	kitchenTimerEnableFlag = 1;
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマのカウントダウンを行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void kitchenTimerCountDown(void){
	if(kitchenTimerEnableFlag==1 && getRemainingTime()>0){
			setRemainingTime(getRemainingTime()-1);
	}
	else if(kitchenTimerEnableFlag==1 && getRemainingTime()<=0 && kitchenTimerBuzzerCount<3){
		playBuzzer(100);
		kitchenTimerBuzzerCount++;
	}
	else{
		kitchenTimerBuzzerCount = 0;
		kitchenTimerEnableFlag = 0;
	}
}


/* 
 * ------------------------------------------------------ * 
 * @function: キッチンタイマ残り秒数を7seg用に分単位に変換
 * @param	: void
 * @return	: キッチンタイマ残り時間(分、int)
 * ------------------------------------------------------ * 
 */
int convertSecondToMinute(void){
	if(getRemainingTime()%60>0 && getRemainingTime()/60<60)
		return getRemainingTime()/60+1;
	else
		return getRemainingTime()/60;
}
