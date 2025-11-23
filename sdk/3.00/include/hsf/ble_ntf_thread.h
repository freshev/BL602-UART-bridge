 /* ble_ntf_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _BLE_NTF_THREAD_H_
#define _BLE_NTF_THREAD_H_

#ifdef __cplusplus
extern "C"{
#endif


#define BLE_MTU_SIZE (0x14)


/**
 * @brief init ble notification data operation.
 *
 * @param[in] NULL.
 * @return[out] the 0: success , -1: fail!
 * @see None.
 * @note None.
 */
int32_t HSF_IAPI hfble_init_notification(void);

/**
 * @brief send ble data operation.
 *
 * @param[in] NULL.
 * @return[out] the number of send success count!
 * @see None.
 * @note None.
 */
int32_t HSF_IAPI hf_send_ble_data(uint8_t *send_data, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif

