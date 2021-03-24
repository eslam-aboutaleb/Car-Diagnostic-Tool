/*Includes*/
#include <stdint.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SW_interface.h"
#include "USART_interface.h"
#include "BlPrint_interface.h"
#include "Bootloader_interface.h"
#include "FPEC_interface.h"
#include "SCB_private.h"
/* **************************************************************************************** */

/*Static global APIs*/
static void BL_vStartBootLoader(void);
static void BL_vWelcomeMSG(void);
static void CMD_MSG(void);
static void BL_RSTR_SYS(void);
void BL_vStartUserApp(void);

/* **************************************************************************************** */

static inline __attribute__((always_inline)) void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

/* ***************************************************************************************
Function   : BL_Login
Parameters : void
Return     : void
Job : Welcome message at the beginning of the program
 **************************************************************************************** */
static void BL_vWelcomeMSG(void)
{
	BlPrint_vPrintCMD((uint8*) "Welcome : Press boot button to start bootloader \r\n");
}

/* ***************************************************************************************
Function   : BL_Login
Parameters : void
Return     : void
Job : Check if the boot button pressed or not if it is pressed will jump to the bootloader
program if it isn't it will jump to the user app
 **************************************************************************************** */
static void CMD_MSG(void)
{
	uint8 MEM_WR[]      = "1 - Memory write program \r\n";
	uint8 Flash_Erase[] = "2 - Flash Erase sectors \r\n";
	uint8 MEM_R[]       = "3 - Read memory \r\n";
	uint8 GO_Add[]      = "4 - Go to address \r\n";
	uint8 EN_P[]        = "5 - Enable protection for sector \r\n";
	uint8 DIS_P[]       = "6 - Disable all sectors protection \r\n";
	uint8 Read_P[]      = "7 - Show the current protection level \r\n";
	uint8 BL_VR[]       = "8 - Get Bootloader version \r\n";
	uint8 CH_ID[]       = "9 - Get chip ID \r\n";
	uint8 JMP_APP[]  	= "A - Jump to user APP \r\n";
	uint8 RSTR_S[]    	= "B - Restart the system \r\n";

	/*Print on screen for the user*/
	BlPrint_vPrintCMD((uint8*) "           BL Commands        \r\n");
	BlPrint_vPrintCMD((uint8*) "           ===========        \r\n");
	BlPrint_vPrintCMD((uint8*) MEM_WR);
	BlPrint_vPrintCMD((uint8*) Flash_Erase);
	BlPrint_vPrintCMD((uint8*) MEM_R);
	BlPrint_vPrintCMD((uint8*) GO_Add);
	BlPrint_vPrintCMD((uint8*) EN_P);
	BlPrint_vPrintCMD((uint8*) DIS_P);
	BlPrint_vPrintCMD((uint8*) Read_P);
	BlPrint_vPrintCMD((uint8*) BL_VR);
	BlPrint_vPrintCMD((uint8*) CH_ID);
	BlPrint_vPrintCMD((uint8*) JMP_APP);
	BlPrint_vPrintCMD((uint8*) RSTR_S);
}

/* ***************************************************************************************
Function   : BL_Login
Parameters : void
Return     : void
Job : Check if the boot button pressed or not if it is pressed will jump to the bootloader
program if it isn't it will jump to the user app
 **************************************************************************************** */
void BL_Login(void)
{
	uint32 Delay_Index=0;
	/*Welcome Msg*/
	BL_vWelcomeMSG();
	/*loop on switch*/
	for(Delay_Index=0;Delay_Index<BL_T_BOOT_BUTTON_MS*1000;Delay_Index++)
	{
		SW_vUpdate();
	}
	/*Check if the boot button has been pressed*/
	if(SW_xGetState(SW_BOOT_SW)== SW_PRESSED)
	{
		BlPrint_vPrintDebug((uint8*)"Boot button has been pressed \r\n Going to bootloader mode ... \r\n");
		/*Jump to bootloader */
		BL_vStartBootLoader();
	}
	else
	{
		BlPrint_vPrintDebug((uint8*)"Going to user APP \r\n");
		/*Jump to user app*/
		BL_vStartUserApp();
	}
}

/* ***************************************************************************************
Function   : BL_StartBootLoader
Parameters : void
Return     : void
Job : Starts the bootloader. It gets command from the user and upon it decides the right
function to execute
 **************************************************************************************** */
