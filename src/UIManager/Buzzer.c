#include "Buzzer.h"
#include "../General/Timer.h"
#include "../UIManager/UIControl.h"
#include "../InfoManager/KettleInfo.h"

void initBuzzer(void){
	P6.DDR = 0x70;
}


void playBuzzer(int playSeconds){
	int i;
	P6.DR.BIT.B4 = 1;
	P6.DR.BIT.B5 = 1;
	for(i=0; i<playSeconds; i++){
		if(i%2==0)
			drawLeftOf7SegLed(getRemainingTime());
		else if(i%2==1)
			drawRightOf7SegLed(getRemainingTime());
		timer1ms(1);
	}
	P6.DR.BIT.B5 = 0;
	P6.DR.BIT.B4 = 0;
}
