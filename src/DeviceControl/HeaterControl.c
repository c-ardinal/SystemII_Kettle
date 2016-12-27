#include "HeaterControl.h"


/* ヒーター初期化 */
void initHeater(void){
	P6.DDR = 0x70;
	DA.DR0 = 0x00;
	DA.CR.BIT.DAOE0 = 1;
	controlSource(ON);
}


/* ヒーター操作 */
void setHeaterPower(int power){
	DA.DR0 = (power*2000)/256;
}


/* ヒーター電源操作 */
void controlSource(int state){
	P6.DR.BIT.B6 = state;
}
