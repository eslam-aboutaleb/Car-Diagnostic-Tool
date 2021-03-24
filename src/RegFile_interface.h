
#ifndef REGFILE_INTERFACE_H_
#define REGFILE_INTERFACE_H_


__attribute__( ( always_inline ) ) static inline void __enable_irq(void)
{
  asm volatile ("cpsie i" : : : "memory");
}

__attribute__( ( always_inline ) ) static inline void __disable_irq(void)
{
  asm volatile ("cpsid i" : : : "memory");
}




#endif /* REGFILE_INTERFACE_H_ */
