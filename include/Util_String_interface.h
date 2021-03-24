#ifndef UTIL_STRING_INTERFACE_H_
#define UTIL_STRING_INTERFACE_H_

#define UTIL_IS_VALID_HEX(HEXCHAR)										(HEXCHAR >= '0' && HEXCHAR <= '9')||\
																		(HEXCHAR >= 'A' && HEXCHAR <= 'F')||\
																		(HEXCHAR >= 'a' && HEXCHAR <= 'f')


uint16 UtilString_u16HexToDecLittleEndian ( uint8 *Copy_HexNum );
uint16 UtilString_u16countStr(uint8 *pu8Str);
uint32 UtilString_u32Pow(uint32 Copy_u32Base ,uint32 Copy_u32Power);
Error_Status UtilString_xStrToNum(uint8 *pu8Str , uint32 *pu32Result);
Flag_Status UtilString_xFindWord(uint8 *pu8WordToFind , uint8 *pu8Line);
void UtilString_vNumtoStr(sint32 Copy_s32Num,uint8 *pu8Buffer);


#endif
