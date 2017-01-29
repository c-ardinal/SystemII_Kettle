/* 
 * ------------------------------------------------------ * 
 * @file	: UIControl.c
 * @brief	: ユーザインターフェースの制御を行う
 * ------------------------------------------------------ * 
 */
#include "UIControl.h"


/* 
 * ------------------------------------------------------ * 
 * @function: LCDの初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
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


/* 
 * ------------------------------------------------------ * 
 * @function: LCDに対して8bitでデータを書き込む
 * @param	: 書き込むデータ、書き込むレジスタ(DATA, CONTROL)
 * @sa		: DATA, CONTROLはconstant.hに宣言
 * @return	: void
 * ------------------------------------------------------ * 
 */
void write8bitLcd(int WriteData, int SelectRegister){
	P3.DR.BIT.B4 = SelectRegister;	//任意のレジスタ設定
	P3.DR.BIT.B6 = WRITE;			//Writeモード
	P3.DR.BYTE = (P3.DR.BYTE & 0xf0) | WriteData;
	P3.DR.BIT.B5 = ON;				//Enable信号ON
	timer250ns();
	P3.DR.BIT.B5 = OFF;				//Enable信号OFF
	timer250ns();
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDに対して4bitでデータを書き込む
 * @param	: 書き込むデータ、書き込むレジスタ(DATA, CONTROL)
 * @sa		: DATA, CONTROLはconstant.hに宣言
 * @return	: void
 * ------------------------------------------------------ * 
 */
void write4bitLcd(int WriteData, int SelectRegister){
	write8bitLcd((WriteData >> 4 & 0x0f), SelectRegister);
	write8bitLcd((WriteData & 0x0f), SelectRegister);
	waitLcd();
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDのビジーフラグを読み取る
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
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


/* 
 * ------------------------------------------------------ * 
 * @function: ビジーフラグ読み取りを用いた処理待ち
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void waitLcd(void){
	while(readBusyFlag() != 0)		//上位読み出し
		readBusyFlag();				//下位は破棄
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDに文字列を表示する
 * @param	: 表示文字列、表示する段(0, 1)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void drawStringToLcd(char *DrawString, int DrawPoint){
	write4bitLcd((0x80+(0x40*DrawPoint)), CONTROL);
	while(*DrawString)
		write4bitLcd(*DrawString++, DATA);
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDに3桁の数値を表示する
 * @param	: 表示する数値、表示する段(0, 1)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void draw3NumToLcd(int DrawNum, int DrawPoint){
	int NumSplit[3] = {0, 0, 0};
	NumSplit[0] = DrawNum/100;
	NumSplit[1] = (DrawNum-(NumSplit[0]*100))/10;
	NumSplit[2] = DrawNum-(NumSplit[0]*100)-(NumSplit[1]*10);
	write4bitLcd((0x80+(0x40*DrawPoint)), CONTROL);
	//100の位表示
	write4bitLcd(0x30+NumSplit[0], DATA);
	//10の位表示
	write4bitLcd(0x30+NumSplit[1], DATA);
	//1の位表示
	write4bitLcd(0x30+NumSplit[2], DATA);
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDにn桁の数値を表示する
 * @param	: 表示する数値、表示する段(0, 1)
 * @return	: void
 * ------------------------------------------------------ * 
 */
void drawNumToLcd(int DrawNum, int DrawPoint){
	#define arrSize 6
	int NumSplit[arrSize] = {0, 0, 0, 0, 0, 0};
	int i = 0;
	// ここの処理が冗長的なので抽象化する予定 ========================================
	NumSplit[0] = DrawNum/100000;
	NumSplit[1] = (DrawNum-(NumSplit[0]*100000))/10000;
	NumSplit[2] = (DrawNum-(NumSplit[0]*100000)-(NumSplit[1]*10000))/1000;
	NumSplit[3] = (DrawNum-(NumSplit[0]*100000)-(NumSplit[1]*10000)-(NumSplit[2]*1000))/100;
	NumSplit[4] = (DrawNum-(NumSplit[0]*100000)-(NumSplit[1]*10000)-(NumSplit[2]*1000)-(NumSplit[3]*100))/10;
	NumSplit[5] = (DrawNum-(NumSplit[0]*100000)-(NumSplit[1]*10000)-(NumSplit[2]*1000)-(NumSplit[3]*100)-(NumSplit[4]*10));
	//=============================================================================
	write4bitLcd((0x80+(0x40*DrawPoint)), CONTROL);
	for(i=0; i<arrSize; i++)
		write4bitLcd(0x30+NumSplit[i], DATA);
}


/* 
 * ------------------------------------------------------ * 
 * @function: LCDに水温を表示する
 * @param	: 水温
 * @return	: void
 * ------------------------------------------------------ * 
 */
void drawTemperature(int DrawTemperature){
	//桁ごとに分割{100の位, 10の位, 1の位}
	int TemperatureSplit[3] = {0, 0, 0};
	TemperatureSplit[0] = DrawTemperature/100;
	TemperatureSplit[1] = (DrawTemperature-(TemperatureSplit[0]*100))/10;
	TemperatureSplit[2] = DrawTemperature-(TemperatureSplit[0]*100)-(TemperatureSplit[1]*10);
	//文字列表示
	drawStringToLcd("Temperature: ", 0);
	//100の位表示
	if(DrawTemperature<=99)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+TemperatureSplit[0], DATA);
	//10の位表示
	if(DrawTemperature<=9)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd(0x30+TemperatureSplit[1], DATA);
	//1の位表示
	write4bitLcd(0x30+TemperatureSplit[2], DATA);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 保温モードを表示
 * @param	: 保温モードID
 * @return	: void
 * ------------------------------------------------------ * 
 */
void drawKeepWarmMode(int ModeId){
	//文字列表示
	drawStringToLcd(" KeepMode  :  ", 1);
	//10の位表示
	if((ModeId/10)==0)
		write4bitLcd(0x20, DATA);
	else
		write4bitLcd((0x30+(ModeId/10)), DATA);
	//1の位表示
	write4bitLcd((0x30+(ModeId-(ModeId/10)*10)), DATA);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 7segを初期化する
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void init7SegLed(void){
	PA.DDR = 0xff;
	PA.DR.BYTE = 0x00;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 7segに二桁の数値を表示する
 * @param	: キッチンタイマ残り時間
 * @return	: void
 * ------------------------------------------------------ * 
 */
void draw7SegLed(int RemainingTime){
	//10の位表示(リセット|書き込み|左点灯右消灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (RemainingTime/10) | 0x20;
	timer10us(50);
	//1の位表示(リセット|書き込み|左消灯右点灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (RemainingTime - ((RemainingTime/10)*10)) | 0x10;
	timer10us(50);
}


/* 
 * ------------------------------------------------------ * 
 * @function: 7segの左桁(10の位)のみ表示する
 * @param	: キッチンタイマ残り時間
 * @return	: void
 * ------------------------------------------------------ * 
*/
void drawLeftOf7SegLed(int RemainingTime){
	//(リセット|書き込み|左点灯右消灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (RemainingTime/10) | 0x20;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 7segの右桁(1の位)のみ表示する
 * @param	: キッチンタイマ残り時間
 * @return	: void
 * ------------------------------------------------------ * 
*/
void drawRightOf7SegLed(int RemainingTime){
	//(リセット|書き込み|左消灯右点灯)
	PA.DR.BYTE = (PA.DR.BYTE & 0x00) | (RemainingTime - ((RemainingTime/10)*10)) | 0x10;
}



/* 
 * ------------------------------------------------------ * 
 * @function: LEDを初期化する
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initLed(void){
	PB.DDR = 0xff;
	PB.DR.BYTE = 0x00;
}


/* 
 * ------------------------------------------------------ * 
 * @function: 水位を表示する
 * @param	: 水位
 * @return	: void
 * ------------------------------------------------------ * 
 */
void drawWaterLevel(int WaterLevel){
	if(WaterLevel>WATER_LV_MAX)
		WaterLevel = WATER_LV_MAX;
	else if(WaterLevel<WATER_LV_EMPTY)
		WaterLevel = WATER_LV_EMPTY;
	PB.DR.BYTE = (PB.DR.BYTE & 0xf0) | (0x0f>>(WATER_LV_MAX-WaterLevel));
}


/* 
 * ------------------------------------------------------ * 
 * @function: LEDを点灯させる
 * @param	: BOIL_LAMP::沸騰ランプ、K_W_LAMP::保温ランプ。LOCK_LAMP::ロックランプ
 * @return	: void
 * ------------------------------------------------------ * 
 */
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


/* 
 * ------------------------------------------------------ * 
 * @function: LEDを消灯させる
 * @param	: BOIL_LAMP::沸騰ランプ、K_W_LAMP::保温ランプ。LOCK_LAMP::ロックランプ
 * @return	: void
 * ------------------------------------------------------ * 
 */
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


/* 
 * ------------------------------------------------------ * 
 * @function: LEDを反転させる
 * @param	: BOIL_LAMP::沸騰ランプ、K_W_LAMP::保温ランプ。LOCK_LAMP::ロックランプ
 * @return	: void
 * ------------------------------------------------------ * 
 */
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
