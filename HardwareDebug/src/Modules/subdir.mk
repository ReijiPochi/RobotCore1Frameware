################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/Modules/AnalogIN.c \
..\src/Modules/AnalogOUT.c \
..\src/Modules/Battery.c \
..\src/Modules/Bluetooth.c \
..\src/Modules/Buzzer.c \
..\src/Modules/LED.c \
..\src/Modules/Motor.c \
..\src/Modules/Timer.c 

C_DEPS += \
./src/Modules/AnalogIN.d \
./src/Modules/AnalogOUT.d \
./src/Modules/Battery.d \
./src/Modules/Bluetooth.d \
./src/Modules/Buzzer.d \
./src/Modules/LED.d \
./src/Modules/Motor.d \
./src/Modules/Timer.d 

OBJS += \
./src/Modules/AnalogIN.obj \
./src/Modules/AnalogOUT.obj \
./src/Modules/Battery.obj \
./src/Modules/Bluetooth.obj \
./src/Modules/Buzzer.obj \
./src/Modules/LED.obj \
./src/Modules/Motor.obj \
./src/Modules/Timer.obj 


# Each subdirectory must supply rules for building sources it contributes
src/Modules/%.obj: ../src/Modules/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.
