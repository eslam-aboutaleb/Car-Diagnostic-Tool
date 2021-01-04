/*
 * LPWR_Intereface.h
 *
 *  Created on: Dec 23, 2020
 *      Author: Abeer
 */

#ifndef LPWR_INTEREFACE_H_
#define LPWR_INTEREFACE_H_


typedef enum{
	LPWR_SLEEP_NOW,
	LPWR_SLEEP_ON_EXIT
}SleepModes;

typedef enum{
	LPWR_VOLT_ON,
	LPWR_VOLT_LOW
}Voltage_regulator_mods;

void LPWR_VidInit();

void LPWR_VidStandby( );

void LPWR_VidSleep(u8 Copy_U8SleepMode);


#endif /* LPWR_INTEREFACE_H_ */
