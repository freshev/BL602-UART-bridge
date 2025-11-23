/* hfpartition.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_PARTITION_H_
#define _HF_PARTITION_H_

#ifdef __cplusplus
extern "C" {
#endif


#define PARTITION_TABLE_ADDR				0x0000C000

#define PARTITION_MAX_NUM 					16
#define PARTITION_NAME_MAX_NUM			24
#define PARTITION_MAGIC						(0x54504642)

#define PARTITION_NAME_BOOT				"bootloader"
#define PARTITION_NAME_CODE				"code"
#define PARTITION_NAME_UPGRADE			"upgrade"
#define PARTITION_NAME_BOOTCONFIG			"bootconfig"
#define PARTITION_NAME_SECUFLASH			"secuflash"
#define PARTITION_NAME_USERPAGE			"userpage"
#define PARTITION_NAME_USERPAGEBACKUP	"userpage_backup"
#define PARTITION_NAME_FSETTING			"fsetting"
#define PARTITION_NAME_TEMPFLASH			"tempflash"
#define PARTITION_NAME_USERBIN				"userbin"
#define PARTITION_NAME_WEBPAGE			"webpage"
#define PARTITION_NAME_UFLASH				"uflash"
#define PARTITION_NAME_UFLASH1			"uflash1"


struct PARTITION_HEADER
{
	unsigned int magic;
	char version[12];
	unsigned int size;
	unsigned int crc32;
	unsigned int reserved[2];
};

struct PARTITION_DATA
{
	char name[PARTITION_NAME_MAX_NUM];
	unsigned int addr;
	unsigned int size;
};


int HSF_IAPI hfpartition_table_init(void);

int HSF_IAPI hfpartition_table_is_valid(void);

int HSF_IAPI hfpartition_table_addr(const char *name, unsigned int *addr, unsigned int *size);

unsigned int HSF_IAPI hfpartition_addr(const char *name);

unsigned int HSF_IAPI hfpartition_size(const char *name);


#ifdef __cplusplus
}
#endif

#endif

