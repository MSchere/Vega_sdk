################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/xprintf_iface_v1.c 

OBJS += \
./swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/xprintf_iface_v1.o 

C_DEPS += \
./swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/xprintf_iface_v1.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/%.o: ../swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


