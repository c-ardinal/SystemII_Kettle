//#ifndef _SENSOR_CHECK_H_
//#define _SENSOR_CHECK_H_


#include "../3048f.h"


void initSensor(void);
int checkWaterTemperature(void);
int checkLidState(void);
int checkWaterLevel(void);
void int_irq4(void);


//#endif
