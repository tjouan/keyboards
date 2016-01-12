require 'rake/clean'

ARDUINO_DIR = "#{ENV['HOME']}/usr/arduino/arduino-1.6.7".freeze
BUILD_DIR   = 'build'.freeze
SRC_DIR     = 'src'.freeze
SRCS        = FileList['src/*.cpp']
OBJS        = SRCS.pathmap("%{^#{SRC_DIR},#{BUILD_DIR}}X.o")
ELF_FILE    = "#{BUILD_DIR}/main.elf".freeze
HEX_FILE    = "#{BUILD_DIR}/main.hex".freeze
CC          = "avr-gcc".freeze
CXX         = "avr-g++".freeze
OBJCOPY     = "avr-objcopy".freeze
SIZE        = "avr-size".freeze
OPTIONS     = %w[
  -DF_CPU=16000000L
  -DARDUINO=167
  -DARDUINO_ARCH_AVR
  -D__PROG_TYPES_COMPAT__
].freeze
INCLUDES    = %W[
  -I#{ARDUINO_DIR}/hardware/arduino/avr/cores/arduino
  -I#{ARDUINO_DIR}/hardware/arduino/avr/variants/standard
]
CPPFLAGS    = %W[
  -MMD -mmcu=atmega328p
  -Wall -ffunction-sections -fdata-sections -Os -fno-exceptions
].freeze
LDFLAGS     = %w[-mmcu=atmega328p -Wl,--gc-sections -Os]
# FIXME: remove hardcoded libcore (built with arduino-mk for now)
LIBS        = %w[libcore.a -lc -lm].freeze

OBJ_TO_SRC = proc do |t|
  t.pathmap("%{^#{BUILD_DIR},#{SRC_DIR}}X.cpp")
end

CLEAN.include "#{BUILD_DIR}/*"


file HEX_FILE => ELF_FILE do |t|
  sh "#{SIZE} #{ELF_FILE}"
  sh "#{OBJCOPY} -O ihex -R .eeprom #{ELF_FILE} #{t.name}"
end

file ELF_FILE => OBJS do |t|
  sh "#{CC} #{LDFLAGS.join ' '} -o #{t.name} #{t.prerequisites.join ' '} #{LIBS.join ' '}"
end

rule '.o' => OBJ_TO_SRC do |t|
  args = [*CPPFLAGS, *OPTIONS, *INCLUDES].join ' '
  sh "#{CXX} #{args} #{t.source} -c -o #{t.name}"
end


task default: :build
#task all: %i[build install]

desc 'Build the hex file'
task build: HEX_FILE
