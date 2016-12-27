#include "PumpControl.h"


/*  */
void initPump(void){
	DA.DR1 = 0x00;
	DA.CR.BIT.DAOE1 = 1;
}


/**/
void doPump(void){
	DA.DR1 = 255;
	setPumpState(SUPPLY_NOW);
}


/**/
void stopPump(void){
	DA.DR1 = 0;
	setPumpState(SUPPLY_NO);
}
