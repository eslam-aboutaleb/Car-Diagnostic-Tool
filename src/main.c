#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "BlPrint_interface.h"
#include "Bootloader_interface.h"
#include "ESP_interface.h"

void RCC_Init(void)
{
	/*Configure system clock*/
	RCC_Config_t RCC_Copy;
	RCC_Copy.ClockSource = RCC_HSI;
	RCC_Copy.Prescaler.ABP1_Prescaler = APB1_NOT_DEVIDED;
	RCC_Copy.Prescaler.ABP2_Prescaler = APB2_NOT_DEVIDED;
	RCC_Copy.Prescaler.AHB_Prescaler  = AHB_NOT_DEVIDED;
	RCC_vClockInit(&RCC_Copy);

	/*Initialize GPIOA peripheral*/
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_GPIOA_CLOCK,RCC_ENABLE_PERIPHERAL);
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_GPIOB_CLOCK,RCC_ENABLE_PERIPHERAL);
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_USART1_CLOCK,RCC_ENABLE_PERIPHERAL);
	RCC_vSetCLKPeripheral(RCC_AHB_BUS,RCC_FSMC_CLOCK,RCC_ENABLE_PERIPHERAL);

}

void main (void)
{
	RCC_Init();
	ESP_xInit();
	BL_vHandleMEMWriteWIFICMD();
	BL_vStartUserApp();
	while(1)
	{

	}
}
