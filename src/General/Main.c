/* 
 * ------------------------------------------------------ * 
 * @file	: Main.c
 * @brief	: 一番初めに呼び出される処理
 * ------------------------------------------------------ * 
 */
#include "Main.h"


/* 
 * ------------------------------------------------------ * 
 * @function: 本システムの大元
 * @param	: void
 * @return	: void
 * ------------------------------------------------------ * 
 */
int main(void){
	
	//システム初期化
	initSystem();
	while (1) {
		//システム実行
		executeSystem();
	}

	return 0;
}


