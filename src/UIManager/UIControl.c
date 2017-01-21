#include "UIControl.h"
#include "../General/Timer.h"


/* LCD初期化 */
void initLcd(void){
	//ポート3の初期化
	P3.DDR = 0xff;
	P3.DR.BYTE = 0x00;
	timer1ms(15);
	//ファンクション設定：データ幅8bit, 1行表示, 5*8dot
	write8bitLcd(0x03, CONTROL);
	timer10us(410);
	//ファンクション設定：データ幅8bit, 1行表示, 5*8dot
	write8bitLcd(0x03, CONTROL);
	timer10us(10);
	//ファンクション設定：データ幅8bit, 1行表示, 5*8dot
	write8bitLcd(0x03, CONTROL);
	timer10us(4);
	//ファンクション設定：データ幅4bit, 1行表示, 5*8dot
	write8bitLcd(0x02, CONTROL);
	timer10us(4);
	//ファンクション設定：データ幅4bit, 2行表示, 5*8dot
	write4bitLcd(0x28, CONTROL);
	//ディスプレイ設定：表示ON, カーソルOFF, 点滅OFF
	write4bitLcd(0x0c, CONTROL);
	//表示消去：
	write4bitLcd(0x01, CONTROL);
	//エントリーモードセット：読み書き後カーソル右シフト, 表示シフトOFF
	write4bitLcd(0x06, CONTROL);
}


/* LCD8bit書き込み */
void write8bitLcd(int writeData, int selectRegister){
	P3.DR.BIT.B4 = selectRegister;	//任意のレジスタ設定
	P3.DR.BIT.B6 = WRITE;			//Writeモード
	P3.DR.BYTE = (P3.DR.BYTE & 0xf0) | writeData;
	P3.DR.BIT.B5 = ON;				//Enable信号ON
	timer250ns();
	P3.DR.BIT.B5 = OFF;				//Enable信号OFF
	timer250ns();
}


/* LCD4bit書き込み */
void write4bitLcd(int writeData, int selectRegister){
	write8bitLcd((writeData >> 4 & 0x0f), selectRegister);
	write8bitLcd((writeData & 0x0f), selectRegister);
	waitLcd();
}


/* busyフラグの読み出し */
int readBusyFlag(void){
	int result = 0;
	P3.DDR = 0x70;					//上位3bit出力、下位4bit入力
	P3.DR.BIT.B4 = CONTROL;			//制御用レジスタを選択
	P3.DR.BIT.B6 = READ;			//Readモード
	P3.DR.BIT.B5 = ON;				//Enable信号ON
	timer250ns();
	result = P3.DR.BIT.B3;			//DB7 or DB3を読み出し
	P3.DR.BIT.B5 = OFF;				//Enable信号OFF
	timer250ns();
	P3.DDR = 0x7f;					//全bit出力に
	return result;
}


/* busyフラグによるウェイト */
void waitLcd(void){
	while(readBusyFlag() != 0)		//上位読み出し
		readBusyFlag();				//下位は破棄
}


/* 文字列表示 */
void drawStringToLcd(char *str, int point){
	write4bitLcd((0x80+(0x40*point)), CONTROL);
	while(*str)
		write4bitLcd(*str++, DATA);
}


void draw3NumToLcd(int num, int point){
	int numSplit[3] = {0, 0, 0};
	numSplit[0] = num/100;
	numSplit[1] = (num-(numSplit[0]*100))/10;
	numSplit[2] = num-(numSplit[0]*100)-(numSplit[1]*10);
	write4bitLcd((0x80+(0x40*point)), CONTROL);
	//100の位表示
	write4bitLcd(0x30+numSplit[0], DATA);
	//10の位表示
	write4bitLcd(0x30+numSplit[1], DATA);
	//1の位表示
	write4bitLcd(0x30+numSplit[2], DATA);
}

void drawNumToLcd(int num, int point){
	#define arrSize 6
	int numSplit[arrSize] = {0, 0, 0, 0, 0, 0};
	int i = 0;
	// ここの処理が冗長的なので抽象化する予定 ========================================
	numSplit[0] = num/100000;
	numSplit[1] = (num-(numSplit[0]*100000))/10000;
	numSplit[2] = (num-(numSplit[0]*100000)-(numSplit[1]*10000))/1000;
	numSplit[3] = (num-(numSplit[0]*100000)-(numSplit[1]*10000)-(numSplit[2]*1000))/100;
	numSplit[4] = (num-(numSplit[0]*100000)-(numSplit[1]*10000)-(numSplit[2]*1000)-(numSplit[3]*100))/10;
	numSplit[5] = (num-(numSplit[0]*100000)-(numSplit[1]*10000)-(numSplit[2]*1000)-(numSplit[3]*100)-(numSplit[4]*10));
	//=============================================================================
	write4bitLcd((0x80+(0x40*point)), CONTROL);
	for(i=0; i<arrSize; i++)
		write4bitLcd(0x30+numSplit[i], DATA);
}


