#include "KettleControl.h"


/* システムの初期化 */
void initSystem(void){
	//各処理の初期化関数呼び出し
	timerInit();
	initLcd();
	init7SegLed();
	initLed();
}


/* システム実行 */
void executeSystem(void){
	// 演習4課題用の処理
	
	int i;
	static int count=99;
	
	/* LED点灯 */
	drawTemperature(count);					//LCDに水温表示
	drawKeepWarmMode(HIGH_TEMPERATURE_MODE);//LCDに保温モード(高温モード)を表示
	onLamp(BOIL_LAMP);						//沸騰ランプを点灯
	onLamp(K_W_LAMP);						//保温ランプを点灯
	onLamp(LOCK_LAMP);						//ロックランプを点灯
	drawWaterLevel(4);						//水位メーターを満水状態で表示
	for(i=0; i<1000; i++)
		drawKitchenTimer(count);			//キッチンタイマ残り時間表示[1msのウェイト代わり]
	if(count<=0)
		count = 99;
	else
		count--;
	
	/* LED消灯 */
	drawTemperature(count);					//LCDに水温表示
	drawKeepWarmMode(MILK_MODE);			//LCDに保温モード(ミルクモード)を表示
	offLamp(BOIL_LAMP);						//沸騰ランプを消灯
	offLamp(K_W_LAMP);						//保温ランプを消灯
	offLamp(LOCK_LAMP);						//ロックランプを消灯
	drawWaterLevel(0);						//水位メーターを枯渇状態で表示
	for(i=0; i<1000; i++)
		drawKitchenTimer(count);			//キッチンタイマ残り時間表示[1msのウェイト代わり]
	if(count<=0)
		count = 99;
	else
		count--;
}
