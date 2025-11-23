/* assis_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _ASSIS_THREAD_H_
#define _ASSIS_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


#define ASSIS_PORT			48899
#define ASSIS_PBUF_SIZE		200


/**
 * @brief start assis thread.
 *
 * @param[in] port: assis thread listen udp port
 * @return[out] HF_SUCCESS-successfully, other value is failed
 */
int HSF_IAPI start_assis(uint16_t port);

/**
 * @brief check whether or not in assis AT cmd mode.
 *
 * @param[in] None
 * @return[out] 0-not in, 1-in assis AT cmd mode
 * @see None.
 * @note None.
 */
int HSF_IAPI assis_is_in_cmd(void);

/**
 * @brief get assis AT cmd source IP address.
 *
 * @param[in] None
 * @return[out] IP address in number format
 * @see None.
 * @note None.
 */
uint32_t HSF_IAPI assis_get_peer_ip(void);

/**
 * @brief send response to AT commands from assis thread.
 *
 * @param[in] rsp: the response
 *			 len: the length of response
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */ 
int HSF_IAPI assis_cmd_response(char *rsp, int len);


#ifdef __cplusplus
}
#endif

#endif

