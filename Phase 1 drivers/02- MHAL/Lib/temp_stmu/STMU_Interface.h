/*
 * STMU_Interface.h
 *
 *  Created on: Dec 16, 2020
 *      Author: Abeer
 */

#ifndef STMU_INTERFACE_H_
#define STMU_INTERFACE_H_

typedef struct{

	void (*CllBackFunc)(void);
	void (*UpdateFunc)(void);
	u16 periodicity;
}Task_Type;

typedef enum{

	STMU_SRC_AHB_8,
	STMU_SRC_AHB=4
}STMU_CLOCK_SRC;

void STMU_voidInit(STMU_CLOCK_SRC CLK_Source);

void STMU_voidAddTask(Task_Type task);

void STMU_voidStartScheduler(u32 tick_ms);



#endif /* STMU_INTERFACE_H_ */
