#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"


#include "SW_interface.h"
#include "Led_interface.h"
#include "BlPrint_interface.h"
#include "FPEC_interface.h"
#include "Util_String_interface.h"
#include "ESP_interface.h"
#include "SYSTICK_interface.h"

#include "Bootloader_interface.h"
#include "Bootloader_config.h"

/* ***************************************************************************************
Function : BL_vHandleGetVerCMD
Parameters : void
Return : void
Job : Gets current bootloader version
 **************************************************************************************** */
void BL_vHandleGetVerCMD(void)
{
	uint8 Version = (uint8)BL_VERSION;

	BlPrint_vPrintCMD((uint8*)"Bootloader version is %d  \r\n",Version );
}
#define BL_MAX_N_SECTORS_DISITS										5
/* ***************************************************************************************
Function : BL_vHandleFlashEraseCMD
Parameters : void
Return : void
Job : Erase any number of sectors that the user enters but sector 0 & 1 because the boolo-
      -ader consumes them
 **************************************************************************************** */
void BL_vHandleFlashEraseCMD(void)
{
	Error_Status Local_xErrorStatus				= E_OK;
	uint8 PageNumASCII 							= 0;
	uint8 Local_u8PageNum 						= 0;

	uint8 Index 								= 0;
	uint8 N_Sectors[BL_MAX_N_SECTORS_DISITS]	= {0};
	uint32 ActSectorsNum						= 0;

	BlPrint_vPrintCMD((uint8*)"Enter number of flash Pages \r\n");
	for(Index = 0;N_Sectors[Index] != '\0';Index++ )
	{
		BlPrint_xReadCMD(&N_Sectors[Index],1);
	}

	/*Convert the ASCII value to a number*/
	Local_xErrorStatus	=	UtilString_xStrToNum(N_Sectors,&ActSectorsNum);
	if(Local_xErrorStatus != E_OK)
	{
		BlPrint_vPrintCMD((uint8*)"You entered invalid numbers %s Please use only numbers",N_Sectors);
	}


	for(Index=0;Index<ActSectorsNum;Index++)
	{
		BlPrint_vPrintCMD((uint8*)"Enter flash page number %d \r\n",Index);
		BlPrint_xReadCMD(&PageNumASCII,1);

		/*Convert the ASCII value to a number*/
		Local_u8PageNum = (uint8)PageNumASCII-'0';

		/* Check if the user wants to delete a section that includes bootloader */
		if(Local_u8PageNum < BL_N_PAGES)
		{
			FPEC_xPageErase(Local_u8PageNum);
			BlPrint_vPrintDebug((uint8*)"Page %d is erased \r\n",Local_u8PageNum);
		}
		else
		{
			BlPrint_vPrintDebug((uint8*)"Page %d can't be erased \r\n",Local_u8PageNum);
		}
	}
}

/* ***************************************************************************************
Function : BL_Handle_MEM_Write_CMD
Parameters : void
Return : void
Job : Reads hex file that is sent through communication protocol and translates it to
      digits and writes them to flash
 **************************************************************************************** */
