################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pswpackages/freertosapi_freertos_x86_v1/src/freertos_def.c 

OBJS += \
./pswpackages/freertosapi_freertos_x86_v1/src/freertos_def.o 

C_DEPS += \
./pswpackages/freertosapi_freertos_x86_v1/src/freertos_def.d 


# Each subdirectory must supply rules for building sources it contributes
pswpackages/freertosapi_freertos_x86_v1/src/%.o: ../pswpackages/freertosapi_freertos_x86_v1/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


