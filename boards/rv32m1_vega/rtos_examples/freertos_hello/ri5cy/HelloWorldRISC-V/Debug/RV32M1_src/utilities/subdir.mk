################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RV32M1_src/utilities/fsl_debug_console.c \
../RV32M1_src/utilities/fsl_io.c \
../RV32M1_src/utilities/fsl_log.c \
../RV32M1_src/utilities/fsl_str.c 

OBJS += \
./RV32M1_src/utilities/fsl_debug_console.o \
./RV32M1_src/utilities/fsl_io.o \
./RV32M1_src/utilities/fsl_log.o \
./RV32M1_src/utilities/fsl_str.o 

C_DEPS += \
./RV32M1_src/utilities/fsl_debug_console.d \
./RV32M1_src/utilities/fsl_io.d \
./RV32M1_src/utilities/fsl_log.d \
./RV32M1_src/utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
RV32M1_src/utilities/%.o: ../RV32M1_src/utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/include" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/utilities" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/config/include/public" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/board" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/drivers" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/portable/GCC/RISCY" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


