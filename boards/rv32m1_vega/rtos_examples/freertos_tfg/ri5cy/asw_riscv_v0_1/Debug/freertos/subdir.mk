################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/croutine.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/event_groups.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/MemMang/heap.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/list.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/queue.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/tasks.c \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/timers.c 

OBJS += \
./freertos/croutine.o \
./freertos/event_groups.o \
./freertos/heap.o \
./freertos/list.o \
./freertos/queue.o \
./freertos/tasks.o \
./freertos/timers.o 

C_DEPS += \
./freertos/croutine.d \
./freertos/event_groups.d \
./freertos/heap.d \
./freertos/list.d \
./freertos/queue.d \
./freertos/tasks.d \
./freertos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/croutine.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/event_groups.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/heap.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/MemMang/heap.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/list.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/queue.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/tasks.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

freertos/timers.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


