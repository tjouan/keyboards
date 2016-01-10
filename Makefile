ARDUINO_DIR		= $(HOME)/usr/arduino/arduino-1.6.7
AVR_TOOLS_PATH		= /usr/local/bin
ARDUINO_PORT		= /dev/cuaU1
BOARD_TAG		= uno
ARDUINO_SKETCHBOOK	= .

include $(HOME)/src/hw/Arduino-Makefile/Arduino.mk
