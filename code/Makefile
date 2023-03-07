###############################################################################
###############################################################################
#
# Author:	Jesus Rafael Rijo Candelario
# Date:		02/06/2023
# Course:	CSC 415: Advanced Graphics and Simulation (Spring 2023)
# Instructor:	Dr. A. Pounds
#
# Description:  Makefile to build the window manager project.
#
###############################################################################
###############################################################################

# Defining flags.
CC = g++
LIBS = Utils.cpp -lglfw -lGL -lGLEW ../SOIL2/libsoil2.a

# Defining resulting files.
all: driver

# Program to change the view.
driver: main.cpp
	$(CC) main.cpp  $(LIBS)
	mv a.out driver

# Commands to remove old executable and object files.
pristine:
	rm driver
