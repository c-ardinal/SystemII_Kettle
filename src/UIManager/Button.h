#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "../3048f.h"
#include "../constant.h"


//ボタン識別ID
typedef enum{
	LOCK_BUTTON,
	BOIL_BUTTON,
	SUPPLY_BUTTON,
	TIMER_BUTTON,
	K_W_BUTTON
}ButtonId_t;


typedef struct{
    void (*initButton)(void);
    int (*isState)(ButtonId_t);
    int (*isPressed)(ButtonId_t);
} Button;


Button newButton(void);
void initButton(void);
int isState(ButtonId_t);
int isPressed(ButtonId_t);


#endif
