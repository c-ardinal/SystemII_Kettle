#include "Button.h"


/* ボタン初期化 */
void initButton(void){
	P4.DDR = 0x00;
}


/* 各種ボタン状態取得 */
int isState(ButtonId_t buttonId){
	return ((P4.DR.BYTE & (0x01 << buttonId)) >> buttonId);
}
