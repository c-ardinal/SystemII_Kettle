/* 
 * ------------------------------------------------------ * 
 * @file	: Bzzer.c
 * @brief	: ブザーの制御を行う
 * ------------------------------------------------------ * 
 */
#include "Buzzer.h"


 /* 
 * ------------------------------------------------------ * 
 * @function: ブザーの初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initBuzzer(void){
	P6.DDR = 0x70;
}


 /* 
 * ------------------------------------------------------ * 
 * @function: ブザーを指定時間鳴動させる
 * @param	: 鳴動時間(msec)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void playBuzzer(int playSeconds){
	int i, remainingTime = 0;
	P6.DR.BIT.B4 = 1;
	P6.DR.BIT.B5 = 1;
	for(i=0; i<playSeconds; i++){
		if(getRemainingTime()%60>0 
			&& getRemainingTime()/60<60)
			remainingTime = getRemainingTime()/60+1;
		else
			remainingTime = getRemainingTime()/60;
			
		if(i%2==0)
			drawLeftOf7SegLed(remainingTime);
		else if(i%2==1)
			drawRightOf7SegLed(remainingTime);
		timer1ms(1);
	}
	P6.DR.BIT.B5 = 0;
	P6.DR.BIT.B4 = 0;
}


 /* 
 * ------------------------------------------------------ * 
 * @function: ブザーを常にならす
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void onBuzzer(void){
	P6.DR.BYTE = (P6.DR.BYTE & 0xcf) | 0x3f;
}


 /* 
 * ------------------------------------------------------ * 
 * @function: ブザーを停止する
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void offBuzzer(void){
	P6.DR.BYTE &= 0xcf;
}
