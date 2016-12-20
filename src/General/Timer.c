#include "Timer.h"


/* タイマ初期化*/
void initTimer(void){
	/* ウェイト用のタイマ初期化 */
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
	
	/* 外部割り込み初期化 */
	//IRQ4のレベルセンス/立ち下がりの選択
	INTC.ISCR.BIT.IRQ4SC = 1;
	//IRQ4の割り込みを許可
	INTC.IER.BIT.IRQ4E = 1;
	//フラグリセット
	INTC.ISR.BIT.IRQ4F = 1;
	
	/* タイマ割り込み初期化 */
	//IMFAフラグをリセット
	ITU1.TSR.BIT.IMFA = 0;
	//カウンタ動作停止
	ITU.TSTR.BIT.STR1 = 0;
	//GRAコンペアマッチ/インプットキャプチャでTCNTクリア、立ち上がりでカウント、8分周
	ITU1.TCR.BYTE = 0x23;
	//GRA出力禁止
	ITU1.TIOR.BYTE = 0x00;
	//0.5[us] * 2000 = 1[ms]
	ITU1.GRA = 2000;
	//ITU0のIMFAフラグによる割り込みを許可
	ITU1.TIER.BIT.IMIEA = 1;
	//カウンタ動作開始
	ITU.TSTR.BIT.STR1 = 1;
	
	//全割り込み許可
	STI();
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
