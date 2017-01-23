#include "PumpControl.h"
#include "../InfoManager/KettleInfo.h"


KettleInfo kettleInfo;


/*  */
void initPump(void){
	DA.DR1 = 0x00;
	DA.CR.BIT.DAOE1 = 1;
	kettleInfo = newKettleInfo();
}


/**/
void doPump(void){
	DA.DR1 = 255;
	kettleInfo.setPumpState(SUPPLY_NOW);
}


/**/
void stopPump(void){
	DA.DR1 = 0;
	kettleInfo.setPumpState(SUPPLY_NO);
}
