#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

DEBUG_VIA_BLE = 1
BAUDRATE ?= 115200
DATABITS = 8

$(info DEBUG_VIA_BLE is $(DEBUG_VIA_BLE))
$(info BAUDRATE is $(BAUDRATE))
$(info DATABITS is $(DATABITS))

ifeq ($(PROJECT_NAME),lpt270)
TARGET = __LPT270__
else ifeq ($(PROJECT_NAME),lpt170)
TARGET = __LPT170__
else ifeq ($(PROJECT_NAME),lpt271)
TARGET = __LPT271__
else ifeq ($(PROJECT_NAME),lpb170)
TARGET = __LPB170__
else ifeq ($(PROJECT_NAME),lpb175)
TARGET = __LPB175__
else ifeq ($(PROJECT_NAME),lpt570)
TARGET = __LPT570__
else ifeq ($(PROJECT_NAME),lpt272)
TARGET = __LPT272__
endif

#TARGET = __LPT570__

#for delete code size
# NOMAL_MODE  
# DELETE_CODE  
PROJECT_MODE=DELETE_CODE

PROJECT_PATH := $(abspath .)
export PROJECT_PATH

ifeq ($(origin PROJECT_SDK_PATH), undefined)
PROJECT_SDK_PATH_GUESS ?= $(shell pwd)
PROJECT_SDK_PATH ?= $(PROJECT_SDK_PATH_GUESS)
endif

AFTER_BUILD =

EXAMPLE_NAME ?= null
#EXAMPLE_NAME = ble
SDK_VERSION = 3.00

ifeq ($(EXAMPLE_NAME),null)
APPDIR = MQTT-C src
else
APPDIR = MQTT-C example/$(EXAMPLE_NAME)
endif

ifeq ($(EXAMPLE_NAME),httpsd)
APPDIR += Cyassl
CFLAGS   += -D_DELETE_SMARTAPLINK_
CFLAGS   += -D_DELETE_SMARTLINK_
else ifeq ($(EXAMPLE_NAME), mqtt_ssl)
APPDIR += mbedtls
else ifeq ($(EXAMPLE_NAME), ssl)
APPDIR += mbedtls
else ifeq ($(EXAMPLE_NAME), websocket)
APPDIR += websocket-c websocketclient
endif

ifeq ($(DEBUG_VIA_BLE),1)
	CFLAGS   += -DDEBUG_VIA_BLE
	export DEBUG_VIA_BLE
endif

CFLAGS   += -DBAUDRATE=$(BAUDRATE)

ifeq ($(DATABITS),7)
CFLAGS   += -DDATABITS=7
else
CFLAGS   += -DDATABITS=8
endif

INCLUDE_COMPONENTS += $(SDK_VERSION) $(APPDIR)

include $(PROJECT_SDK_PATH)/tools/scripts/project.mk

CFLAGS   += -D_NOT_SUPPORT_JD_ -D_HSF_ -D$(TARGET)

#delete code size option
ifeq ($(PROJECT_MODE),DELETE_CODE)
# /*delete WPS, about 23K*/
CFLAGS   += -D_DELETE_WPS_

# /*delete socketa*/
CFLAGS   += -D_DELETE_SOCKETA_

# /*delete socketb*/
CFLAGS   += -D_DELETE_SOCKETB_

# /*delete MDNS for smartAPLink, about 14K*/
CFLAGS   += -D_DELETE_MDNS_

# /*delete smartAPLink, about 17K*/
CFLAGS   += -D_DELETE_SMARTAPLINK_

# /*delete smartLink, about 10K*/
CFLAGS   += -D_DELETE_SMARTLINK_

# /*delete http server, about 25K*/
#CFLAGS   += -D_DELETE_HTTPD_

# /*delete BLE, about 80K*/
#CFLAGS   += -D_DELETE_BLE_
endif