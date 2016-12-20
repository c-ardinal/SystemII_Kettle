//#ifndef _KETTLE_INFO_H_
//#define _KETTLE_INFO_H_


#include "../3048f.h"

/* 	情報管理用構造体 */
typedef struct{
	int waterTemperature;
	int lidState;
	int waterLevel;
	int lockState;
	int remainingTime;
	int targetTemperature;
}info_t;


/* setter */
void setWaterTemperature(int);
void setLidState(int);
void setWaterLevel(int);
void setLockState(int);
void setRemainingTime(int);
void setTargetTemperature(int);


/* getter */
int getWaterTemperature(void);
int getLidState(void);
int getWaterLevel(void);
int getLockState(void);
int getRemainingTime(void);
int getTargetTemperature(void);


//#endif
