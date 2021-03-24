/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */


#ifndef LED_CONFIG_H
#define LED_CONFIG_H

/* ***********************************************************  */

typedef GPIO_Port_t											LedPort_t;
typedef unsigned char										LedPin_t;

/* ***********************************************************  */

#define LEDS_N												1

typedef struct{
	LedPort_t	Led_Port;
	LedPin_t	Led_Pin;
}LedMap_st;

LedMap_st Leds[LEDS_N] ={
		{GPIOA,GPIO_PIN_0}
};


#endif /* LED_CONFIG_H */
