#include "Buzzer.h"
#include "../General/Timer.h"
#include "../UIManager/UIControl.h"
#include "../InfoManager/KettleInfo.h"

void initBuzzer(void){
	P6.DDR = 0x70;
}


void playBuzzer(int playSeconds){
	int i, remainingTime = 0;
	P6.DR.BIT.B4 = 1;
	P6.DR.BIT.B5 = 1;
	for(i=0; i<playSeconds; i++){
		if(getRemainingTime()%60>0 && getRemainingTime()/60<60)
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


void onBuzzer(){
	P6.DR.BYTE = (P6.DR.BYTE & 0xcf) | 0x3f;
}


void offBuzzer(){
	P6.DR.BYTE &= 0xcf;
}
