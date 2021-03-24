#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "FPEC_reg.h"
#include "FPEC_interface.h"
#include "FPEC_private.h"

Error_Status FLASH_xSetLatency(FPEC_Latency_t Copy_xFLASH_Latency)
{
  /* Check the parameters */
  ERROR_CHECK(FPEC_IS_VALID_LATENCY(Copy_xFLASH_Latency));

  /* CLEAR flash latency bits */
  FPEC->ACR &= ACR_LATENCY_Mask;

  /* Write the ACR register */
  FPEC->ACR |= Copy_xFLASH_Latency;

  return E_OK;
}

Error_Status FPEC_xPageErase(FPEC_FlashPage_t Copy_xPage)
{
	/*Variable to store  the function status*/
	Error_Status Local_xError_Status	=	E_OK;

	/* Temporary variable to calculate the Page Address*/
	uint32 Local_u32Temp = 0   ;

	/*check if is it page number*/
	if(FPEC_IS_VALID_PAGE(Copy_xPage)!=E_OK)
	{
		Local_xError_Status = E_NOK;
	}

	ERROR_CHECK(Local_xError_Status);

	/*wait for the busy flag before any operation*/
	FPEC_IS_BUSY();

	/*Unlock the Flash controller*/
	FPEC_vUnLock();

	/*Enable the page erase bit in the FPEC control Register*/
	SET_BIT(FPEC->CR , 1);

	/*the Page size == 1024KB starting from the Start of the flash(0x08000000)*/
	Local_u32Temp = ((Copy_xPage * FLASH_PAGE_SIZE) + FPEC_FLASH_START_ADDRESS);

	/*Put the Page Address in the the Flash address Register to Be deleted according to the data sheet*/
	FPEC->AR = Local_u32Temp ;

	/*Start the erase operation*/
	SET_BIT(FPEC->CR , 6);

	/*wait for the busy Flag till the operation finishes*/
	FPEC_IS_BUSY();

	/*Clear the end of operation (EOP) Flag in the status register*/
	SET_BIT(FPEC->SR , FPEC_EOP_FLAG);

	/*Clear the page erase  Activation bit*/
	CLEAR_BIT(FPEC->CR , 1);

	/*Lock the Flash again*/
	FPEC_vLock();


	return Local_xError_Status ;
}

void FPEC_vMassErase(void)
{
	/*wait for the busy flag before any operation*/
	FPEC_IS_BUSY();

	/*Unlock the Flash controller*/
	FPEC_vUnLock();

	/*Enable the Mass erase bit in the FPEC control Register*/
	SET_BIT(FPEC->CR , 2);

	/*Start the erase operation*/
	SET_BIT(FPEC->CR , 6);

	/*wait for the busy Flag till the operation finshs*/
	FPEC_IS_BUSY();
	/*Clear the end of operation(EOP) Flag in the status register*/
	SET_BIT(FPEC->SR , FPEC_EOP_FLAG);
	/*Clear the mass erase Activation bit*/
	CLEAR_BIT(FPEC->CR , 2);

	/*Lock the Flash again*/
	FPEC_vLock();
}


Error_Status FPEC_xProgrammHalfword(uint32 Copy_u32Address , uint16 Copy_xData)
{
	/*Temporary Variable to store  the function state*/
	Error_Status Local_xErrorStatus	=	E_OK;
	/*Check for the passed address*/
	Local_xErrorStatus	=	FPEC_IS_VALID_ADDRESS(Copy_u32Address);
	ERROR_CHECK(Local_xErrorStatus);

	/*wait for the busy flag before any operation*/
	FPEC_IS_BUSY();

	/*Unlock the Flash controller*/
	FPEC_vUnLock();

	/*GO into flash programming mode*/
	SET_BIT(FPEC->CR , 0);

	/*put the Data in the current address*/
	*((volatile uint16 *) Copy_u32Address) = Copy_xData;
	/*wait for the busy Flag till the operation finishes*/
	FPEC_IS_BUSY();

	/*Clear the end of operation(EOP) Flag in the status register*/
	SET_BIT(FPEC->SR , FPEC_EOP_FLAG);
	/*Step out from flash programming mode */
	CLEAR_BIT(FPEC->CR , 0);

	/*Lock the Flash again*/
	FPEC_vLock();

	/*return function state*/
	return Local_xErrorStatus ;

}

void FPEC_OB_RDPLevelConfig(FPEC_RDPLevel_t Copy_xRDPLevel)
{
	/*first store the read protection level before working */
	volatile FPEC_RDPLevel_t Temp_RDPLevel  = Copy_xRDPLevel;

	/*wait for the busy flag before any operation*/
	FPEC_IS_BUSY();
	/*Unlock the Flash controller*/
	FPEC_vUnLock();
	/*Unlock the Flash OptionByte controller*/
	FPEC_vUnLockOptionByte();

	/*Enable option byte erase bit*/
	SET_BIT(FPEC->CR, 5);

	/*Start the erase operation*/
	SET_BIT(FPEC->CR, 6);

	/*wait for the busy Flag till the operation finishes*/
	FPEC_IS_BUSY();

	/**then set the read protection level**/

	/*Disable the option byte erase option after erasing*/
	CLEAR_BIT(FPEC->CR, 5);
	/*Set the option programming mode*/
	SET_BIT(FPEC->CR, 4);
	/*Put the read protection level into the Option byte read protection register */
	OB->RDP = Temp_RDPLevel ;
	/*Clear the option programming mode*/
	CLEAR_BIT(FPEC->CR, 4);

	/*Lock the Flash again*/
	FPEC_vLock();

	/*Unlock the Flash OptionByte controller*/
	FPEC_vLockOptionByte();

}


/*
static helper function to unlock the option byte
 */
static void FPEC_vUnLockOptionByte(void)
{
	if(BIT_IS_CLEAR(FPEC->CR , 9))
	{
		FPEC->OPTKEYR = FLASH_KEY1 ;

		FPEC->OPTKEYR = FLASH_KEY2 ;
	}
	else
	{
		/*Do Nothing*/
	}

}

/*
static helper function to lock the option byte
 */
static void FPEC_vLockOptionByte(void)
{
	if(BIT_IS_SET(FPEC->CR , 9))
	{
		CLEAR_BIT(FPEC->CR , 9);
	}
	else
	{
		/*Do Nothing*/
	}

}


/*
static helper function to the  lock Flash interface
 */
static void FPEC_vUnLock(void)
{
	if(BIT_IS_SET(FPEC->CR , 7))
	{
		FPEC->KEYR = FLASH_KEY1 ;

		FPEC->KEYR = FLASH_KEY2 ;
	}
	else
	{
		/*Do Nothing*/
	}

}

/*
static helper function to the  lock Flash interface
 */
static void FPEC_vLock(void)
{
	if(BIT_IS_CLEAR(FPEC->CR , 7))
	{
		SET_BIT(FPEC->CR , 7);
	}
	else
	{
		/*Do Nothing*/
	}

}