/* 水温表示 */
void drawTemperature(int temperature){
	//桁ごとに分割{100の位, 10の位, 1の位}
	int temperatureSplit[3] = {0, 0, 0};
	temperatureSplit[0] = temperature/100;
	temperatureSplit[1] = (temperature-(temperatureSplit[0]*100))/10;
	temperatureSplit[2] = temperature-(temperatureSplit[0]*100)-(temperatureSplit[1]*10);
	//文字列表示
	drawStringToLcd("Temperature: ", 0);
	//100の位表示
	if(temperature<=99)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+temperatureSplit[0], DATA);
	//10の位表示
	if(temperature<=9)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+temperatureSplit[1], DATA);
	//1の位表示
	write4bitLcd(0x30+temperatureSplit[2], DATA);
}


/* 保温モード表示 */
void drawKeepWarmMode(int modeId){
	//文字列表示
	drawStringToLcd(" KeepMode  :  ", 1);
	//10の位表示
	if((modeId/10)==0)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd((0x30+(modeId/10)), DATA);
	//1の位表示
	write4bitLcd((0x30+(modeId-(modeId/10)*10)), DATA);
}


/* 7セグメントLED初期化 */
void init7SegLed(void){
	PA.DDR = 0xff;
	PA.DR.BYTE = 0x00;
}


/* キッチンタイマー表示 */
void draw7SegLed(int remainingTime){
	//10の位表示(リセット|書き込み|左点灯右消灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (remainingTime/10) | 0x20;
	timer10us(50);
	//1の位表示(リセット|書き込み|左消灯右点灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (remainingTime - ((remainingTime/10)*10)) | 0x10;
	timer10us(50);
}


/* キッチンタイマー10の位表示表示 */
void drawLeftOf7SegLed(int remainingTime){
	//(リセット|書き込み|左点灯右消灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (remainingTime/10) | 0x20;
}

/* キッチンタイマー1の位表示表示 */
void drawRightOf7SegLed(int remainingTime){
	//(リセット|書き込み|左消灯右点灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (remainingTime - ((remainingTime/10)*10)) | 0x10;
}



/* LED初期化 */
void initLed(void){
	PB.DDR = 0xff;
	PB.DR.BYTE = 0x00;
}


/* 水位ゲージ表示 */
void drawWaterLevel(int waterLevel){
	if(waterLevel==4)
		PB.DR.BYTE = (PB.DR.BYTE & 0xf0) | 0x0f;
	else if(waterLevel==3)
		PB.DR.BYTE = (PB.DR.BYTE & 0xf0) | 0x07;
	else if(waterLevel==2)
		PB.DR.BYTE = (PB.DR.BYTE & 0xf0) | 0x03;
	else if(waterLevel==1)
		PB.DR.BYTE = (PB.DR.BYTE & 0xf0) | 0x01;
	else if(waterLevel<=0 || waterLevel>=5)
		PB.DR.BYTE &= 0xf0;
	
}


/* LED点灯 */
void onLamp(LampId_t lampId){
	switch(lampId){
		case BOIL_LAMP:
			PB.DR.BIT.B4 = 1;
		break;
		case K_W_LAMP:
			PB.DR.BIT.B5 = 1;
		break;
		case LOCK_LAMP:
			PB.DR.BIT.B6 = 1;
		break;
		default:
		break;
	}
}


/* LED消灯 */
void offLamp(LampId_t lampId){
	switch(lampId){
		case BOIL_LAMP:
			PB.DR.BIT.B4 = 0;
		break;
		case K_W_LAMP:
			PB.DR.BIT.B5 = 0;
		break;
		case LOCK_LAMP:
			PB.DR.BIT.B6 = 0;
		break;
		default:
		break;
	}
}


/* LED反転 */
void revLamp(LampId_t LampId){
switch(LampId){
		case BOIL_LAMP:
			PB.DR.BIT.B4 = ~PB.DR.BIT.B4;
		break;
		case K_W_LAMP:
			PB.DR.BIT.B5 = ~PB.DR.BIT.B5;
		break;
		case LOCK_LAMP:
			PB.DR.BIT.B6 = ~PB.DR.BIT.B6;
		break;
		default:
		break;
	}
}
