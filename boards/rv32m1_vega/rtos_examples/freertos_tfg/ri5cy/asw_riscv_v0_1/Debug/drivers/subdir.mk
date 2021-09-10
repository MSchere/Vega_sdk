################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_clock.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_common.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_gpio.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_lpuart.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_msmc.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_msmc.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_msmc.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/fsl_clock.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_common.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_common.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_gpio.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_lpuart.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_lpuart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_msmc.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/drivers/fsl_msmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


