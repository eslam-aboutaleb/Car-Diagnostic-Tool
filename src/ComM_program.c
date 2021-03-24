/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ComM_program.c		                                             */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "USART_interface.h"

#include "ComM_config.h"
#include "ComM_interface.h"
#include "ComM_private.h"

/* **************************************************************************************** */

Error_Status ComM_xInit(ComM_TypeDef *Com_CnfgSt)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	USART_InitTypeDef USART_CnfgSt;

	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:
		/* Initialize the selected channel */
		USART_xInitStruct(&USART_CnfgSt);
		USART_xInit(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),&USART_CnfgSt);

		/* Clear error status */
		Local_xErrorStatus	=	E_OK;
		break;
	default:
		break;
	}
	return Local_xErrorStatus;
}

/* **************************************************************************************** */

Error_Status ComM_xSendData(ComM_TypeDef *Com_CnfgSt)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	uint16 Local_u16DataLength	=	0;

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:
		/* Send data over the selected channel */
		for(Local_u16DataLength = 0; Local_u16DataLength < Com_CnfgSt->DataTxSize ; Local_u16DataLength++)
		{
			USART_xSendByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
					(Com_CnfgSt->DataTx[Local_u16DataLength]),
					Com_CnfgSt->TimeOut);
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}

	return Local_xErrorStatus;
}

/* **************************************************************************************** */

Error_Status ComM_xReceiveData(ComM_TypeDef *Com_CnfgSt)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	uint16 Local_u16DataLength	=	0;

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:
		/* Send data over the selected channel */
		for(Local_u16DataLength = 0; Local_u16DataLength <
		Com_CnfgSt->DataRxSize ; Local_u16DataLength++)
		{
			USART_xGetByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
					&(Com_CnfgSt->DataRx[Local_u16DataLength]),
					Com_CnfgSt->TimeOut);
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}

	return Local_xErrorStatus;
}


/* **************************************************************************************** */
Error_Status ComM_xReceiveDataTillCharacter(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint16 Local_u16DataLength		=	0;
	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:

		/* Send data over the selected channel */
		for(Local_u16DataLength = 0;  ; Local_u16DataLength++)
		{
			USART_xGetByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
					&(Com_CnfgSt->DataRx[Local_u16DataLength]),
					Com_CnfgSt->TimeOut);

			if(Com_CnfgSt->DataRx[Local_u16DataLength] == LimitCharacter)
			{
				break;
			}
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}
	return Local_xErrorStatus;
}

/* **************************************************************************************** */
Error_Status ComM_xReceiveDatawithStartEnd(ComM_TypeDef *Com_CnfgSt,uint8 StartChar,uint8 LimitCharacter)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	Flag_Status Local_xFlag			=	E_NOK;
	sint16 Local_s16DataLength		=	0;
	uint8 Local_u8TempDataRecv		=	0;

	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:

		/* Send data over the selected channel */
		for(Local_s16DataLength = 0;  ; Local_s16DataLength++)
		{

			if(Local_xFlag != E_OK)
			{
				USART_xGetByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
						&Local_u8TempDataRecv,
						Com_CnfgSt->TimeOut);
				if(Local_u8TempDataRecv == StartChar)
				{
					Local_xFlag = E_OK;
					Local_s16DataLength = -1;
				}
			}
			else
			{
				USART_xGetByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
						&(Com_CnfgSt->DataRx[Local_s16DataLength]),
						Com_CnfgSt->TimeOut);

				if(Com_CnfgSt->DataRx[Local_s16DataLength] == LimitCharacter)
				{
					break;
				}
			}
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}
	return Local_xErrorStatus;
}

/* **************************************************************************************** */

Error_Status ComM_xSendDataTillCharacter(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint16 Local_u16DataLength		=	0;
	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:

		/* Send data over the selected channel */
		for(Local_u16DataLength = 0;  ; Local_u16DataLength++)
		{
			USART_xSendByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
					(Com_CnfgSt->DataTx[Local_u16DataLength]),
					Com_CnfgSt->TimeOut);
			if(Com_CnfgSt->DataTx[Local_u16DataLength] == LimitCharacter)
			{
				break;
			}
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}
	return Local_xErrorStatus;
}

/* **************************************************************************************** */

Error_Status ComM_xSendDataTillCharacterWithDelay(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter , uint32 u32ByteDelay)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint16 Local_u16DataLength		=	0;
	uint32 Local_u32DelayIndex = 0;

	/* Check if is it valid communication protocol */
	ERROR_CHECK(COMM_IS_VALID_COM_PROTOCOL(Com_CnfgSt->ComProtocolID));

	switch(Com_CnfgSt->ComProtocolID)
	{
	case COM_USART_ID:

		/* Send data over the selected channel */
		for(Local_u16DataLength = 0;  ; Local_u16DataLength++)
		{
			USART_xSendByteTimeOut(USART_CHOOSE_CHANNEL(Com_CnfgSt->Channel),
					(Com_CnfgSt->DataTx[Local_u16DataLength]),
					Com_CnfgSt->TimeOut);
			if(Com_CnfgSt->DataTx[Local_u16DataLength] == LimitCharacter)
			{
				break;
			}

			for(Local_u32DelayIndex = 0; Local_u32DelayIndex< u32ByteDelay ; Local_u32DelayIndex++)
			{
				asm("NOP");
			}
		}

		/* Clear error status */
		Local_xErrorStatus = E_OK;
		break;
	case COM_SPI_ID:
		break;
	case COM_I2C_ID:
		break;
	default:
		break;
	}
	return Local_xErrorStatus;
}
