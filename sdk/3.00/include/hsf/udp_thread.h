/* udp_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _UDP_THREAD_H_
#define _UDP_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief start socketA in UDP mode.
 *
 * @param[in] type: 0-UDP client, 1-UDP server
 * @return[out] None
 * @see None.
 * @note None.
 */
void HSF_IAPI udp_thread(char type);


#ifdef __cplusplus
}
#endif

#endif

