################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/port.c 

S_UPPER_SRCS += \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S 

OBJS += \
./freertos/portable/port.o \
./freertos/portable/portASM.o 

C_DEPS += \
./freertos/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/portable/port.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/portable/portASM.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


