#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

# Add your Source files to this variable
SOURCES = main.c \
	  memory.c \
	  startup_msp432p401r_gcc.c \
	  system_msp432p401r.c \
	  interrupts_msp432p401r_gcc.c

# Add your include paths to this variable
INCLUDES = ../include/CMSIS/cmsis_gcc.h \
	   ../include/CMSIS/core_cm4.h \
	   ../include/CMSIS/core_cmFunc.h \
	   ../include/CMSIS/core_cmInstr.h \
	   ../include/CMSIS/core_cmSimd.h \
	   ../include/common/memory.h \
	   ../include/common/platform.h \
	   ../include/msp432/msp432p401r.h \
	   ../include/msp432/msp_compatibility.h \
	   ../include/msp432/system_msp432p401r.h


