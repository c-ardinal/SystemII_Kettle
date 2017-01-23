#include "KitchenTimerControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../UIManager/Buzzer.h"


static int kitchenTimerEnableFlag = 0,
		   kitchenTimerBuzzerCount = 0;
KettleInfo kettleInfo;


void initKitchenTimer(void){
    kettleInfo = newKettleInfo();
}


/* キッチンタイマカウントアップ処理 */
void kitchenTimerCountUp(void){
	int setTime = kettleInfo.getRemainingTime()+60;
	if(setTime>KITCHEN_TIMER_MAX_TIME)
		setTime = KITCHEN_TIMER_MAX_TIME;
	kettleInfo.setRemainingTime(setTime);
	kitchenTimerEnableFlag = 1;
}

/* キッチンタイマカウントダウン処理 */
void kitchenTimerCountDown(void){
	if(kitchenTimerEnableFlag==1 
	    && kettleInfo.getRemainingTime()>0){
        kettleInfo.setRemainingTime(kettleInfo.getRemainingTime()-1);
	}
	else if(kitchenTimerEnableFlag==1 
	    && kettleInfo.getRemainingTime()<=0 
	    && kitchenTimerBuzzerCount<3){
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
	if(kettleInfo.getRemainingTime()%60>0 
	    && kettleInfo.getRemainingTime()/60<60)
		return kettleInfo.getRemainingTime()/60+1;
	else
		return kettleInfo.getRemainingTime()/60;
}
