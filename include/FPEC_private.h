#ifndef FPEC_PRIVATE_H_
#define FPEC_PRIVATE_H_

#define FPEC_FLASG_WRITE												0
#define FPEC_FLASG_ERASE												1

#define FPEC_IS_VALID_PAGE(PAGE)										( PAGE <= FLASH_PAGE63 )
#define FPEC_IS_BUSY()													while(BIT_IS_SET(FPEC->SR , FPEC_BUSY_FLAG))

#define FPEC_IS_VALID_ADDRESS(ADDRESS)									((ADDRESS >= FPEC_FLASH_START_ADDRESS)||\
																		(ADDRESS <= FPEC_FLASH_END_ADDRESS))

#define FPEC_IS_VALID_LATENCY(LATENCY) 									(((LATENCY) == FLASH_LATENCY_0) || \
																	   	((LATENCY) == FLASH_LATENCY_1) || \
																		((LATENCY) == FLASH_LATENCY_2))


#define FLASH_PAGE_SIZE													1024

#define FLASH_KEY1														(0x45670123)
#define FLASH_KEY2														(0xCDEF89AB)



#define FPEC_EOP_FLAG													5
#define FPEC_WRITE_PROTECTION_ERR_FLAG									4
#define FPEC_PROGRAMMING_ERR_FLAG										2
#define FPEC_BUSY_FLAG													0


#define ACR_LATENCY_Mask         										((uint32)0x00000038)

static void FPEC_vUnLock(void);
static void FPEC_vLock(void);
static void FPEC_vUnLockOptionByte(void);
static void FPEC_vLockOptionByte(void);


#endif /* FPEC_PRIVATE_H_ */
