#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

/* *************************************************************************************** */

/* Bootloader version 1.0*/
#define BL_VERSION    		 				1

#define BL_N_PAGES							8
/*BL used addresses*/
#define USER_APP_BASE_ADDRESS               0x08002400
#define USER_APP_USED_PAGE_NUM            	9

#define BL_BASE_ADDRESS                     0x08000000

/*Max flash memory sectors , for STM32F446RE there are 7 sectors*/
#define MAX_PAGES_NUM                     	55
/*Hex file line won't be more than 13 - 50 character*/
#define BL_BUFFER_SIZE                      100

/*Time to wait on pressing boot button in ms*/
#define BL_T_BOOT_BUTTON_MS                 1000

#define BL_LED								0

#define SW_BOOT_SW							0
/* *************************************************************************************** */

/*BL commands*/

/*This command is used to write data in to different memories of the MCU.*/
#define BL_MEM_WRITE							 	'1'

/*This command is used to mass erase or sector erase of the user flash .*/
#define BL_FLASH_ERASE     							'2'

/*This command is used to read data from different memories of the microcontroller.*/
#define BL_MEM_READ				 					'3'

/*This command is used to jump bootloader to specified address.*/
#define BL_GO_TO_ADDR								'4'

/*This command is used to enable or disable read/write protect on different sectors of the user flash .*/
#define BL_EN_RW_PROTECT	 						'5'

/*This command is used disable all sector read/write protection. */
#define BL_DIS_R_W_PROTECT 							'6'

/*This command is used to read the FLASH Read Protection level.*/
#define BL_GET_RDP_STATUS	 						'7'

/*This command is used to read the bootloader version from the MCU.*/
#define BL_GET_VER				 					'8'

/*This command is used to read the MCU chip identification number.*/
#define BL_GET_CID				 					'9'

/*This command is used to read the MCU chip identification number.*/
#define BL_JMB_USR_APP		 						'A'

/*This command is used to read the MCU chip identification number.*/
#define RSTR_SYS									'B'

/* *************************************************************************************** */

void BL_vHandleMEMWriteCMD(void);
void BL_vHandleMEMWriteWIFICMD(void);
void BL_vHandleFlashEraseCMD(void);
void BL_vStartUserApp(void);
void Bl_vGetHexLineWifi(uint8 *pu8Line , Flag_Status AckFlag);

#endif
