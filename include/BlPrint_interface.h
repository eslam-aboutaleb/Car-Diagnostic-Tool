/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: BLPrint_interface.h		                                         */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef BLPRINT_INTERFACE_H_
#define BLPRINT_INTERFACE_H_

/* **************************************************************************************** */
							/* Functions prototypes */
/* **************************************************************************************** */

void BlPrint_vInitCMD(void);
void BlPrint_vInitDebug(void);
Error_Status BlPrint_xReadCMD(uint8 *pu8DataBuffer , uint16 Copy_u16DataSize);
void BlPrint_vTransmitCMD(uint8 *pu8DataBuffer,uint16 Copy_u16DataSize);
void BlPrint_vPrintDebug(uint8 *Data,...);
void BlPrint_vPrintCMD(uint8 *Data,...);


#endif /*BLPRINT_INTERFACE_H_*/
