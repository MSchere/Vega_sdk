################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/include" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/utilities" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/config/include/public" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/board" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/drivers" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/portable/GCC/RISCY" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


