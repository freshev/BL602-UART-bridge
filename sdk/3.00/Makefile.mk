# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ./include/freertos ./include/hsf ./include/lwip ./include/mdns

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=							 

## This component's src 
COMPONENT_SRCS1 := 			libs/start.S

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
COMPONENT_SRCS := $(COMPONENT_SRCS1)
COMPONENT_SRCDIRS := . libs

## This component's linker script 
LINKER_SCRIPTS := LPBX7.ld

## This component's linkfile 
COMPONENT_ADD_LDFLAGS += -L $(COMPONENT_PATH)/libs $(addprefix -T ,$(LINKER_SCRIPTS))                
COMPONENT_ADD_LINKER_DEPS := $(addprefix libs/,$(LINKER_SCRIPTS))

## This component's library 
ifeq ($(DEBUG_VIA_BLE),1)
LIBS ?= LPBX7Kernel_debug_ble
else
LIBS ?= LPBX7Kernel
endif

COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/libs $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/libs/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += 
