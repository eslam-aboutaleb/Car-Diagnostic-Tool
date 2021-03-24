/* ***********************************************************  */
/* Author : Eslam Ehab Aboutaleb                                */
/* Version: V01                                                 */
/* Date: 19-8-2020                                              */
/* ***********************************************************  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Led_interface.h"
#include "Led_config.h"
#include "Led_private.h"

/* ***********************************************************  */
/*Functions definitions*/
/* ***********************************************************  */

Error_Status LED_xInit(LED_t Copy_xLed, LED_State_t Copy_xState)
{
	if(E_OK	!=	LED_IS_VALID(Copy_xLed))
	{
		return E_NOK;
	}
	/* Set led as output*/
	GPIO_vInitPortPin(Leds[Copy_xLed].Led_Port,Leds[Copy_xLed].Led_Pin,GPIO_OUT);
	/* Set led state */
	LED_xSetState(Copy_xLed, Copy_xState);

	return E_OK;
}

/* ***********************************************************  */

Error_Status LED_xToggle(LED_t Copy_xLed)
{
	if(E_OK	!=	LED_IS_VALID(Copy_xLed))
	{
		return E_NOK;
	}

	/* Get led state */
	LED_State_t Local_xLedState = LED_OFF;
	LED_xGetState(Copy_xLed,&Local_xLedState);

	/* Toggle led */
	if (Local_xLedState == LED_ON)
	{
		LED_xSetState(Copy_xLed, LED_OFF);
	} else
	{
		LED_xSetState(Copy_xLed, LED_ON);
	}
	return E_OK;
}

/* ***********************************************************  */

Error_Status LED_xSetState(LED_t Copy_xLed, LED_State_t Copy_xState)
{
	if(E_OK	!=	LED_IS_VALID(Copy_xLed))
	{
		return E_NOK;
	}
	GPIO_vWritePortPin(Leds[Copy_xLed].Led_Port,Leds[Copy_xLed].Led_Pin,Copy_xState);
	return E_OK;
}

/* ***********************************************************  */

Error_Status LED_xGetState(LED_t Copy_xLed,LED_State_t *pxLedState)
{
	if(E_OK	!=	LED_IS_VALID(Copy_xLed))
	{
		return E_NOK;
	}

	*pxLedState = GPIO_u8ReadPortPin(Leds[Copy_xLed].Led_Port,Leds[Copy_xLed].Led_Pin);

	return E_OK;
}

