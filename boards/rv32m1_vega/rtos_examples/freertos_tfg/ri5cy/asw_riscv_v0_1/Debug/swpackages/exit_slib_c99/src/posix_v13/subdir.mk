################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../swpackages/exit_slib_c99/src/posix_v13/exit_iface.c 

OBJS += \
./swpackages/exit_slib_c99/src/posix_v13/exit_iface.o 

C_DEPS += \
./swpackages/exit_slib_c99/src/posix_v13/exit_iface.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/exit_slib_c99/src/posix_v13/%.o: ../swpackages/exit_slib_c99/src/posix_v13/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


