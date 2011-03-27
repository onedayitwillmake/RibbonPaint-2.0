################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FadeOutText.cpp \
../src/IKLine.cpp \
../src/RibbonPaint.cpp \
../src/Segment.cpp 

OBJS += \
./src/FadeOutText.o \
./src/IKLine.o \
./src/RibbonPaint.o \
./src/Segment.o 

CPP_DEPS += \
./src/FadeOutText.d \
./src/IKLine.d \
./src/RibbonPaint.d \
./src/Segment.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/onedayitwillmake/GIT/LIBRARY/Cinder/boost -I/Users/onedayitwillmake/GIT/LIBRARY/Cinder/include -I"/Users/onedayitwillmake/GIT/RibbonPaint/include" -I/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -O0 -g -Wall -c -fmessage-length=0 -arch i386 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


