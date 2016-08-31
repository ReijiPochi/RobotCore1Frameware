################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/Modules/Bluetooth.c \
..\src/Modules/LED.c \
..\src/Modules/Motor.c 

C_DEPS += \
./src/Modules/Bluetooth.d \
./src/Modules/LED.d \
./src/Modules/Motor.d 

OBJS += \
./src/Modules/Bluetooth.obj \
./src/Modules/LED.obj \
./src/Modules/Motor.obj 


# Each subdirectory must supply rules for building sources it contributes
src/Modules/%.obj: ../src/Modules/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

