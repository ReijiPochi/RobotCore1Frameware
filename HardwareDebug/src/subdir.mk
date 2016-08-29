################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\src/RobotCore1Framework.cpp 

C_SRCS += \
..\src/dbsct.c \
..\src/interrupt_handlers.c \
..\src/reset_program.c \
..\src/sbrk.c \
..\src/vector_table.c 

C_DEPS += \
./src/dbsct.d \
./src/interrupt_handlers.d \
./src/reset_program.d \
./src/sbrk.d \
./src/vector_table.d 

OBJS += \
./src/RobotCore1Framework.obj \
./src/dbsct.obj \
./src/interrupt_handlers.obj \
./src/reset_program.obj \
./src/sbrk.obj \
./src/vector_table.obj 

CPP_DEPS += \
./src/RobotCore1Framework.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.cpp src/cpp.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=cpp   -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=cpp -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/%.obj: ../src/%.c src/c.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c   -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_3_0/include"  -debug -isa=rxv1 -fpu -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

