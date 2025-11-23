/* kvmgr.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _KVMGR_H_
#define _KVMGR_H_

#ifdef __cplusplus
extern "C" {
#endif


/* The totally storage size for key-value store */
#define KV_TOTAL_SIZE   (8 * 1024)

/* The physical flash address for key-value store */
#define KV_FLASH_ADDRESS    0xA000


typedef enum _kv_get_type_e
{
    KV_GET_TYPE_STRING = 1,
    KV_GET_TYPE_BINARY,
    KV_GET_TYPE_INT,
    KV_GET_TYPE_FLOAT,
    KV_GET_TYPE_MAX
}kv_get_type_e;

/**
 * @brief init the kv module.
 *
 * @param[in] none.
 *
 * @note: the default KV size is @HASH_TABLE_MAX_SIZE, the path to store
 *        the kv file is @KVFILE_PATH.
 * @retval  0 on success, otherwise -1 will be returned
 */
int kv_module_init(void);

/**
 * @brief deinit the kv module.
 *
 * @param[in] none.
 *
 * @note: all the KV in RAM will be released.
 * @retval none.
 */
void kv_module_deinit(void);


#ifdef __cplusplus
}
#endif

#endif

