#include "UIControl.h"


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
	waitLcd();
	//ディスプレイ設定：表示ON, カーソルOFF, 点滅OFF
	write4bitLcd(0x0c, CONTROL);
	waitLcd();
	//表示消去：
	write4bitLcd(0x01, CONTROL);
	waitLcd();
	//エントリーモードセット：読み書き後カーソル右シフト, 表示シフトOFF
	write4bitLcd(0x06, CONTROL);
	waitLcd();
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
	waitLcd();
	while(*str){
		write4bitLcd(*str++, DATA);
		waitLcd();
	}
}


/* 水温表示 */
void drawTemperature(int Temperature){
	//桁ごとに分割
	int TemperatureSplit[3] = {0, 0, 0};
	TemperatureSplit[0] = Temperature/100;
	TemperatureSplit[1] = (Temperature-(TemperatureSplit[0]*100))/10;
	TemperatureSplit[2] = Temperature-(TemperatureSplit[0]*100)-(TemperatureSplit[1]*10);
	//文字列表示
	drawStringToLcd("Temperature: ", 0);
	//100の位表示
	if(TemperatureSplit[0]==0)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+TemperatureSplit[0], DATA);
	waitLcd();
	//10の位表示
	if(TemperatureSplit[1]==0)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+TemperatureSplit[1], DATA);
	waitLcd();
	//1の位表示
	write4bitLcd(0x30+TemperatureSplit[2], DATA);
	waitLcd();
}


/* 保温モード表示 */
void drawKeepWarmMode(int ModeId){
	//文字列表示
	drawStringToLcd(" KeepMode  :  ", 1);
	//10の位表示
	if((ModeId/10)==0)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd((0x30+(ModeId/10)), DATA);
	waitLcd();
	//1の位表示
	write4bitLcd((0x30+(ModeId-(ModeId/10)*10)), DATA);
	waitLcd();
}


/* 7セグメントLED初期化 */
void init7SegLed(void){
	PA.DDR = 0xff;
	PA.DR.BYTE = 0x00;
}


/* キッチンタイマー表示 */
void drawKitchenTimer(int RemainingTime){
	//10の位表示
	PA.DR.BYTE &= 0x00;
	PA.DR.BYTE |= (RemainingTime/10);
	PA.DR.BYTE |= 0x20;
	timer10us(50);
	//1の位表示
	PA.DR.BYTE &= 0x00;
	PA.DR.BYTE |= RemainingTime - ((RemainingTime/10)*10);
	PA.DR.BYTE |= 0x10;
	timer10us(50);
}


/* LED初期化 */
void initLed(void){
	PB.DDR = 0xff;
	PB.DR.BYTE = 0x00;
}


/* 水位ゲージ表示 */
void drawWaterLevel(int WaterLevel){
	if(WaterLevel>=4)
		PB.DR.BYTE |= 0x0f;
	else if(WaterLevel==3){
		PB.DR.BYTE &= 0xf7;
		PB.DR.BYTE |= 0x07;
	}
	else if(WaterLevel==2){
		PB.DR.BYTE &= 0xf3;
		PB.DR.BYTE |= 0x03;
	}
	else if(WaterLevel==1){
		PB.DR.BYTE &= 0xf1;
		PB.DR.BYTE |= 0x01;
	}
	else if(WaterLevel<=0)
		PB.DR.BYTE &= 0xf0;
	
}


/* LED点灯 */
void onLamp(LampId_t LampId){
	switch(LampId){
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
void offLamp(LampId_t LampId){
	switch(LampId){
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