void BL_vHandleMEMWriteCMD(void)
{
	uint16 Index					=	0;
	uint16 Data_Index				=	0;
	uint8 N_Data					=	0;
	sint16 Data						=	0;
	uint8 Data_RX					=	0;
	uint8 RX_Buffer[100]			=	{0};
	uint8 OffSet_Data_Buffer[100]		=	{0};
	sint16 Address 					= 	0;
	Error_Status Local_xErrorStatus	=	E_OK;

	/*Clear flash sectors that are present after bootloader to make sure there is no other images in the flash memory*/
	for(Index=USER_APP_USED_PAGE_NUM;Index<=MAX_PAGES_NUM;Index++)
	{
		FPEC_xPageErase(Index);
	}

	BlPrint_vPrintCMD((uint8*)"Type the hex file \r\n");

	/*Critical section, disable interrupts*/
	//__disable_irq();

	/*Turn on Led to indicate of flashing the program*/
	LED_xSetState(BL_LED,LED_ON);

	while(1)
	{
		/*Receive data until it is start of new hex line*/
		Local_xErrorStatus	=	BlPrint_xReadCMD(&Data_RX,1);

		if(Local_xErrorStatus	==	E_NOK)
		{
			BlPrint_vPrintDebug((uint8*)"Error happened while receiving the hex line there is no indication of new line\r\n");
		}
		if(Data_RX == ':')
		{
			/*Loop until there is new line to get all data after ':' into buffer, 13 = ASCII for enter button */
			for(Index=0;Data_RX!= 13;Index++)
			{
				Local_xErrorStatus	=	BlPrint_xReadCMD(&Data_RX,1);
				RX_Buffer[Index]	=	Data_RX;

				/* Print a debug error message if there is any error while receiving */
				if(Local_xErrorStatus	==	E_NOK)
				{
					BlPrint_vPrintDebug((uint8*)"Error happened while receiving the hex line at Index %d \r\n",Index);
				}
			}

			/* First & second in the array determines the length of data */
			N_Data=(( ( RX_Buffer[0]-'0')*16 )+( (RX_Buffer[1]-'0')*1) );

			/* If there is no data */
			if(N_Data == 0)
			{
				/*Terminate the while loop*/
				break;
			}

			/* Third & 4th & 5th & 6th are the address */
			/* Convert them from ASCII to digits */

			OffSet_Data_Buffer[0]	=	RX_Buffer[2];
			OffSet_Data_Buffer[1]	=	RX_Buffer[3];
			OffSet_Data_Buffer[2]	=	RX_Buffer[4];
			OffSet_Data_Buffer[3]	=	RX_Buffer[5];

			Address	=	UtilString_u16HexToDecLittleEndian(OffSet_Data_Buffer) + BL_BASE_ADDRESS;


			/* Data is in little endian order */
			for(Data_Index=0,Index=0;Index<N_Data;Data_Index+=4,Index+=2)
			{
				OffSet_Data_Buffer[0]	=	RX_Buffer[10 + Data_Index];
				OffSet_Data_Buffer[1]	=	RX_Buffer[11 + Data_Index];
				OffSet_Data_Buffer[2]	=	RX_Buffer[8  + Data_Index];
				OffSet_Data_Buffer[3]	=	RX_Buffer[9  + Data_Index];

				Data	=	UtilString_u16HexToDecLittleEndian(OffSet_Data_Buffer);

				/*Write data to the address*/
				FPEC_xProgrammHalfword(Address+Index,Data);
			}
		}
	}
	/*Enable interrupts*/
	//__enable_irq();

	/*Turn off Led to indicate the end of flashing the program*/
	LED_xSetState(BL_LED,LED_OFF);


	BlPrint_vPrintDebug((uint8*)"Writing on memory is done \r\n");
}
static uint8 Wifi_Buffer[5000]				=	{0};
/* *************************************************************************************** */
void Bl_vGetHexLineWifi(uint8 *pu8Line , Flag_Status AckFlag)
{
	static Flag_Status Local_xFlag			=	E_OK;
	static uint16 Local_u16Index			=	0;
	uint16 Local_u16LineIndex				=	0;
	uint8 buf[100]={0};

	if(AckFlag == E_NOK)
	{
		memset(Wifi_Buffer,'\0',sizeof(Wifi_Buffer));
		/* Get the new content of the hex lines page */
		ESP_xServerConnect((uint8*)"TCP",(uint8*)BL_WEBSITE_IP,(uint8*)"80");

		ESP_xGetDataCustomStart((uint8*)BL_HEX_TXT_FILE,':',Wifi_Buffer);
		Local_u16Index = 0;
	}

	else
	{
		if(Wifi_Buffer[Local_u16Index] == '\0')
		{
			memset(Wifi_Buffer,'\0',sizeof(Wifi_Buffer));
			ESP_xServerConnect((uint8*)"TCP",(uint8*)BL_WEBSITE_IP,(uint8*)"80");

			/* 2- Send the Get command */
			ESP_xGetData((uint8*)BL_ACK_LINK,buf);
			/* ********************************************************** */
			/* Get the new content of the hex lines page */
			ESP_xServerConnect((uint8*)"TCP",(uint8*)BL_WEBSITE_IP,(uint8*)"80");

			ESP_xGetDataCustomStart((uint8*)BL_HEX_TXT_FILE,':',Wifi_Buffer);
			Local_u16Index = 0;
		}
	}
	for( ;Wifi_Buffer[Local_u16Index] != '\n';Local_u16Index++,Local_u16LineIndex++)
	{
		pu8Line[Local_u16LineIndex] = Wifi_Buffer[Local_u16Index];
	}
	Local_u16Index++;
	//pu8Line[Local_u16LineIndex] = '\n';

	//STK_vSetBusyWait(1000,SYSTICK_TICKS_MS);

}

