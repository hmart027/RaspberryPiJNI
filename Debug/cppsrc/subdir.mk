################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cppsrc/i2cJNI.cpp 

OBJS += \
./cppsrc/i2cJNI.o 

CPP_DEPS += \
./cppsrc/i2cJNI.d 


# Each subdirectory must supply rules for building sources it contributes
cppsrc/%.o: ../cppsrc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/usr/lib/jvm/jdk1.8.0_91/include -I/usr/lib/jvm/jdk1.8.0_91/include/linux -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


