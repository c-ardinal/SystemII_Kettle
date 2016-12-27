#include "Button.h"


static int buttonState[8][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};


/* ボタン初期化 */
void initButton(void){
	P4.DDR = 0x00;
}


/* 各種ボタン状態取得 */
int isState(ButtonId_t buttonId){
	return ((P4.DR.BYTE & (0x01 << buttonId)) >> buttonId);
}


/* 各種ボタン状態判断 */
int isPressed(ButtonId_t buttonId){
	buttonState[buttonId][0] = buttonState[buttonId][1];
	buttonState[buttonId][1] = isState(buttonId);
	if(buttonState[buttonId][0]==0 && buttonState[buttonId][1]==1)
		return 1;
	else if(buttonState[buttonId][0]==1 && buttonState[buttonId][1]==1)
		return 2;
	else if(buttonState[buttonId][0]==1 && buttonState[buttonId][1]==0)
		return 3;
	else 
		return 0;
}