static void BL_vStartBootLoader(void)
{
	uint8 Data=0;

	while(1)
	{
		/*MSG to the user to tell the user to enter command*/
		BlPrint_vPrintCMD((uint8*)"Enter the command \r\n");
		/*View bootloader commands*/
		CMD_MSG();
		/*Receive first byte of BL command*/
		BlPrint_xReadCMD(&Data,1);

		/**** Decode BL commands ****/

		/*Check the coming command*/
		switch(Data)
		{
		case BL_GET_VER:
			//BL_Handle_GetVer_CMD();
			break;
		case BL_GET_CID:
			//BL_Handle_GetCid_CMD();
			break;
		case BL_GO_TO_ADDR:
			//BL_Handle_Go_CMD();
			break;
		case BL_FLASH_ERASE:
			BL_vHandleFlashEraseCMD();
			break;
		case BL_MEM_WRITE:
			BL_vHandleMEMWriteCMD();
			break;
		case BL_EN_RW_PROTECT:
			//BL_Handle_En_RW_Potect_CMD();
			break;
		case BL_MEM_READ:
			//BL_Handle_MEM_Read_CMD();
			break;
		case BL_GET_RDP_STATUS:
			//BL_Handle_ReadSectorProtect_CMD();
			break;
		case BL_DIS_R_W_PROTECT:
			//BL_Handle_Dis_RW_protect_CMD();
			break;
		case BL_JMB_USR_APP:
			//BL_StartUserApp();
			break;
		case RSTR_SYS:
			BL_RSTR_SYS();
			break;
		default:
			BlPrint_vPrintDebug((uint8*) "Invalid command code received from host \r\n");
			break;
		}
	}
}



/* ***************************************************************************************
Function   : BL_StartUserApp
Parameters : void
Return     : void
Job : Starts the user app, Change the place of main stack pointer to the the address of
choosen sector , as the first address is the MSP and then assign the second address
which is the reset handler to function pointer and resets the system to its initial
state then calls that function pointer which that starts tha app.
Note that: The program that the user fetch must change its flash start address in linker
script and change the offset of address of vector table in the start up file.
 **************************************************************************************** */
void BL_vStartUserApp(void)
{
	BlPrint_vPrintDebug((uint8*) "Start user app \r\n");

	/*Pointer to function to hold address of reset handler of user APP*/
	void(*UserApp_ResetHandler)(void);

	/*First byte in memory is MSP following by Reset handler*/
	/*Configure main stack pointer by reading value after where the bootloader kept*/
	uint32 UserApp_MSP_Value = (*(volatile uint32*)USER_APP_BASE_ADDRESS);

	/* Check if it has valid stack pointer in the RAM */
	if(0x20000000 != (UserApp_MSP_Value & 0x20000000))
	{
		BlPrint_vPrintDebug((uint8*) "User APP MSP is not valid \r\n");
		return;
	}

	BlPrint_vPrintDebug((uint8*) "User APP MSP value: %#x \r\n",UserApp_MSP_Value);

	/*Set main stack pointer where the user APP is */
	__set_MSP(UserApp_MSP_Value);


	/*Get user app reset handler*/
	uint32 UserApp_ResetHandler_Value = (*(volatile uint32*)(USER_APP_BASE_ADDRESS + 4));

	/*Send reset handler on debug port*/
	BlPrint_vPrintDebug((uint8*) "User APP reset handler is %#x \r\n",UserApp_ResetHandler_Value);

	/*Initialize function pointer with the reset handler of user APP*/
	UserApp_ResetHandler = (void*)UserApp_ResetHandler_Value;

	/* Reallocate vector table */
	SCB->VTOR = USER_APP_BASE_ADDRESS;

	/*Start the User APP*/
	UserApp_ResetHandler();
}




/* ***************************************************************************************
Function   : BL_RSTR_SYS
Parameters : void
Return     : void
Job : Calls rsest handler of the program
 **************************************************************************************** */
static void BL_RSTR_SYS(void)
{
	/*Pointer to function to hold address of reset handler of program*/
	void(*Program_ResetHandler)(void);

	/*First byte in memory is MSP following by Reset handler*/
	uint32 Program_MSP_Value = (*(volatile uint32*)BL_BASE_ADDRESS);

	/*Set main stack pointer where the user app is */
	__set_MSP(Program_MSP_Value);

	/*Get user APP reset handler*/
	uint32 Program_ResetHandler_Value = (*(volatile uint32*)(BL_BASE_ADDRESS + 4));

	/*Initialize function pointer with the reset handler of program*/
	Program_ResetHandler = (void*)Program_ResetHandler_Value;


	/*Start the User app*/
	Program_ResetHandler();

}
