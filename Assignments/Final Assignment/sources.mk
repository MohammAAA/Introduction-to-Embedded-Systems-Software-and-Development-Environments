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

ifeq ($(PLATFORM),MSP432)
	SOURCES = src/*.c

	INCLUDES = ../include/CMSIS \
	   	../include/common \
	   	../include/msp432

else
	SOURCES = src/main.c \
		  src/memory.c \
		  src/data.c \
		  src/stats.c \
		  src/course1.c

	INCLUDES = ../include/common
endif
