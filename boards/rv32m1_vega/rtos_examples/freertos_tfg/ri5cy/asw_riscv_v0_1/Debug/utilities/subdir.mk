################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_debug_console.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_io.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_log.c \
C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/fsl_debug_console.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_debug_console.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_io.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_io.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_log.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_log.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_str.o: C:/Vega/rv32m1_sdk_riscv/devices/RV32M1/utilities/fsl_str.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


