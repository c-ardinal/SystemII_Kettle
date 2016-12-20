//#ifndef _BUTTON_H_
//#define _BUTTON_H_


#include "../3048f.h"


//ボタン識別ID
typedef enum{
	LOCK_BUTTON,
	BOIL_BUTTON,
	SUPPLY_BUTTON,
	TIMER_BUTTON,
	K_W_BUTTON
}ButtonId_t;


void initButton(void);
int isState(ButtonId_t);


//#endif
