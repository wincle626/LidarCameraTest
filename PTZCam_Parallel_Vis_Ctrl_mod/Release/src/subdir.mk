################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/curl.cpp \
../src/key.cpp \
../src/main.cpp \
../src/ptzcam.cpp 

OBJS += \
./src/curl.o \
./src/key.o \
./src/main.o \
./src/ptzcam.o 

CPP_DEPS += \
./src/curl.d \
./src/key.d \
./src/main.d \
./src/ptzcam.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I/home/mueavi-pc-01/HumanDrive/OpenCV/opencv-3.4.1/install/include -I/usr/include/eigen3 -I/home/mueavi-pc-01/HumanDrive/VTK/VTK-8.1.1/install/include/vtk-8.1 -I/home/mueavi-pc-01/HumanDrive/PCL/pcl-pcl-1.8.1/install/include/pcl-1.8 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


