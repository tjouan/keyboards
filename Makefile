ARDUINO_DIR		= $(HOME)/usr/arduino/arduino-1.6.7
#BOARDS_TXT		= $(ARDUINO_DIR)/hardware/arduino/avr/boards.txt
AVR_TOOLS_PATH		= /usr/local/bin
ARDUINO_PORT		= /dev/cuaU1
BOARD_TAG		= micro
ARDUINO_SKETCHBOOK	= .
USER_LIB_PATH		= lib
CPPFLAGS		= -Iinclude
CXXFLAGS		= -std=c++11
ARDUINO_LIBS		= HID
ARDUINO_LIBS		+= Keyboard

include $(HOME)/src/firmwares/Arduino-Makefile/Arduino.mk
