//#ifndef _TEMPERATURE_CONTROL_H_
//#define _TEMPERATURE_CONTROL_H_


#include "../3048f.h"
#include "../constant.h"


int doBoiling(void);
void doKeepWarm(void);
void switchKeepWarmMode(void);
int culHeaterPid(float, float);


//#endif
