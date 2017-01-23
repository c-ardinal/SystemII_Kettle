#include "SensorCheck.h"
#include "../UIManager/UIControl.h"
#include "../InfoManager/KettleInfo.h"
#include "../DeviceControl/HeaterControl.h"


KettleInfo kettleInfo;


/* センサー初期化関数 */
void initSensor(void){
	P8.DDR = 0x00;
	P9.DDR = 0x00;
	
	//AD変換用(動作モード:単一, 割り込み:許可, チャネルセレクト:AN0)
	AD.CSR.BYTE = 0x60;
	
	kettleInfo = newKettleInfo();
}


/* 加熱可能か判断する関数 */
int isHeatable(void){
	if(kettleInfo.getLidState()==CLOSE 
	    && WATER_LV_MIN<=kettleInfo.getWaterLevel() 
	    && kettleInfo.getWaterLevel()<=WATER_LV_MAX)
		return TRUE;
	return FALSE;
}


/* 水温チェック関数 */
void checkWaterTemperature(void){
	//AD変換開始
	AD.CSR.BIT.ADST = 1;
}


/* ふたの状態チェック関数 */
void checkLidState(void){
	kettleInfo.setLidState(!P9.DR.BIT.B4);
}


/* 水位チェック関数 */
int gainWaterLevel(void){
	int i;
	for(i=4; i>=0; i--)
		if((P8.DR.BYTE & (0x01 << i)) != 0)
			return i+1;
	return -1;
}


/* 外部割り込みを用いたふたの状態チェック関数 */
#pragma interrupt
void int_irq4(void){
	controlSource(OFF);
	kettleInfo.setHeatState(NONE);
	if(INTC.ISR.BIT.IRQ4F==1)
		INTC.ISR.BIT.IRQ4F = 0;
}


/* AD変換を用いたサーミスタの状態チェック関数 */
#pragma interrupt
void int_adi(void){
	if(AD.CSR.BIT.ADF==1){
		AD.CSR.BIT.ADF = 0;
		kettleInfo.setWaterTemperature(((float)(AD.DRA>>6))/1024.0*125.0);
		AD.CSR.BIT.ADST = 0;
	}
}
