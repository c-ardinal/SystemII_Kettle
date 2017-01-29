/* 
 * ------------------------------------------------------ * 
 * @file	: Button.c
 * @brief	: 各ボタンのチェックを行う
 * ------------------------------------------------------ * 
 */
#include "Button.h"


/* 
 * ------------------------------------------------------ * 
 * @function: ボタンの初期化を行う
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
void initButton(void){
	P4.DDR = 0x00;
}


/* 
 * ------------------------------------------------------ * 
 * @function: ボタンの状態を取得する
 * @param	: ボタンID(Button.hに宣言)
 * @return	: 0::解放中、1::押下中
 * ------------------------------------------------------ * 
 */
int isState(ButtonId_t buttonId){
	return ((P4.DR.BYTE & (0x01 << buttonId)) >> buttonId);
}


/* 
 * ------------------------------------------------------ * 
 * @function: ボタンの状態変化を取得する
 * @param	: ボタンID(Button.hに宣言)
 * @return	: PRESS_NO::解放中, PRESS_START::解放→押下, 
 * 			  PRESS_NOW::押下中, PRESS_END::押下→解放(constant.hに宣言)
 * ------------------------------------------------------ * 
 */
int isPressed(ButtonId_t buttonId){
	// ボタンの状態保持用変数 
	static int buttonState[8][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	buttonState[buttonId][PAST] = buttonState[buttonId][NEW];
	buttonState[buttonId][NEW] = isState(buttonId);
	//解放→押下
	if(buttonState[buttonId][PAST]==OFF 
		&& buttonState[buttonId][NEW]==ON)
		return PRESS_START;
	//押下中
	else if(buttonState[buttonId][PAST]==ON 
		&& buttonState[buttonId][NEW]==ON)
		return PRESS_NOW;
	//押下→解放
	else if(buttonState[buttonId][PAST]==ON 
		&& buttonState[buttonId][NEW]==OFF)
		return PRESS_END;
	//解放中
	else 
		return PRESS_NO;
}

