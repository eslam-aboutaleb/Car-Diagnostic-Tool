/*
 * STMU_Program.c
 *
 *  Created on: Dec 16, 2020
 *      Author: Abeer
 */
#include "../lib/STD_Types.h"
#include "../lib/BIT_MATH.h"
#include "../include/MSTK_Interface.h"
#include "../include/STMU_Private.h"
#include "../include/STMU_Interface.h"
#include "../include/STMU_Config.h"


static u8 tasks_counter = 0;
static Task_Type task_arr[ TASKS_NUM];

void STMU_voidInit(STMU_CLOCK_SRC CLK_Source){

	MSTK_VidInit(CLK_Source);
}


static void STMU_voidScheduler(){

	for (u8 i = 0; i < tasks_counter ; i++) {

		u8 count=MSTK_U8GetCounter()-1;

		//CHECK if it has reached the periodicity of this task
		if((count % (task_arr[i].periodicity))==0  && count > 0){

			//pause the timer of TMU
			MSTK_VidPauseTimer();

			//call the update funtion to update the average temperature
			task_arr[i].UpdateFunc();

			//reset the counter
			MSTK_VidClearCounter();

			//resume the timer of TMU
			MSTK_VidResumeTimer();

		}
		else{

			//call the callback funtion to read new temperature
			task_arr[i].CllBackFunc();
		}
	}
}



void STMU_voidAddTask(Task_Type task){

	//add new task to the array of tasks
	task_arr[tasks_counter]=task;

	//increment the task iterator
	tasks_counter++;

}

void STMU_voidStartScheduler(u32 tick_ms){

	if(tasks_counter == TASKS_NUM){

		//start the timer of TMU
		MSTK_VidSetIntervalPeriodic(tick_ms*CONVERT_TO_US , STMU_voidScheduler );
	}
	else{
		//error
	}
}


