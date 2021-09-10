################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service1.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service12.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service128.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service17.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service19.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service20.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service21.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service3.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service5.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service6.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service9.cpp \
../swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_services.cpp 

OBJS += \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service1.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service12.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service128.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service17.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service19.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service20.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service21.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service3.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service5.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service6.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service9.o \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_services.o 

CPP_DEPS += \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service1.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service12.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service128.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service17.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service19.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service20.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service21.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service3.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service5.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service6.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_service9.d \
./swpackages/icuasw_pus_services_slib_head/src/icuasw_pus_services.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/icuasw_pus_services_slib_head/src/%.o: ../swpackages/icuasw_pus_services_slib_head/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


