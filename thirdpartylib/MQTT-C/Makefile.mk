# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ./MQTTClient-C ./MQTTPacket

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 

## This component's src 
COMPONENT_SRCS := MQTTClient-C/MQTTClient.c \
				  MQTTClient-C/MQTTHF.c \
				  MQTTClient-C/MQTTmbedtls.c \
				  MQTTPacket/MQTTConnectClient.c \
				  MQTTPacket/MQTTConnectServer.c \
				  MQTTPacket/MQTTDeserializePublish.c \
				  MQTTPacket/MQTTFormat.c \
				  MQTTPacket/MQTTPacket.c \
				  MQTTPacket/MQTTSerializePublish.c \
				  MQTTPacket/MQTTSubscribeClient.c \
				  MQTTPacket/MQTTSubscribeServer.c \
				  MQTTPacket/MQTTUnsubscribeClient.c \
				  MQTTPacket/MQTTUnsubscribeServer.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_SRCDIRS := MQTTClient-C MQTTPacket

## This component's library 
LIBS ?= 
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += 
