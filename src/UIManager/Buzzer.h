#ifndef _BUZZER_H_
#define _BUZZER_H_


#include "../3048f.h"
#include "../constant.h"


typedef struct{
    void (*initBuzzer)(void);
    void (*playBuzzer)(int);
    void (*onBuzzer)(void);
    void (*offBuzzer)(void);
} Buzzer;


Buzzer newBuzzer(void);
void initBuzzer(void);


void playBuzzer(int);
void onBuzzer(void);
void offBuzzer(void);


#endif
