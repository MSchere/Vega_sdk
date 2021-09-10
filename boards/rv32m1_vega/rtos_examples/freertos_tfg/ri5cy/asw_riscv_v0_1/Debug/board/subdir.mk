################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/ri5cy/board.c \
C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/ri5cy/clock_config.c \
C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/board.o: C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/ri5cy/board.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/clock_config.o: C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/ri5cy/clock_config.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/pin_mux.o: C:/Vega/rv32m1_sdk_riscv/boards/rv32m1_vega/rtos_examples/freertos_tfg/pin_mux.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


