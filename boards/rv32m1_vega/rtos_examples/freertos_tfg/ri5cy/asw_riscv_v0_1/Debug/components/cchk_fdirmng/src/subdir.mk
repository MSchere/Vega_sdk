################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/cchk_fdirmng/src/CCHK_FDIRMngB.cpp \
../components/cchk_fdirmng/src/CCHK_FDIRMngS.cpp 

OBJS += \
./components/cchk_fdirmng/src/CCHK_FDIRMngB.o \
./components/cchk_fdirmng/src/CCHK_FDIRMngS.o 

CPP_DEPS += \
./components/cchk_fdirmng/src/CCHK_FDIRMngB.d \
./components/cchk_fdirmng/src/CCHK_FDIRMngS.d 


# Each subdirectory must supply rules for building sources it contributes
components/cchk_fdirmng/src/%.o: ../components/cchk_fdirmng/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


