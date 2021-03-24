/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ComM_private.h		                                             */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef COMM_PRIVATE_H_
#define COMM_PRIVATE_H_

/* **************************************************************************************** */
/* Error Checkers */
/* **************************************************************************************** */

#define COMM_IS_VALID_COM_PROTOCOL(COM)									((COM == COM_USART_ID)||\
																		(COM == COM_SPI_ID)||\
																		(COM == COM_I2C_ID))


#endif /* COMM_PRIVATE_H_ */
