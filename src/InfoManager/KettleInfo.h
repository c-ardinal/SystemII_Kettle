#ifndef _KETTLE_INFO_H_
#define _KETTLE_INFO_H_


#include "../3048f.h"


/* 	情報管理用構造体 */
typedef struct{
	int heatState;
	int pumpState;
	float waterTemperature;
	int lidState;
	int waterLevel;
	int lockState;
	int remainingTime;
	float targetTemperature;
}info_t;


typedef struct{
	void (*setHeatState)(int);
	void (*setPumpState)(int);
	void (*setWaterTemperature)(float);
	void (*setLidState)(int);
	void (*setWaterLevel)(int);
	void (*setLockState)(int);
	void (*setRemainingTime)(int);
	void (*setTargetTemperature)(float);

	int (*getHeatState)(void);
	int (*getPumpState)(void);
	float (*getWaterTemperature)(void);
	int (*getLidState)(void);
	int (*getWaterLevel)(void);
	int (*getLockState)(void);
	int (*getRemainingTime)(void);
	float (*getTargetTemperature)(void);
}KettleInfo;


KettleInfo newKettleInfo(void);

/* setter */
void setHeatState(int);
void setPumpState(int);
void setWaterTemperature(float);
void setLidState(int);
void setWaterLevel(int);
void setLockState(int);
void setRemainingTime(int);
void setTargetTemperature(float);


/* getter */
int getHeatState(void);
int getPumpState(void);
float getWaterTemperature(void);
int getLidState(void);
int getWaterLevel(void);
int getLockState(void);
int getRemainingTime(void);
float getTargetTemperature(void);


#endif
