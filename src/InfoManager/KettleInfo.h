//#ifndef _KETTLE_INFO_H_
//#define _KETTLE_INFO_H_


#include "../3048f.h"

/* 	情報管理用構造体 */
typedef struct{
	int heatState;
	int pumpState;
	int waterTemperature;
	int lidState;
	int waterLevel;
	int lockState;
	int remainingTime;
	int targetTemperature;
}info_t;


/* setter */
void setHeatState(int);
void setPumpState(int);
void setWaterTemperature(int);
void setLidState(int);
void setWaterLevel(int);
void setLockState(int);
void setRemainingTime(int);
void setTargetTemperature(int);


/* getter */
int getHeatState(void);
int getPumpState(void);
int getWaterTemperature(void);
int getLidState(void);
int getWaterLevel(void);
int getLockState(void);
int getRemainingTime(void);
int getTargetTemperature(void);


//#endif