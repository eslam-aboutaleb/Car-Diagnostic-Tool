/*
 * LM35_Interface.h
 *
 *  Created on: Nov 21, 2020
 *      Author: Abeer Mohamed Hassan
 */

#ifndef LM35_LM35_INTERFACE_H_
#define LM35_LM35_INTERFACE_H_


void LM35_VidSetADCChannel(u8 Copy_U8Channel);

void LM35_VidRead(f32 * Copy_U16Read, u16 Copy_U8ADCRead);

void LM35_VidUpdate();

f32 LM35_F32GetTemp();

 #endif /* LM35_LM35_INTERFACE_H_ */
