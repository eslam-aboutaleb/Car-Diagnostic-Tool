#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Util_String_interface.h"
#include "Util_String_private.h"


Flag_Status UtilString_xFindWord(uint8 *pu8WordToFind , uint8 *pu8Line)
{
	uint16 Local_u16Index	=	0;
	uint16 Local_u16Index2	=	0;
	Flag_Status Local_xFlag	=	0;

	for(Local_u16Index = 0; pu8Line[Local_u16Index] != '\0'; Local_u16Index++ )
	{
		if(pu8Line[Local_u16Index] == pu8WordToFind[0])
		{
			Local_xFlag	=	E_OK;
			for(Local_u16Index2 = 0; pu8WordToFind[Local_u16Index2] != '\0'; Local_u16Index2++ )
			{
				if(pu8Line[Local_u16Index + Local_u16Index2] != pu8WordToFind[Local_u16Index2])
				{
					Local_xFlag	=	E_NOK;
					break;
				}
			}
		}

		if(E_OK == Local_xFlag)
		{
			break;
		}
	}

	return Local_xFlag;
}


uint16 UtilString_u16HexToDecLittleEndian ( uint8 *Copy_HexNum )
{
	uint16 Base_Mul = 4096;
	uint16 DecNum = 0;
	uint16 FinalNum = 0;
	uint8 Local_u8Iterator = 0;

	for(Local_u8Iterator = 0; Copy_HexNum[Local_u8Iterator] != '\0'; Local_u8Iterator++ , Base_Mul= Base_Mul/16)
	{
		if((Copy_HexNum[Local_u8Iterator] >= '0') && (Copy_HexNum[Local_u8Iterator] <= '9'))
		{
			/*Convert the number from char to integer*/
			DecNum = Copy_HexNum[Local_u8Iterator] - '0';

			DecNum *= Base_Mul;

			FinalNum+=DecNum;
		}
		else if((Copy_HexNum[Local_u8Iterator] >= 'A') && (Copy_HexNum[Local_u8Iterator] <= 'F') )
		{
			DecNum = Copy_HexNum[Local_u8Iterator] - 55;
			DecNum *= Base_Mul;
			FinalNum+=DecNum;
		}
		else if((Copy_HexNum[Local_u8Iterator] >= 'a') && (Copy_HexNum[Local_u8Iterator] <= 'f'))
		{
			DecNum = (Copy_HexNum[Local_u8Iterator] - 86);
			DecNum = (DecNum * Base_Mul)-1;
			FinalNum+=DecNum;
		}
		else
		{
			/* No Action */
		}
	}
	return FinalNum;
}



uint16 UtilString_u16countStr(uint8 *pu8Str)
{
	uint16 Local_u16Counter = 0;
	while(*pu8Str++)
	{
		Local_u16Counter++;
	}
	return Local_u16Counter;
}
