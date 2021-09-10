################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/edroombp_free_rtos.cpp 

OBJS += \
./swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/edroombp_free_rtos.o 

CPP_DEPS += \
./swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/edroombp_free_rtos.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/%.o: ../swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


