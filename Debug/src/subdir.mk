################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BLPrint_program.c \
../src/BLServices_program.c \
../src/Bootloader_program.c \
../src/ComM_program.c \
../src/ESP_program.c \
../src/FPEC_program.c \
../src/GPIO_program.c \
../src/Led_program.c \
../src/RCC_program.c \
../src/SW_program.c \
../src/SYSTICK_program.c \
../src/USART_program.c \
../src/Util_String_program.c \
../src/main.c 

OBJS += \
./src/BLPrint_program.o \
./src/BLServices_program.o \
./src/Bootloader_program.o \
./src/ComM_program.o \
./src/ESP_program.o \
./src/FPEC_program.o \
./src/GPIO_program.o \
./src/Led_program.o \
./src/RCC_program.o \
./src/SW_program.o \
./src/SYSTICK_program.o \
./src/USART_program.o \
./src/Util_String_program.o \
./src/main.o 

C_DEPS += \
./src/BLPrint_program.d \
./src/BLServices_program.d \
./src/Bootloader_program.d \
./src/ComM_program.d \
./src/ESP_program.d \
./src/FPEC_program.d \
./src/GPIO_program.d \
./src/Led_program.d \
./src/RCC_program.d \
./src/SW_program.d \
./src/SYSTICK_program.d \
./src/USART_program.d \
./src/Util_String_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


