/*////////////////////////////////////////////////////////////////////////////// */
/* Author: Eslam Ehab Aboutaleb                                                  */
/* File:  SYSTICK_interface.h                                                    */
/* Version: V01                                                                  */
/* Date: 28-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

/************************************************************************************************************* */
#define CPU_CLK     			  		   (8000000)
#define SYSTICK_TIMER_TICK_MS               1
#define SYS_MAX_DELAY  						0xFFFFFFFFU

/************************************************************************************************************* */
/*Systick ticks types*/
#define SYSTICK_TICKS_US                    1
#define SYSTICK_TICKS_MS					1000
#define SYSTICK_TICKS_S						1000000

/************************************************************************************************************* */
/* Systick clock source options*/
#define	STK_CLK_SRC_AHB_DIVIDED_BY_8        0
#define	STK_CLK_SRC_AHB						1

/************************************************************************************************************* */
/* Systick Interval modes*/
#define STK_SINGLE_INTERVAL_MODE		    0
#define STK_PERIODIC_INTERVAL_MODE	     	1

/************************************************************************************************************* */
/*Functions prototype*/
void STK_vInit(uint8 Copy_xClockSource);
void STK_vSetBusyWait(uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe);
void STK_vSetIntervalSingle  ( uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe, void (*Copy_vpFuncPtr)(void));
void STK_vSetIntervalPeriodic(uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe , void (* Copy_vpFuncPtr) (void));
void STK_vStopInterval(void);
uint32 STK_u32GetRemainingTime(uint32 Copy_u32TicksTybe);
uint32 STK_u32GetElapsedTime(uint32 Copy_u32TicksTybe);
void STK_vInitSysTickCounter(uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe);
uint32 STK_u32GetSysTick(void);


#endif /*SYSTICK_INTERFACE_H*/
