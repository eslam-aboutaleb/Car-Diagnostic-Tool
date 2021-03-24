/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: BLPrint_program.c		                                             */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "ComM_interface.h"

#include "BlPrint_interface.h"
#include "BlPrint_config.h"

/* ***************************************************************************************
Function   : BlPrint_vInitCMD
Parameters : void
Return     : void
Job : initializes command port
 **************************************************************************************** */
void BlPrint_vInitCMD(void)
{
	ComM_xInit(&hPrintCmdCom);
}

/* ***************************************************************************************
Function   : BlPrint_vInitDebug
Parameters : void
Return     : void
Job : initializes debug port
 **************************************************************************************** */
void BlPrint_vInitDebug(void)
{
#if BL_DEBUG_MESSAGE_EN	==	ENABLE
	ComM_xInit(&hPrintDebugCom);
#endif
}

Error_Status BlPrint_xReadCMDTillCharacter(uint8 *pu8DataBuffer , uint8 LimitCharacter)
{
	Error_Status Local_xErrorStatus	=	E_OK;
	Local_xErrorStatus				= 	ComM_xReceiveDataTillCharacter(&hPrintCmdCom,LimitCharacter);

	return Local_xErrorStatus;
}

/* ***************************************************************************************
Function   : BlPrint_xReadCMD
Parameters : Pointer to buffer type uint8
Return     : void
Job : Receive strings by Command port
 **************************************************************************************** */
Error_Status BlPrint_xReadCMD(uint8 *pu8DataBuffer , uint16 Copy_u16DataSize)
{
	Error_Status Local_xErrorStatus	=	E_OK;
	hPrintCmdCom.DataRx				= pu8DataBuffer;
	hPrintCmdCom.DataRxSize			= Copy_u16DataSize;

	Local_xErrorStatus				=	ComM_xReceiveData(&hPrintCmdCom);

	return Local_xErrorStatus;
}

/* ***************************************************************************************
Function   : BlPrint_vTransmitCMD
Parameters : Pointer to buffer type uint8 , DataSize from type uint32
Return     : void
Job : Send data by command port
 **************************************************************************************** */
void BlPrint_vTransmitCMD(uint8 *pu8DataBuffer,uint16 Copy_u16DataSize)
{
	hPrintCmdCom.DataTx		= pu8DataBuffer;
	hPrintCmdCom.DataTxSize	= Copy_u16DataSize;

	ComM_xSendData(&hPrintCmdCom);
}


/* ***************************************************************************************
Function   : BlPrint_vPrintCMD
Parameters : Pointer to buffer type uint8
Return     : void
Job : Print function for command port
 **************************************************************************************** */
void BlPrint_vPrintCMD(uint8 *Data,...)
{
	uint8 Str[BLPRINT_DEBUG_BUF_SIZE];
	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, Data);
	vsprintf(Str, Data,args);
	hPrintCmdCom.DataTxSize	= strlen(Str);
	hPrintCmdCom.DataTx		= Str;
	ComM_xSendData(&hPrintCmdCom);
	va_end(args);
}

/* ***************************************************************************************
Function   : BlPrint_vPrintDebug
Parameters : Pointer to buffer type uint8
Return     : void
Job : Print function for debugging port
 **************************************************************************************** */
void BlPrint_vPrintDebug(uint8 *Data,...)
{
#if BL_DEBUG_MESSAGE_EN == ENABLE
	uint8 Str[BLPRINT_DEBUG_BUF_SIZE];
	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, Data);
	vsprintf(Str, Data,args);
	hPrintDebugCom.DataTxSize	= strlen(Str);
	hPrintDebugCom.DataTx		= Str;
	ComM_xSendData(&hPrintDebugCom);
	va_end(args);
#else
	UN_USED(*Data);
#endif
}
