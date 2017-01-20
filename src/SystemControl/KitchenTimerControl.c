#include "KitchenTimerControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../UIManager/Buzzer.h"

static int kitchenTimerEnableFlag = 0,
		   kitchenTimerBuzzerCount = 0;


/* キッチンタイマカウントアップ処理 */
void kitchenTimerCountUp(void){
	int setTime = getRemainingTime()+60;
	if(setTime>KITCHEN_TIMER_MAX_TIME)
		setTime = KITCHEN_TIMER_MAX_TIME;
	setRemainingTime(setTime);
	kitchenTimerEnableFlag = 1;
}

/* キッチンタイマカウントダウン処理 */
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


/* キッチンタイマ残り秒数を分に変換する関数 */
int convertSecondToMinute(void){
	if(getRemainingTime()%60>0 && getRemainingTime()/60<60)
		return getRemainingTime()/60+1;
	else
		return getRemainingTime()/60;
}
