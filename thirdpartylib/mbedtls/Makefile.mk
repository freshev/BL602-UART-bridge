# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ./compatible

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := include/mbedtls

## This component's src 
# COMPONENT_SRCS += compatible/mbedtls_compatible_cyassl.c
COMPONENT_SRCS += compatible/mbedtls_compatible_alios.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_SRCDIRS := compatible

## This component's library 
LIBS ?= 
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += 
