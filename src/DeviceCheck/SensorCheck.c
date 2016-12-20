#include "SensorCheck.h"
#include "../UIManager/UIControl.h"


/* センサー初期化関数 */
void initSensor(void){
	P8.DDR = 0x00;
	P9.DDR = 0x00;
}


/* 水温チェック関数 */
int checkWaterTemperature(void){
	return 0;
}


/* ふたの状態チェック関数 */
int checkLidState(void){
	return P9.DR.BIT.B4;
}


/* 水位チェック関数 */
int checkWaterLevel(void){
	int i;
	for(i=4; i>=0; i--)
		if((P8.DR.BYTE & (0x01 << i)) != 0)
			return i+1;
	return 0;
}


/* 外部割り込みを用いたふたの状態チェック関数 */
#pragma interrupt
void int_irq4(void){
	onLamp(LOCK_LAMP);
	if(INTC.ISR.BIT.IRQ4F==1)
		INTC.ISR.BIT.IRQ4F = 0;
}
