/* hsf.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HSF_H_
#define _HSF_H_

#define HSF_API
#define HSF_IAPI HSF_API
#define USER_FUNC


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef BYTE
typedef unsigned char	BOOL;
typedef unsigned char	BYTE;
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;
typedef int				INT;
typedef unsigned int	UINT;
typedef long			LONG;
typedef unsigned long	DWORD;
#endif

#ifndef TRUE
    #define TRUE  1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

#define HF_SUCCESS 		0

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC	extern
#include <stdbool.h>
//typedef unsigned char           bool;
#define true                    1
#define false					0
#endif


#ifndef NULL
    #if defined(__cplusplus)
        #define NULL            0
    #else
        #define NULL            ((void *) 0)
    #endif
#endif

#define WEAK __attribute__ ((weak))
#define FUNC_IN_RAM __attribute__((section(".tcm_code")))
#include "hfble.h"
#include "hferrno.h"
#include "hfconfig.h"
#include "hfuart.h"
#include "hfat.h"
#include "hflist.h"
#include "hfnvm.h"
#include "hfsys.h"
#include "hfflash.h"
#include "hfthread.h"
#include "hfflashlayout.h"
#include "hfpartition.h"
#include "hfproduct.h"
#include "hffile.h"
#include "hfnet.h"
#include "hf_debug.h"
#include "hfgpio.h"
#include "hftimer.h"
#include "hfupdate.h"
#include "hfwifi.h"
#include "hfsniffer.h"
#include "hftime.h"
#include "hfsmtlk.h"
#include "hfmsgq.h"
#include "hfdns.h"
#include "hfspi.h"
#include "hfcrypto.h"
#include "hfntp.h"
#include "hfsmtaplk.h"


#define GLOBAL_VER 				"3.01"
#ifdef CONFIG_FLASH_SIZE_1MB
#define GLOBAL_LVER				"00 (2022-02-28 18:00 1M)"
#elif defined CONFIG_FLASH_SIZE_2MB
#define GLOBAL_LVER				"25 (2025-05-20 14:00 2M)"
#endif


#endif

