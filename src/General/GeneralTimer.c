#include "GeneralTimer.h"


/* タイマ初期化*/
void timerInit(void){
	//IMFAフラグをリセット
	ITU0.TSR.BIT.IMFA = 0;
	//カウンタ動作停止
	ITU.TSTR.BIT.STR0 = 0;
	//GRAコンペアマッチ/インプットキャプチャでTCNTクリア、立ち上がりでカウント、8分周
	ITU0.TCR.BYTE = 0x23;
	//GRA出力禁止
	ITU0.TIOR.BYTE = 0x00;
	//0.5[us] * 20 = 10[us]
	ITU0.GRA = 20;
}


/* 250nsタイマ */
void timer250ns(void){
	asm volatile(
		"nop\n\t"						//この1命令だけで125nsウェイト
		"nop"
	);
}


/* 10usタイマ */
void timer10us(int sec){
	int i;
	ITU.TSTR.BIT.STR0 = 1;				//カウンタ動作開始
	for(i=0; i<=sec; i++){
		while(ITU0.TSR.BIT.IMFA == 0);	//フラグ立ち上がり待機
		ITU0.TSR.BIT.IMFA = 0;			//フラグリセット
	}
	ITU.TSTR.BIT.STR0 = 0;				//カウンタ動作停止
}


/* 1msタイマ */
void timer1ms(int sec){
	int i;
	for(i=0; i<=sec; i++)
		timer10us(100);
}
