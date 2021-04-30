################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Convolver.cpp \
../src/Convolver2.cpp \
../src/FFT.cpp \
../src/main.cpp 

O_SRCS += \
../src/Convolver.o \
../src/Debug.o \
../src/FFT.o \
../src/main.o 

OBJS += \
./src/Convolver.o \
./src/Convolver2.o \
./src/FFT.o \
./src/main.o 

CPP_DEPS += \
./src/Convolver.d \
./src/Convolver2.d \
./src/FFT.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


