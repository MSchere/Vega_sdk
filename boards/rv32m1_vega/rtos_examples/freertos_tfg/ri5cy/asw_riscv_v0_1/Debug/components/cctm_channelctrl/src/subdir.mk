################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/cctm_channelctrl/src/CCTM_ChannelCtrlB.cpp \
../components/cctm_channelctrl/src/CCTM_ChannelCtrlS.cpp 

OBJS += \
./components/cctm_channelctrl/src/CCTM_ChannelCtrlB.o \
./components/cctm_channelctrl/src/CCTM_ChannelCtrlS.o 

CPP_DEPS += \
./components/cctm_channelctrl/src/CCTM_ChannelCtrlB.d \
./components/cctm_channelctrl/src/CCTM_ChannelCtrlS.d 


# Each subdirectory must supply rules for building sources it contributes
components/cctm_channelctrl/src/%.o: ../components/cctm_channelctrl/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


