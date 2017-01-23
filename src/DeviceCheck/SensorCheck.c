/* 
 * ------------------------------------------------------ * 
 * @file	: SensorCheck.c
 * @brief	: 各センサーの状態のチェックを行う
 * ------------------------------------------------------ * 
 */
#include "SensorCheck.h"


/* 
 * ------------------------------------------------------ * 
 * @function: センサー類の初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initSensor(void){
	P8.DDR = 0x00;
	P9.DDR = 0x00;
	
	//AD変換用(動作モード:単一, 割り込み:許可, チャネルセレクト:AN0)
	AD.CSR.BYTE = 0x60;
}


/* 
 * ------------------------------------------------------ * 
 * @function: システムが加熱可能な状態にあるか判断する
 * @param	: void
 * @return	: 加熱可能ならTRUE、加熱不能ならFALSE
 * ------------------------------------------------------ * 
 */
int isHeatable(void){
	if(getLidState()==CLOSE 
		&& WATER_LV_MIN<=getWaterLevel() 
		&& getWaterLevel()<=WATER_LV_MAX)
		return TRUE;
	return FALSE;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水温のチェックを開始する
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void checkWaterTemperature(void){
	//AD変換開始
	AD.CSR.BIT.ADST = 1;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ふたの状態のチェックを行う(ふた状態の更新)
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void checkLidState(void){
	setLidState(!P9.DR.BIT.B4);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水位の取得を行う(水位情報の更新)
 * @param	: void
 * @return	: 0:空、1〜4:正常、5:満水
 * ------------------------------------------------------ * 
 */
int gainWaterLevel(void){
	int i;
	for(i=4; i>=0; i--)
		if((P8.DR.BYTE & (0x01 << i)) != 0)
			return i+1;
	return -1;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ふたが開閉された時に発動する割り込み処理
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
#pragma interrupt
void int_irq4(void){
	controlSource(OFF);
	setHeatState(NONE);
	if(INTC.ISR.BIT.IRQ4F==1)
		INTC.ISR.BIT.IRQ4F = 0;
}


/* 
 * ------------------------------------------------------ * 
 * @function: AD変換を用いて水温を更新する処理
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
#pragma interrupt
void int_adi(void){
	if(AD.CSR.BIT.ADF==1){
		AD.CSR.BIT.ADF = 0;
		setWaterTemperature(((float)(AD.DRA>>6))/1024.0*125.0);
		AD.CSR.BIT.ADST = 0;
	}
}
