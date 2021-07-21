################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos_9.0.0/Source/portable/GCC/RISCY/port.c 

S_UPPER_SRCS += \
../freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S 

OBJS += \
./freertos_9.0.0/Source/portable/GCC/RISCY/port.o \
./freertos_9.0.0/Source/portable/GCC/RISCY/portASM.o 

S_UPPER_DEPS += \
./freertos_9.0.0/Source/portable/GCC/RISCY/portASM.d 

C_DEPS += \
./freertos_9.0.0/Source/portable/GCC/RISCY/port.d 


# Each subdirectory must supply rules for building sources it contributes
freertos_9.0.0/Source/portable/GCC/RISCY/%.o: ../freertos_9.0.0/Source/portable/GCC/RISCY/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/include" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/utilities" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/config/include/public" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/board" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/drivers" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/portable/GCC/RISCY" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos_9.0.0/Source/portable/GCC/RISCY/%.o: ../freertos_9.0.0/Source/portable/GCC/RISCY/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


