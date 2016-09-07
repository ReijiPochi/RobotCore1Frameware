################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/startup/dbsct.c \
..\src/startup/hardware_setup.c \
..\src/startup/reset_program.c \
..\src/startup/sbrk.c 

C_DEPS += \
./src/startup/dbsct.d \
./src/startup/hardware_setup.d \
./src/startup/reset_program.d \
./src/startup/sbrk.d 

OBJS += \
./src/startup/dbsct.obj \
./src/startup/hardware_setup.obj \
./src/startup/reset_program.obj \
./src/startup/sbrk.obj 


# Each subdirectory must supply rules for building sources it contributes
src/startup/%.obj: ../src/startup/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -optimize=0 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

