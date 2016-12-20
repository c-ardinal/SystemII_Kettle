//#ifndef _UI_CONTROL_H_
//#define _UI_CONTROL_H_


#include "../3048f.h"
#include "../General/Timer.h"


//LED識別ID
typedef enum{
	BOIL_LAMP,
	K_W_LAMP,
	LOCK_LAMP
}LampId_t;
	

//保温モード識別ID
#define HIGH_TEMPERATURE_MODE 98
#define SAVING_MODE           90
#define MILK_MODE             60


//レジスタ識別ID
#define CONTROL 0
#define DATA    1


//W/R定数化
#define WRITE 0
#define READ  1


//ON/OFF定数化
#define OFF 0
#define  ON 1



void initLcd(void);
void write8bitLcd(int, int);
void write4bitLcd(int, int);
int readBusyFlag(void);
void waitLcd(void);
void drawStringToLcd(char *, int);
void drawTemperature(int);
void drawKeepWarmMode(int);

void init7SegLed(void);
void draw7SegLed(int);
void drawLeftOf7SegLed(int);
void drawRightOf7SegLed(int);

void initLed(void);
void drawWaterLevel(int);
void onLamp(LampId_t);
void offLamp(LampId_t);
void revLamp(LampId_t);


//#endif
