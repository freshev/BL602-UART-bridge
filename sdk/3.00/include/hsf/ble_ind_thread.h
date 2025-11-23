 /* ble_ind_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _BLE_IND_THREAD_H_
#define _BLE_IND_THREAD_H_

#ifdef __cplusplus
extern "C"{
#endif


/**
 * @brief init ble indicate data operation.
 *
 * @param[in] NULL.
 * @return[out] the 0: success , -1: fail!
 * @see None.
 * @note None.
 */
int32_t HSF_IAPI hfble_init_init_indicate(void);

/**
 * @brief ble indicate send data operation.but len <= 20 byte
 *
 * @param[in] send_data: send data point, len : send data len.
 * @return[out] the 0: success , -1: fail!
 * @see None.
 * @note None.
 */
int32_t HSF_IAPI hf_send_ble_ind_data(uint8_t *send_data, uint16_t len);


#ifdef __cplusplus
}
#endif

#endif

