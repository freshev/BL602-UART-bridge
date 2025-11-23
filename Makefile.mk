
#Relative PATH in  in CONFIG_TOOLPREFIX
CONFIG_TOOLPREFIX ?= ./toolchain/bin/riscv64-unknown-elf-

### Compiler definitions
CC := $(call dequote,$(CONFIG_TOOLPREFIX))gcc
CXX := $(call dequote,$(CONFIG_TOOLPREFIX))g++
LD := $(call dequote,$(CONFIG_TOOLPREFIX))ld
AR := $(call dequote,$(CONFIG_TOOLPREFIX))ar
OBJCOPY := $(call dequote,$(CONFIG_TOOLPREFIX))objcopy
SIZE := $(call dequote,$(CONFIG_TOOLPREFIX))size
STRIP := $(call dequote,$(CONFIG_TOOLPREFIX))strip
export CC CXX LD AR OBJCOPY SIZE
