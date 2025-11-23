/* uart_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _UART_THREAD_H_
#define _UART_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


#define M2M_MAXUARTRECV 				1024/*1400*/

/**
 * @brief start uart thread.
 *
 * @param[in] uart_id: UART id, 0 or 1
 *			 uxpriority: the uxpriority of uart thread
 *			 size: the size of the stack, real size is [size*4]
 * @return[out] HF_SUCCESS-successfully, other value is failed
 */
int HSF_IAPI uart_thread_start(int uart_id, uint32_t uxpriority, int size);

/**
 * @brief send uart data in format.
 *
 * @param[in] buf: send data buf
 *			 sendnum: the number of send data
 * @return[out] None
 */
void HSF_IAPI usart_send_in_hf_format(char *buf, int sendnum);

/**
 * @brief send data to throughput UART.
 *
 * @param[in] Buf: sned data buf
 *			 BufLen: the number want send
 * @return[out] None
 */
int HSF_IAPI usart_send(char* Buf,uint32_t BufLen);

/**
 * @brief recv data from throughput UART.
 *
 * @param[in] Buf: recv data buf
 *			 BufLen: the number want recv
 *			 Wait: recv wait time
 * @return[out] None
 */
int HSF_IAPI usart_recv(char* Buf,uint32_t BufLen,uint32_t Wait);

/**
 * @brief set attribute for UART.
 *
 * @param[in] irq_size: uart irq buffer size, in bytes, default is 1024
 *			 irq_wait_time: irq wait timeout, in milliseconds, default is 20
 *			 callback_recv_num: uart callback recv num at one time, in bytes, default is macro 'M2M_MAXUARTRECV'
 *			 callback_recv_timeout: uart callback recv imeout at one time, in milliseconds, default is 1000
 * @return[out] None
 */
int HSF_IAPI uart_set_attribute(int irq_size, int irq_wait_time, int callback_recv_num, int callback_recv_timeout);


#ifdef __cplusplus
}
#endif


#endif

