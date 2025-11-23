/* socket_b_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _SOCKET_B_THREAD_H_
#define _SOCKET_B_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


#define SOCKB_MAX_RECV_NUM 1500


typedef struct SOCKETB_THREAD_HANDLE
{
	int8_t sockb_mode;
	int sockb_socket;
	int sockb_active;
	char sockb_net_recv[SOCKB_MAX_RECV_NUM+32];
	int sockb_is_connected;
	int sockb_need_reconnect;
	int sockb_disable_connect;
	
	int sockb_recvnum;
	int sockb_readnum;
	int sockb_num;
	
	struct sockaddr_in sockb_udp_toaddr;
}socketb_handle_t;

extern socketb_handle_t *socketb_thread_handle;


/**
 * @brief start socketB.
 *
 * @param[in] uxpriority: the uxpriority of socketa thread
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI start_socketb(uint32_t uxpriority);

/**
 * @brief check whether or not socketB is started.
 *
 * @param[in] None
 * @return[out] 0-not start, 1-have started
 * @see None.
 * @note None.
 */
int HSF_IAPI socketb_is_started(void);

/**
 * @brief send data to SOCKETB.
 *
 * @param[in] data: the data buffer you want send
 *			 len: the size of send buffer
 * @return[out] the size send out by SOCKETB
 * @see None.
 * @note None.
 */
int HSF_IAPI socketb_send(char *data, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif

