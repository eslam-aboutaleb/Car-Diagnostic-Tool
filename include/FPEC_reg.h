#ifndef FPEC_REG_H_
#define FPEC_REG_H_


#define FPEC_BASE_ADDRESS									(0x40022000)

#define OPTION_BYTE_BASE_ADDRESS   		 					(0x1FFFF800)



typedef struct
{
	volatile uint32 ACR;
	volatile uint32 KEYR;
	volatile uint32 OPTKEYR;
	volatile uint32 SR;
	volatile uint32 CR;
	volatile uint32 AR;
	uint32 RESERVED;
	volatile uint32 OBR;
	volatile uint32 WRPR;

}FPEC_TypeDef;

typedef struct
{
	volatile uint16 RDP;
	volatile uint16 USER;
	volatile uint16 DATA0;
	volatile uint16 DATA1;
	volatile uint16 WRPR[4];

}OB_TypeDef;


#define FPEC											((FPEC_TypeDef	*)	FPEC_BASE_ADDRESS)
#define OB												((OB_TypeDef   	*)	OPTION_BYTE_BASE_ADDRESS)

#endif /* FPEC_REG_H_ */
