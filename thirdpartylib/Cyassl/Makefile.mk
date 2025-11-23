# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += 

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 

## This component's src 
COMPONENT_SRCS := ctaocrypt/src/aes.c
COMPONENT_SRCS += ctaocrypt/src/arc4.c
COMPONENT_SRCS += ctaocrypt/src/asm.c
COMPONENT_SRCS += ctaocrypt/src/asn.c
COMPONENT_SRCS += ctaocrypt/src/blake2b.c
COMPONENT_SRCS += ctaocrypt/src/camellia.c
COMPONENT_SRCS += ctaocrypt/src/coding.c
COMPONENT_SRCS += ctaocrypt/src/compress.c
COMPONENT_SRCS += ctaocrypt/src/des3.c
COMPONENT_SRCS += ctaocrypt/src/dh.c
COMPONENT_SRCS += ctaocrypt/src/dsa.c
COMPONENT_SRCS += ctaocrypt/src/ecc.c
COMPONENT_SRCS += ctaocrypt/src/ecc_fp.c
COMPONENT_SRCS += ctaocrypt/src/error.c
COMPONENT_SRCS += ctaocrypt/src/hc128.c
COMPONENT_SRCS += ctaocrypt/src/hmac.c
COMPONENT_SRCS += ctaocrypt/src/integer.c
COMPONENT_SRCS += ctaocrypt/src/logging.c
COMPONENT_SRCS += ctaocrypt/src/md2.c
COMPONENT_SRCS += ctaocrypt/src/md4.c
COMPONENT_SRCS += ctaocrypt/src/md5.c
COMPONENT_SRCS += ctaocrypt/src/memory.c
COMPONENT_SRCS += ctaocrypt/src/misc.c
COMPONENT_SRCS += ctaocrypt/src/pwdbased.c
COMPONENT_SRCS += ctaocrypt/src/rabbit.c
COMPONENT_SRCS += ctaocrypt/src/random.c
COMPONENT_SRCS += ctaocrypt/src/ripemd.c
COMPONENT_SRCS += ctaocrypt/src/rsa.c
COMPONENT_SRCS += ctaocrypt/src/sha.c
COMPONENT_SRCS += ctaocrypt/src/sha256.c
COMPONENT_SRCS += ctaocrypt/src/sha512.c
COMPONENT_SRCS += ctaocrypt/src/tfm.c
COMPONENT_SRCS += src/crl.c
COMPONENT_SRCS += src/internal.c
COMPONENT_SRCS += src/io.c
COMPONENT_SRCS += src/keys.c
COMPONENT_SRCS += src/ocsp.c
COMPONENT_SRCS += src/sniffer.c
COMPONENT_SRCS += src/ssl.c
COMPONENT_SRCS += src/tls.c
COMPONENT_SRCS += src/hf_cyassl.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_SRCDIRS := ctaocrypt/src src

## This component's library 
LIBS ?= 
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

## This component's flag
#CPPFLAGS += -DSUPPORT_MULTI_CERTIFICATE