#define BL_IS_VALID_HEX(HEXCHAR)										(HEXCHAR >= '0' && HEXCHAR <= '9')||\
							(HEXCHAR >= '0' && HEXCHAR <= '9')

/* ***************************************************************************************
Function : BL_vHandleMEMWriteWIFICMD
Parameters : void
Return : void
Job : Reads hex file that is sent through communication protocol and translates it to
      digits and writes them to flash
 **************************************************************************************** */
void BL_vHandleMEMWriteWIFICMD(void)
{
	uint16 Index					=	0;
	uint16 Data_Index				=	0;
	uint8 N_Data					=	0;
	sint16 Data						=	0;
	uint8 Data_RX					=	0;
	uint8 RX_Buffer[100]			=	{0};
	uint8 OffSet_Data_Buffer[100]	=	{0};
	sint16 Address 					= 	0;

	/*Clear flash sectors that are present after bootloader to make sure there is no other images in the flash memory*/
	for(Index=USER_APP_USED_PAGE_NUM;Index<=MAX_PAGES_NUM;Index++)
	{
		FPEC_xPageErase(Index);
	}

	/*Turn on Led to indicate of flashing the program*/
	LED_xSetState(BL_LED,LED_ON);

	while(1)
	{
		Bl_vGetHexLineWifi(RX_Buffer , E_OK);
		Data_RX = RX_Buffer[0];


		if(Data_RX == ':' || Data_RX == '\r' )
		{

			/* First & second in the array determines the length of data */
			N_Data=(( ( RX_Buffer[1]-'0')*16 )+( (RX_Buffer[2]-'0')*1) );

			/* If there is no data */
			if(N_Data == 0)
			{
				/*Terminate the while loop*/
				break;
			}

			/* Third & 4th & 5th & 6th are the address */
			/* Convert them from ASCII to digits */

			OffSet_Data_Buffer[0]	=	RX_Buffer[3];
			OffSet_Data_Buffer[1]	=	RX_Buffer[4];
			OffSet_Data_Buffer[2]	=	RX_Buffer[5];
			OffSet_Data_Buffer[3]	=	RX_Buffer[6];

			Address	=	UtilString_u16HexToDecLittleEndian(OffSet_Data_Buffer) + BL_BASE_ADDRESS;


			/* Data is in little endian order */
			for(Data_Index=0,Index=0;Index<N_Data;Data_Index+=4,Index+=2)
			{
				OffSet_Data_Buffer[0]	=	RX_Buffer[11 + Data_Index];
				OffSet_Data_Buffer[1]	=	RX_Buffer[12 + Data_Index];
				OffSet_Data_Buffer[2]	=	RX_Buffer[9  + Data_Index];
				OffSet_Data_Buffer[3]	=	RX_Buffer[10 + Data_Index];

				Data	=	UtilString_u16HexToDecLittleEndian(OffSet_Data_Buffer);

				/*Write data to the address*/
				FPEC_xProgrammHalfword(Address+Index,Data);
			}
		}
	}


	/*Turn off Led to indicate the end of flashing the program*/
	LED_xSetState(BL_LED,LED_OFF);


}
