# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=							 

## This component's src 
COMPONENT_SRCS := 			src/joylink_ble.c \
							src/joylink_extern.c \
							src/joylink_extern_json.c \
							src/joylink_extern_ota.c \
							src/joylink_extern_sub_dev.c \
							src/joylink_extern_user.c \
							src/joylink_flash.c \
							src/joylink_http.c \
							src/joylink_math.c \
							src/joylink_memory.c \
							src/joylink_socket.c \
							src/joylink_softap.c \
							src/joylink_ssl_auth.c \
							src/joylink_stdio.c \
							src/joylink_string.c \
							src/joylink_thread.c \
							src/joylink_ota_https.c \
							src/joylink_time.c 

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_SRCDIRS := . src

## This component's library 
LIBS ?= JDjoylink
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += 
