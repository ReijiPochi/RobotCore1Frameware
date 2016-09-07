################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp src/*.src src/*.p src/*.pp src/*.mrc *.bls *.libelf *.lbk *.abs *.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/startup/subdir.mk
-include src/matSystem/subdir.mk
-include src/UserApplication/subdir.mk
-include src/Modules/micon/subdir.mk
-include src/Modules/subdir.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CP_DEPS)),)
-include $(CP_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CP_UPPER_DEPS)),)
-include $(CP_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(ABS_DEPS)),)
-include $(ABS_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
CONVERTOR_OUTPUT_OUTPUTS += \
RobotCore1Framework.mot \

LINKER_OUTPUT_OUTPUTS += \
RobotCore1Framework.abs \

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
RobotCore1Framework.lib \

# All Target
all: RobotCore1Framework.mot
	@echo 'Build complete.'

# Tool invocations
RobotCore1Framework.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Converter'
	rlink   "F:\GitHub\RobotCore1Frameware\HardwareDebug\RobotCore1Framework.abs" -form=stype  -output="F:\GitHub\RobotCore1Frameware\HardwareDebug\RobotCore1Framework.mot"
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

RobotCore1Framework.abs: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rlink  -subcommand="LinkerSubCommand.tmp"  -library="F:\GitHub\ROBOTC~1\HARDWA~2\RobotCore1Framework.lib" -list="RobotCore1Framework.map" -show -nooptimize -debug -output="F:\GitHub\RobotCore1Frameware\HardwareDebug\RobotCore1Framework.abs" -rom=D=R,D_1=R_1,D_2=R_2 -nocompress -nomessage -nologo
	@echo 'Finished building:'
	@echo.

RobotCore1Framework.lib:  
	@echo 'Invoking: Standard Library'
	lbgrx -head=runtime,stdio,stdlib -isa=rxv1 -fpu -output="RobotCore1Framework.lib"
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
	-$(RM) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS) 
	-rm -rf "src/startup"/*.obj "src/startup"/*.d "src/startup"/*.src "src/startup"/*.p "src/startup"/*.pp "src/startup"/*.mrc "src/startup"/*.prn
	-rm -rf "src/matSystem"/*.obj "src/matSystem"/*.d "src/matSystem"/*.src "src/matSystem"/*.p "src/matSystem"/*.pp "src/matSystem"/*.mrc "src/matSystem"/*.prn
	-rm -rf "src/UserApplication"/*.obj "src/UserApplication"/*.d "src/UserApplication"/*.src "src/UserApplication"/*.p "src/UserApplication"/*.pp "src/UserApplication"/*.mrc "src/UserApplication"/*.prn
	-rm -rf "src/Modules/micon"/*.obj "src/Modules/micon"/*.d "src/Modules/micon"/*.src "src/Modules/micon"/*.p "src/Modules/micon"/*.pp "src/Modules/micon"/*.mrc "src/Modules/micon"/*.prn
	-rm -rf "src/Modules"/*.obj "src/Modules"/*.d "src/Modules"/*.src "src/Modules"/*.p "src/Modules"/*.pp "src/Modules"/*.mrc "src/Modules"/*.prn
	-rm -rf "src"/*.obj "src"/*.d "src"/*.src "src"/*.p "src"/*.pp "src"/*.mrc "src"/*.prn
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-C:\Renesas\E2_STU~1\DEBUGC~1\RX\RX_CON~1.EXE RobotCore1Framework.abs RobotCore1Framework.x
	@echo.

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
