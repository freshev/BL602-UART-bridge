/* aliiot_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _ALIIOT_THREAD_H_
#define _ALIIOT_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief start SOCKETA in ALI-IOT mode.
 *
 * @param[in] None
 * @return[out] None
 * @see None.
 * @note None.
 */
void HSF_IAPI aliiot_thread(void);

/**
 * @brief send data to SOCKETA through ALI-IOT.
 *
 * @param[in] data: the data buffer you want send
 *			 len: the size of send buffer
 * @return[out] the size send out by SOCKETA
 * @see None.
 * @note None.
 */
int HSF_IAPI aliiot_send(char *data, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif/* _ALIIOT_THREAD_H_ */

