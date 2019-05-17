################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/mathformat.cpp \
../src/quanergym8.cpp \
../src/socket.cpp \
../src/test_m8_thread.cpp \
../src/udp.cpp \
../src/visualizer_module.cpp 

OBJS += \
./src/main.o \
./src/mathformat.o \
./src/quanergym8.o \
./src/socket.o \
./src/test_m8_thread.o \
./src/udp.o \
./src/visualizer_module.o 

CPP_DEPS += \
./src/main.d \
./src/mathformat.d \
./src/quanergym8.d \
./src/socket.d \
./src/test_m8_thread.d \
./src/udp.d \
./src/visualizer_module.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/mueavi-pc-01/HumanDrive/Quanergy/quanergy_client-master/include/ -I/home/mueavi-pc-01/HumanDrive/VTK/VTK-8.1.1/install/include/vtk-8.1 -I/usr/include/eigen3 -I/home/mueavi-pc-01/HumanDrive/PCL/pcl-pcl-1.8.1/install/include/pcl-1.8 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


