/*
 * LM35_Program.c
 *
 *  Created on: Nov 21, 2020
 *      Author: Abeer Mohamed Hassan
 */
#include "../lib/BIT_MATH.h"
#include "../lib/STD_Types.h"
#include "MRCC_Interface.h"
#include "../include/ADC_private.h"
#include "../include/ADC_interface.h"
#include "../include/LM35/LM35_Config.h"

u8 temp[10] = {0};
u8 ADC_CHANNEL = 0 ;
u16 SumofTemp = 0;
f32 Avg_Temp=0;;
static u8 Local_U8Iterator=0;

void LM35_VidSetADCChannel(u8 Copy_U8Channel){

	//select the channel of ADC
	ADC_CHANNEL=Copy_U8Channel;
}



void LM35_VidRead()
{

	//read the temperature from ADCchannel
	volatile u16 Adc_read=ADC_u16GetSingleConv(MADC1,ADC_CHANNEL,ADC_SAMPLETIME_41CYCLES5);

	f32 ADC_StepSize,Analog_Read;

	//calculate the step size of ADC digital unit
	ADC_StepSize=(f32)ADC_REFVCC/ADC_Resolution;

	//convert digital read to analog read
	Analog_Read=(f32)ADC_StepSize*(Adc_read);

	//Add the Analog read to temp to calculate accurate average temperature
	temp[Local_U8Iterator]=(Analog_Read/10 );

	//calculate the sum of the temperatures
	SumofTemp += temp[Local_U8Iterator];

	//increment the iterator
	Local_U8Iterator+=1;
}


void LM35_VidUpdate(){

	//calculate the average temperature
	Avg_Temp = SumofTemp/10;

	//reset the iterator
	Local_U8Iterator=0;

	//reset the sum of temperatures
	SumofTemp=0;
}

f32 LM35_F32GetTemp(){

	//return the accurate temperature measurement
	return Avg_Temp;
}

