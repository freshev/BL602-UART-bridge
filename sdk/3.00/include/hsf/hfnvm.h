/* hfnvm.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _HF_NVM_H_
#define _HF_NVM_H_

#ifdef __cplusplus
extern "C" {
#endif


#define HSFNVM_SIZE					(512)

#define HSFNVM_MAGIC_NUM			(0x0102Faac)

#define HSFNVM_MAGIC_NUM_OFFSET				(0)
#define HSFNVM_MAGIC_NUM_SIZE				(16)

#define HSFNVM_RESET_REASON_OFFSET			(16)
#define HSFNVM_RESET_REASON_SIZE				(4)

#define HSFNVM_RANDOM_NUM					(20)
#define HSFNVM_RANDOM_NUM_SIZE				(4)

#define HSFNVM_OTA_MODE						(24)
#define HSFNVM_OTA_MODE_SIZE					(1)

#define HSFNVM_MDCH_MODE						(25)
#define HSFNVM_MDCH_MODE_SIZE				(1)

#define HSFNVM_HFSW_MODE						(26)
#define HSFNVM_HFSW_MODE_SIZE				(1)

#define HSFNVM_USER_OFFSET					(256)


int HSF_IAPI hfnvm_init(void);

int HSF_IAPI hfnvm_write_int(uint16_t offset,int value);

int HSF_IAPI hfnvm_read_int(uint16_t offset);

int HSF_IAPI hfnvm_write_data(uint16_t offset,uint8_t *data,int size);

int HSF_IAPI hfnvm_read_data(uint16_t offset,uint8_t *data,int size);

void HSF_IAPI hfnvm_reset(void);


#ifdef __cplusplus
}
#endif

#endif

