require 'rake/clean'

BUILD_DIR     = 'build'.freeze
PORT          = ENV.fetch 'PORT', '/dev/cuaU1'

ARDUINO_DIR   = "#{ENV['HOME']}/usr/arduino/arduino-1.6.7".freeze
CORE_SRC_DIR  = "#{ARDUINO_DIR}/hardware/arduino/avr/cores/arduino"
CORE_SRCS_C   = FileList["#{CORE_SRC_DIR}/*.c"]
CORE_SRCS_CPP = FileList["#{CORE_SRC_DIR}/*.cpp"]
CORE_SRCS_AS  = FileList["#{CORE_SRC_DIR}/*.S"]
CORE_SRCS     = CORE_SRCS_C + CORE_SRCS_CPP + CORE_SRCS_AS
CORE_OBJS     = CORE_SRCS.pathmap("%{^#{CORE_SRC_DIR},#{BUILD_DIR}/core}X.o")
CORE          = "#{BUILD_DIR}/libcore.a"

SRC_DIR       = 'src'.freeze
SRCS          = FileList["#{SRC_DIR}/*.cpp"]
OBJS          = SRCS.pathmap("%{^#{SRC_DIR},#{BUILD_DIR}}X.o")
ELF_FILE      = "#{BUILD_DIR}/main.elf".freeze
HEX_FILE      = "#{BUILD_DIR}/main.hex".freeze

CC            = "avr-gcc".freeze
CXX           = "avr-g++".freeze
AR            = "avr-ar".freeze
OBJCOPY       = "avr-objcopy".freeze
SIZE          = "avr-size".freeze
OPTIONS       = %w[
  -DF_CPU=16000000L
  -DARDUINO=167
  -DARDUINO_ARCH_AVR
  -D__PROG_TYPES_COMPAT__
].freeze
INCLUDES      = %W[
  -I#{ARDUINO_DIR}/hardware/arduino/avr/cores/arduino
  -I#{ARDUINO_DIR}/hardware/arduino/avr/variants/standard
]
CPPFLAGS      = %w[
  -MMD -mmcu=atmega328p
  -Wall -ffunction-sections -fdata-sections -Os
].freeze
CXXFLAGS      = %w[
  -fno-exceptions
].freeze
LDFLAGS       = %w[-mmcu=atmega328p -Wl,--gc-sections -Os]
LIBS          = %W[#{CORE} -lc -lm].freeze

OBJ_TO_SRC = proc do |t|
  if CORE_OBJS.include? t
    CORE_SRCS.find do |e|
      e.pathmap("%{^#{CORE_SRC_DIR},#{BUILD_DIR}/core}X") == t.pathmap("%X")
    end
  else
    t.pathmap("%{^#{BUILD_DIR},#{SRC_DIR}}X.cpp")
  end
end

CLEAN.include "#{BUILD_DIR}/*", "#{BUILD_DIR}/core/*"


file CORE => CORE_OBJS do |t|
  sh "#{AR} rcs #{t.name} #{t.sources.join ' '}"
end

file HEX_FILE => ELF_FILE do |t|
  sh "#{SIZE} #{ELF_FILE}"
  sh "#{OBJCOPY} -O ihex -R .eeprom #{ELF_FILE} #{t.name}"
end

file ELF_FILE => OBJS do |t|
  sh "#{CC} #{LDFLAGS.join ' '} -o #{t.name} #{t.prerequisites.join ' '} #{LIBS.join ' '}"
end

rule '.o' => OBJ_TO_SRC do |t|
  args = [*CPPFLAGS, *OPTIONS, *INCLUDES]
  if t.source.pathmap('%x') == '.c'
    sh "#{CC} #{args.join ' '} #{t.source} -c -o #{t.name}"
  else
    args += CXXFLAGS
    sh "#{CXX} #{args.join ' '} #{t.source} -c -o #{t.name}"
  end
end


task default: :build
task all: %i[build install]

desc 'Build the hex file'
task build: [CORE, HEX_FILE]

desc 'Install program on USB board'
task install: :build do
  sh "avrdude -V -p atmega328p -D -c arduino -P #{PORT} -U flash:w:#{HEX_FILE}:i"
end
