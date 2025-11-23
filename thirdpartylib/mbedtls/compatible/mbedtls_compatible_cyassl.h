 /* mbedtls_compatible_cyassl.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _MBEDTLS_COMPATIBLE_CYASSL_H_
#define _MBEDTLS_COMPATIBLE_CYASSL_H_

#ifdef __cplusplus
extern "C"{
#endif


#include "mbedtls/config.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/net.h"


struct CYASSL_CTX {
    int verify_mode;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt *ca_cert;
};

struct CYASSL {
    int ssl_inited;
    int ssl_error;
    mbedtls_net_context net;
    mbedtls_ssl_context ssl;
    struct CYASSL_CTX *ctx;
};

typedef struct CYASSL          CYASSL; 
typedef char    CYASSL_METHOD;
typedef struct CYASSL_CTX      CYASSL_CTX;

typedef struct CYASSL_X509_STORE_CTX {
    ;
} CYASSL_X509_STORE_CTX;

typedef int (*VerifyCallback)(int, CYASSL_X509_STORE_CTX*);


enum {
    SSL_ERROR_NONE      =  0,   /* for most functions */
    SSL_FAILURE         =  0,   /* for some functions */
    SSL_SUCCESS         =  1,
    
    SSL_VERIFY_NONE                 = 0,
    SSL_VERIFY_PEER                 = 1,
    SSL_VERIFY_FAIL_IF_NO_PEER_CERT = 2,
    SSL_VERIFY_CLIENT_ONCE          = 4,

    SSL_ERROR_WANT_READ        =  2,
    SSL_ERROR_WANT_WRITE       =  3,
    SSL_ERROR_WANT_CONNECT     =  7,
    SSL_ERROR_WANT_ACCEPT      =  8,
    SSL_ERROR_SYSCALL          =  5,
    SSL_ERROR_WANT_X509_LOOKUP = 83,
    SSL_ERROR_ZERO_RETURN      =  6,
    SSL_ERROR_SSL              = 85,
};

/**
 * @brief init memory tracker.
 *
 * @param[in] None
 * @return[out] None
 * @see None.
 * @note None.
 */
void InitMemoryTracker(void);

/**
 * @brief show memory tracker.
 *
 * @param[in] None
 * @return[out] None
 * @see None.
 * @note will printf memory usage.
 */
void ShowMemoryTracker(void);

/**
 * @brief int ssl library.
 *
 * @param[in] None
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None.
 */
int CyaSSL_Init(void);

/**
 * @brief create TLS1.2 method.
 *
 * @param[in] None
 * @return[out] a pointer to the method 
 * @see None.
 * @note None.
 */
CYASSL_METHOD *CyaTLSv1_2_client_method(void);

/**
 * @brief create ssl ctx.
 *
 * @param[in] method: a pointer to the method 
 * @return[out] a pointer to ctx 
 * @see None.
 * @note None.
 */
CYASSL_CTX* CyaSSL_CTX_new(CYASSL_METHOD* method);

/**
 * @brief set verify mode in ssl.
 *
 * @param[in] ctx: a pointer to the method 
 *			 mode: verify mode, as follows:
 * ==========================================
 * | SSL_VERIFY_NONE                |
 * |----------------------------------------|
 * | SSL_VERIFY_PEER                    |
 * ==========================================
 *			 verify_callback: verify callback function
 * @return[out] None
 * @see None.
 * @note None.
 */
void CyaSSL_CTX_set_verify(CYASSL_CTX* ctx, int mode, VerifyCallback verify_callback);

/**
 * @brief create SSL handle.
 *
 * @param[in] ctx: a pointer to the method
 * @return[out] a pointer to SSL 
 * @see None.
 * @note None.
 */
CYASSL* CyaSSL_new(CYASSL_CTX* ctx);

/**
 * @brief set socket fd to SSL.
 *
 * @param[in] ssl: a pointer to the SSL
 *			 fd: the socket handle
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None.
 */
int CyaSSL_set_fd (CYASSL* ssl, int fd);

/**
 * @brief connect ssl.
 *
 * @param[in] ssl: a pointer to the SSL
 * @return[out] SSL_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int CyaSSL_connect(CYASSL* ssl);

/**
 * @brief write data to ssl.
 *
 * @param[in] ssl: a pointer to the SSL
 *			 data: the data want to send
 *			 len: the length of data
 * @return[out] the num of sendout
 * @see None.
 * @note None.
 */
int CyaSSL_write(CYASSL* ssl, const void* data, int len);

/**
 * @brief read data from ssl.
 *
 * @param[in] ssl: a pointer to the SSL
 *			 data: the data want to recv
 *			 len: the max length of want recv
 * @return[out] the num of read 
 * @see None.
 * @note None.
 */
int CyaSSL_read(CYASSL* ssl, void* data, int len);

/**
 * @brief shutdown ssl.
 *
 * @param[in] ssl: a pointer to the SSL
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None.
 */
int CyaSSL_shutdown(CYASSL*ssl);

/**
 * @brief free SSL handle.
 *
 * @param[in] ssl: a pointer to the SSL
 * @return[out] None
 * @see None.
 * @note None.
 */
void CyaSSL_free(CYASSL*ssl);

/**
 * @brief free ctx.
 *
 * @param[in] ssl: a pointer to the CTX
 * @return[out] None
 * @see None.
 * @note None.
 */
void CyaSSL_CTX_free(CYASSL_CTX* ctx);

/**
 * @brief open debug info.
 *
 * @param[in] None
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None.
 */
int CyaSSL_Debugging_ON(void);

/**
 * @brief close debug info.
 *
 * @param[in] None
 * @return[out] None
 * @see None.
 * @note None.
 */
void CyaSSL_Debugging_OFF(void);

/**
 * @brief get error number to SSL.
 *
 * @param[in] ssl: a pointer to the SSL
 *			 mode: always is 0
 * @return[out] error number 
 * @see None.
 * @note None.
 */
int CyaSSL_get_error(CYASSL*, int mode);

/**
 * @brief get error string from error number.
 *
 * @param[in] err: error number
 *			 string: a buf to store error string
 * @return[out] the string
 * @see None.
 * @note None.
 */					 	
char* CyaSSL_ERR_error_string(unsigned long err, char* string);


#ifdef __cplusplus
}
#endif

#endif

