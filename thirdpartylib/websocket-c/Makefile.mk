# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ./

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 

## This component's src 
COMPONENT_SRCS := src/base64-decode.c
COMPONENT_SRCS += src/client.c
COMPONENT_SRCS += src/client-handshake.c
COMPONENT_SRCS += src/client-parser.c
COMPONENT_SRCS += src/context.c
COMPONENT_SRCS += src/handshake.c
COMPONENT_SRCS += src/libwebsockets.c
COMPONENT_SRCS += src/lws-plat-hf.c
COMPONENT_SRCS += src/lws-ssl.c
COMPONENT_SRCS += src/output.c
COMPONENT_SRCS += src/parsers.c
COMPONENT_SRCS += src/pollfd.c
COMPONENT_SRCS += src/service.c
COMPONENT_SRCS += src/sha1/sha1.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_SRCDIRS := src src/sha1

## This component's library 
LIBS ?= 
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += 
