# Simple makefile for compiling and running a C program
# from a Mac terminal with gcc
# Ulrik Eklund 2013-10-30

C_COMPILER=gcc
TARGET_BASE1=main
TARGET_BASE2=test2

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif

TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)

# SRC_FILES1= src/01ArrayInit.c
# SRC_FILES1= src/02UsingIf.c
# SRC_FILES1= src/03TypeConversion.c
# SRC_FILES1= src/04OutOfBounds.c
# SRC_FILES1= src/05MultipleActions.c 
SRC_FILES1= src/main.c src/LockStateMachine.c

INC_DIRS=-Isrc -I../src

# SYMBOLS=-DTEST
SYMBOLS=

ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET) ; mkdir -p build
else ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* && del /F /Q $(TARGET1)
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET1) 
endif

all: clean default

default:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)	

	./$(TARGET1)

clean:
	$(CLEANUP)

	

