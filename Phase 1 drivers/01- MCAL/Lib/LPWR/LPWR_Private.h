/*
 * LPWR_Private.h
 *
 *  Created on: Dec 23, 2020
 *      Author: Abeer
 */

#ifndef LPWR_PRIVATE_H_
#define LPWR_PRIVATE_H_

typedef struct
{
	u32 CPUID;
	u32 ICSR;
	u32 VTOR;
	u32 AIRCR;
	u32 SCR;
	u32 CCR;
	u32 SHP[12U];
	u32 SHCSR;
	u32 CFSR;
	u32 HFSR;
	u32 DFSR;
	u32 MMFAR;
	u32 BFAR;
	u32 AFSR;
	u32 PFR[2U];
	u32 DFR;
	u32 ADR;
	u32 MMFR[4U];
	u32 ISAR[5U];
	u32 RESERVED0[5U];
	u32 CPACR;
} SCB_Type;

typedef struct
{
	u32 CR;
	u32 CSR;
} PWR_TypeDef;


#define MSCB          ((SCB_Type*) 0xE000ED00 )
#define MPWR          ((PWR_TypeDef*) 0xE000ED00 )

#define  SLEEPDEEP                   2
#define SLEEPONEXIT					 1

#define  BDDS						 1
#define  CWUF						 2
#define	 CSBF						 3
#define EWUP			           	 8
#define WUF			             	 0
#define LPDS		             	 0


#endif /* LPWR_PRIVATE_H_ */
