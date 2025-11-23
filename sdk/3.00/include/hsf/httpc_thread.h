/* httpc_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _HTTPC_THREAD_H_
#define _HTTPC_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief start socketA in http client mode.
 *
 * @param[in] None
 * @return[out] None
 * @see None.
 * @note None.
 */
void HSF_IAPI httpc_thread(void);

/**
 * @brief send data to SOCKETA through http client.
 *
 * @param[in] data: the data buffer you want send
 *			 len: the size of send buffer
 * @return[out] the size send out by SOCKETA
 * @see None.
 * @note None.
 */
int HSF_IAPI httpc_send(char *data, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif

