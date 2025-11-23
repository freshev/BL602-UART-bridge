 /* mbedtls_compatible_alios.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifdef _NOT_SUPPORT_JD_

#ifndef _MQTTMBEDTLS_H_
#define _MQTTMBEDTLS_H_

#ifdef __cplusplus
extern "C"{
#endif


#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "MQTTHF.h"

/**
 * Create a ssl connect.
 *
 * @param[in]  tcp_fd       handle of the tcp socket.
 * @param[in]  ca_cert      CA.
 * @param[in]  ca_cert_len  length of the CA.
 *
 * @return  NULL: error; ssl_param: success.
 */
void *mqtt_mbedtls_ssl_connect(void *tcp_fd, const char *ca_cert,int ca_cert_len,const char *thing_cert,int thing_cert_len,const char *private_cert,int private_cert_len);


/**
 * Send data through ssl.
 *
 * @param[in]  ssl     handle of the ssl.
 * @param[in]  buffer  data to send.
 * @param[in]  length  length of the data.
 *
 * @return  -1: error; others: length of the data be sended.
 */
int mqtt_mbedtls_ssl_send(Network *ssl, unsigned char *buffer, int length, int flag);

/**
 * Recv data through ssl.
 *
 * @param[in]  ssl     handle of the ssl.
 * @param[in]  buffer  buffer to recv data.
 * @param[in]  length  the max size of the buffer.
 *
 * @return  -1: error; 0: EOF; others: length of the data be sended.
 */
int mqtt_mbedtls_ssl_recv(Network *ssl, unsigned char *buffer, int length, int flag);

/**
 * Close the ssl.
 *
 * @param[in]  ssl  handle to be closed.
 *
 * @return  0: success.
 */
void mqtt_mbedtls_ssl_close(Network *ssl);

extern void *mqtt_ssl;

#ifdef __cplusplus
}
#endif

#endif

#endif
