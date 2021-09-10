################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/system_RV32M1_ri5cy.c 

S_UPPER_SRCS += \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/gcc/startup_RV32M1_ri5cy.S 

OBJS += \
./startup/startup_RV32M1_ri5cy.o \
./startup/system_RV32M1_ri5cy.o 

C_DEPS += \
./startup/system_RV32M1_ri5cy.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_RV32M1_ri5cy.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/gcc/startup_RV32M1_ri5cy.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/system_RV32M1_ri5cy.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/system_RV32M1_ri5cy.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


