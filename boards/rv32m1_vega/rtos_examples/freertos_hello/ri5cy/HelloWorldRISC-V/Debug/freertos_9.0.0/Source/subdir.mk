################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos_9.0.0/Source/croutine.c \
../freertos_9.0.0/Source/event_groups.c \
../freertos_9.0.0/Source/list.c \
../freertos_9.0.0/Source/queue.c \
../freertos_9.0.0/Source/tasks.c \
../freertos_9.0.0/Source/timers.c 

OBJS += \
./freertos_9.0.0/Source/croutine.o \
./freertos_9.0.0/Source/event_groups.o \
./freertos_9.0.0/Source/list.o \
./freertos_9.0.0/Source/queue.o \
./freertos_9.0.0/Source/tasks.o \
./freertos_9.0.0/Source/timers.o 

C_DEPS += \
./freertos_9.0.0/Source/croutine.d \
./freertos_9.0.0/Source/event_groups.d \
./freertos_9.0.0/Source/list.d \
./freertos_9.0.0/Source/queue.d \
./freertos_9.0.0/Source/tasks.d \
./freertos_9.0.0/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos_9.0.0/Source/%.o: ../freertos_9.0.0/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/include" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/utilities" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/config/include/public" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/board" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/RV32M1/drivers" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/freertos_9.0.0/Source/portable/GCC/RISCY" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


