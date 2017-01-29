/* 
 * ------------------------------------------------------ * 
 * @file	: constant.h
 * @brief	: システムの可変設定値や固定値を記述する
 * ------------------------------------------------------ * 
 */
#ifndef _CONSTANT_H_
#define _CONSTANT_H_


/* 
 * ------------------------------------------------------ * 
 * @brief	: 可変設定値
 * ------------------------------------------------------ * 
 */
 
 
//PID制御l用パラメータ
#define  KC						55.000F
#define  PU						54.000F


//保温モード識別ID
#define HIGH_TEMPERATURE_MODE	98.00F
#define SAVING_MODE				90.00F
#define MILK_MODE				60.00F


//キッチンタイマ計測最大時間(秒数)
#define KITCHEN_TIMER_MAX_TIME	3600 


//水量の定義
#define WATER_LV_MIN			1
#define WATER_LV_MAX			4
#define WATER_LV_EMPTY			0


/* 
 * ------------------------------------------------------ * 
 * @brief	: 以下固定値
 * ------------------------------------------------------ * 
 */


//LCD::制御レジスタ識別ID
#define CONTROL					0
#define DATA					1


//LCD::データW/R定数化
#define WRITE					0
#define READ					1


//スイッチの状態繊維確認用
#define PAST					0
#define NEW						1


//ON/OFF定数化
#define OFF						0
#define  ON						1


//T or F定数化
#define FALSE					0
#define TRUE					1


//保温モード::LOCK/UNLOCK定数化
#define UNLOCK					0
#define LOCK					1


//スイッチ::状態定義
#define PRESS_NO				0
#define PRESS_START				1
#define PRESS_NOW				2
#define PRESS_END				3


//ふたセンサ::状態定義
#define CLOSE					0
#define OPEN					1


//加熱状態
#define NONE					0
#define BOIL					1
#define BOIL_END				2
#define KEEP_WARM				3


//給湯状態
#define SUPPLY_NO				0
#define SUPPLY_NOW				1


#endif

