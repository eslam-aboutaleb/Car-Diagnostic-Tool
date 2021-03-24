/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/* ***********************************************************  */
/*LED data structures*/
/* ***********************************************************  */

typedef unsigned char LED_t;

typedef enum
{
	LED_OFF = 0,
	LED_ON  = 1
}LED_State_t;

#define LED_0													0
/* ***********************************************************  */
/*Functions prototypes*/
/* ***********************************************************  */

Error_Status LED_xInit(LED_t Copy_xLed, LED_State_t Copy_xState);
Error_Status LED_xToggle(LED_t Copy_xLed);
Error_Status LED_xGetState(LED_t Copy_xLed,LED_State_t *pxLedState);
Error_Status LED_xSetState(LED_t Copy_xLed, LED_State_t Copy_xState);



#endif /* LED_INTERFACE_H */
