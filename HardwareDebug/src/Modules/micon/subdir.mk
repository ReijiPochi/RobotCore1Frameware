################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/Modules/micon/interrupt_handlers.c \
..\src/Modules/micon/vector_table.c 

C_DEPS += \
./src/Modules/micon/interrupt_handlers.d \
./src/Modules/micon/vector_table.d 

OBJS += \
./src/Modules/micon/interrupt_handlers.obj \
./src/Modules/micon/vector_table.obj 


# Each subdirectory must supply rules for building sources it contributes
src/Modules/micon/%.obj: ../src/Modules/micon/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

