/*
 * LPWR_Program.c
 *
 *  Created on: Dec 23, 2020
 *      Author: Abeer
 */
#include "../lib/STD_Types.h"
#include "../lib/BIT_MATH.h"
#include "LPWR_Intereface.h"
#include "LPWR_Private.h"

#include "../include/MRCC/MRCC_Interface.h"


void LPWR_VidInit(){

	//Enable the PWR Control Clock

	MRCC_EnablePeriClock(MRCC_APB1,MRCC_PWR_EN);

}


void LPWR_VidStandby(){

	//enable deep sleep
	SET_BIT(MSCB->SCR,SLEEPDEEP);

	//enter standby mode
	SET_BIT(MPWR->CR,BDDS);

	//clear wake up flag
	SET_BIT(MPWR->CR,CWUF);

	//Enable Wake up bin
	SET_BIT(MPWR->CSR,EWUP);

	//wait for interrupt
	__asm volatile ("wfi");
}


void LPWR_VidSleep(u8 Copy_U8SleepMode){

	//disable deep sleep
	CLR_BIT(MSCB->SCR,SLEEPDEEP);
	if(Copy_U8SleepMode==LPWR_SLEEP_NOW){

		//disable sleep on exit
		CLR_BIT(MSCB->SCR,SLEEPONEXIT);
	}
	else if(Copy_U8SleepMode==LPWR_SLEEP_ON_EXIT){

		//enable sleep on exit
		SET_BIT(MSCB->SCR,SLEEPONEXIT);

	}

	//wait for interrupt
	__asm volatile ("wfi");
}


void LPWR_VidStop(u8 Copy_U8VoltageRegMod){

	//enable deep sleep
	SET_BIT(MSCB->SCR,SLEEPDEEP);

	//enter stop mode
	CLR_BIT(MPWR->CR,BDDS);

	if(Copy_U8VoltageRegMod==LPWR_VOLT_ON){

		CLR_BIT(MPWR->CR,LPDS);
	}
	else{

		SET_BIT(MPWR->CR,LPDS);
	}

	//wait for interrupt
	__asm volatile ("wfi");
}
