################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_lpuart_freertos.c 

OBJS += \
./drivers/freertos/fsl_lpuart_freertos.o 

C_DEPS += \
./drivers/freertos/fsl_lpuart_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/freertos/fsl_lpuart_freertos.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_lpuart_freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


