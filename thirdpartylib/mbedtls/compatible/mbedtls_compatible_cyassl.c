 /* mbedtls_compatible_cyassl.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <lwip/errno.h>

#include "hsf.h"
#include "mbedtls_compatible_cyassl.h"

#if defined(MBEDTLS_THREADING_ALT)
#include "mbedtls/threading.h"
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#endif

#if defined(MBEDTLS_ERROR_C) || defined(MBEDTLS_ERROR_STRERROR_DUMMY)
#include "mbedtls/error.h"
#endif

static int ssl_debug_level = 0;

static int ssl_random(void *prng, unsigned char *output, size_t output_len)
{
    (void)prng;

    while(output_len > 0) {
        output[output_len - 1] = hfsys_random() & 0xFF;
        output_len--;
    }

    return 0;
}

#if defined(MBEDTLS_DEBUG_C)
static void ssl_debug(void *ctx, int level,
                      const char *file, int line, const char *str)
{
    (void)ctx;
    (void) level;

    if(ssl_debug_level == 0)
        return;

    if(level > ssl_debug_level)
        HF_Debug(DEBUG_SSL, "[SSL] %s, line: %d: %s", file, line, str);

    return;
}
#endif

static int ssl_recv( void *ctx, unsigned char *buf, size_t len )
{
    int ret;
    int fd = ((mbedtls_net_context *) ctx)->fd;

    if (fd < 0) {
        HF_Debug(DEBUG_SSL, "[SSL] invalid socket fd\r\n");
        return (MBEDTLS_ERR_NET_INVALID_CONTEXT);
    }

    ret = (int)read(fd, buf, len);

    if (ret < 0) {
        if (errno == EPIPE || errno == ECONNRESET) {
            HF_Debug(DEBUG_SSL, "[SSL] net reset - errno: %d\r\n", errno);
            return (MBEDTLS_ERR_NET_CONN_RESET);
        }

        if (errno == EINTR) {
            return (MBEDTLS_ERR_SSL_WANT_READ);
        }

        HF_Debug(DEBUG_SSL, "[SSL] ssl recv failed - errno: %d\r\n", errno);
        return (MBEDTLS_ERR_NET_RECV_FAILED);
    }

    return ret;
}

static int ssl_send( void *ctx, const unsigned char *buf, size_t len )
{
    int ret;
    int fd = ((mbedtls_net_context *) ctx)->fd;

    if (fd < 0) {
        return (MBEDTLS_ERR_NET_INVALID_CONTEXT);
    }

    ret = (int)send(fd, buf, len, 0);

    if (ret < 0) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl send failed - errno: %d\r\n", errno);
        return (MBEDTLS_ERR_NET_SEND_FAILED);
    }

    return ret;
}

int CyaSSL_Init(void)
{
#if defined(MBEDTLS_PLATFORM_MEMORY)
	extern void * mbedtls_mem_calloc(size_t n, size_t size);
	extern void mbedtls_mem_free( void *ptr );
	mbedtls_platform_set_calloc_free(mbedtls_mem_calloc, mbedtls_mem_free);
#endif
	return 0;
}

CYASSL_METHOD *CyaTLSv1_2_client_method(void)
{
	return "TLS1.2";
}

CYASSL_CTX* CyaSSL_CTX_new(CYASSL_METHOD* method)
{
	CYASSL_CTX *ctx = (CYASSL_CTX *)hfmem_malloc(sizeof(CYASSL_CTX));
	if(ctx)
	{
		memset(ctx, 0, sizeof(CYASSL_CTX));
		return ctx;
	}
	
	return NULL;
}

void CyaSSL_CTX_set_verify(CYASSL_CTX* ctx, int mode, VerifyCallback verify_callback)
{
	if(mode == SSL_VERIFY_NONE)
		ctx->verify_mode = 0;
	else
	{
		ctx->ca_cert = (mbedtls_x509_crt *)hfmem_malloc(sizeof(mbedtls_x509_crt));
		if(ctx->ca_cert)
			memset(ctx->ca_cert, 0, sizeof(mbedtls_x509_crt));
	}
}

CYASSL* CyaSSL_new(CYASSL_CTX* ctx)
{
	CYASSL *ssl = (CYASSL *)hfmem_malloc(sizeof(CYASSL));
	if(ssl)
	{
		memset(ssl, 0, sizeof(CYASSL));
		ssl->ctx = ctx;
		return ssl;
	}
	return NULL;
}

int CyaSSL_set_fd (CYASSL* ssl, int fd)
{
	if(ssl && ssl->ctx && fd >= 0)
	{
		ssl->net.fd = fd;
		return 0;
	}
	
	return -1;
}

int CyaSSL_connect(CYASSL* ssl)
{
	if(ssl && ssl->ctx)
	{
		int ret;
		unsigned int result;
		
#if defined(MBEDTLS_THREADING_ALT)
		mbedtls_threading_set_alt(threading_mutex_init,
			threading_mutex_free,
			threading_mutex_lock,
			threading_mutex_unlock);
#endif

		if(ssl->ctx->verify_mode)
			mbedtls_x509_crt_init(ssl->ctx->ca_cert);
		mbedtls_ssl_config_init(&ssl->ctx->conf);
        	mbedtls_ssl_init(&ssl->ssl);
		ssl->ssl_inited = 1;

		if(ssl->ctx->verify_mode)
		{
			/*ret = mbedtls_x509_crt_parse(&ssl->ctx->ca_cert, (unsigned char *)ca_cert, (size_t)ca_cert_len + 1);
			if (ret < 0) {
				HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: x509 parse failed- 0x%x\n", -ret);
				goto ERR;
			}*/
		}
		
		ret = mbedtls_ssl_config_defaults(&ssl->ctx->conf, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);
		if (ret != 0)
		{
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: set ssl config failed - %d\r\n", ret);
			goto ERR;
		}
		
		if(ssl->ctx->verify_mode)
		{
			mbedtls_ssl_conf_authmode(&ssl->ctx->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
			mbedtls_ssl_conf_ca_chain(&ssl->ctx->conf, ssl->ctx->ca_cert, NULL);
		}
		else
			mbedtls_ssl_conf_authmode(&ssl->ctx->conf, MBEDTLS_SSL_VERIFY_NONE);
		mbedtls_ssl_conf_rng(&ssl->ctx->conf, ssl_random, NULL);
		
#if defined(MBEDTLS_DEBUG_C)
		mbedtls_ssl_conf_dbg(&ssl->ctx->conf, ssl_debug, NULL);
#endif

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
		ret = mbedtls_ssl_conf_max_frag_len(&ssl->ctx->conf, MBEDTLS_SSL_MAX_FRAG_LEN_4096);
		if (ret != 0)
		{
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_conf_max_frag_len returned - %d\r\n", ret);
			goto ERR;
		}
#endif

		ret = mbedtls_ssl_setup(&ssl->ssl, &ssl->ctx->conf);
		if (ret != 0)
		{
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_setup returned - %d\r\n", ret);
			goto ERR;
		}
		
		mbedtls_ssl_set_bio(&ssl->ssl, &ssl->net, ssl_send, ssl_recv, NULL);
		
		while ((ret = mbedtls_ssl_handshake(&ssl->ssl)) != 0) 
		{        
			if ((ret != MBEDTLS_ERR_SSL_WANT_READ) && (ret != MBEDTLS_ERR_SSL_WANT_WRITE)) 
			{
				ssl->ssl_error = ret;
				HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_handshake returned -0x%x\r\n", -ret);         
				goto ERR;
			}
		}
		
		result = mbedtls_ssl_get_verify_result(&ssl->ssl);   
		if (result != 0) 
		{
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: verify result not confirmed - %d\r\n", result);        
			goto ERR;
		}

		HF_Debug(DEBUG_SSL, "[SSL] ssl success, connect ok\r\n", result);  
		return SSL_SUCCESS;
	}
	
ERR:
	if(ssl->ctx->verify_mode)
		mbedtls_x509_crt_free(ssl->ctx->ca_cert);
	mbedtls_ssl_free(&ssl->ssl);
	mbedtls_ssl_config_free(&ssl->ctx->conf);
	return -1;
}

int CyaSSL_write(CYASSL* ssl, const void* data, int len)
{
	int ret;
	int total_len = 0;
	int retry = 0;
	
	if(ssl == NULL || ssl->ctx == NULL || data == NULL || len < 0)
	{
		HF_Debug(DEBUG_SSL, "[SSL] ssl_send: invalid input args\r\n");
		return -1;
	}
	
	if (ssl->ssl_inited != 1) 
	{
		HF_Debug(DEBUG_SSL, "[SSL] ssl uninited\r\n");
		return -1;
	}
	
	do{
		ret = mbedtls_ssl_write(&ssl->ssl, (const unsigned char *)data, (len - total_len));
		if (ret > 0)
		{
			total_len += ret;
			data += ret;
		} 
		else if (ret == 0) 
		{
			/* EOF */
			break;
		}
		else 
		{
			if (ret == MBEDTLS_ERR_SSL_WANT_WRITE){
				retry ++;
				msleep(10);
				continue;
			}
			if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY){
				/*
				* indicate that write already complete,
				* if call read again, it will return 0(EOF))
				*/
				break;
			}
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_send: mbedtls_ssl_write failed - 0x%x\r\n", -ret);
			return -1;
		}
    	} while (total_len < len && retry < 10);
	
	return ret < 0 ? -1 : total_len;
}

int CyaSSL_read(CYASSL* ssl, void* data, int len)
{
	int ret;
	int total_len = 0;
	
	if(ssl == NULL || ssl->ctx == NULL || data == NULL || len < 0)
	{
		HF_Debug(DEBUG_SSL, "[SSL] ssl_recv: invalid input args\r\n");
		return -1;
	}

	if (ssl->ssl_inited != 1) 
	{
		HF_Debug(DEBUG_SSL, "[SSL] ssl uninited\r\n");
		return -1;
	}
	
	do{
		ret = mbedtls_ssl_read(&ssl->ssl, (unsigned char *)data, len);
		if (ret > 0)
		{
			total_len = ret;
			break;
		} 
		else if (ret == 0)
		{
			/* EOF */
			return 0;
		}
		else
		{
			if (ret == MBEDTLS_ERR_SSL_WANT_READ){
				return -EAGAIN;
			}
			if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
				/*
				* indicate that read already complete,
				* if call read again, it will return 0(EOF))
				*/
				break;
			}
			ssl->ssl_error = ret;
			HF_Debug(DEBUG_SSL, "[SSL] ssl_recv: mbedtls_ssl_read failed - 0x%x\r\n", -ret);
			return -1;
		}
	}while (0);
	
	return total_len;
}

int CyaSSL_shutdown(CYASSL*ssl)
{
	if(ssl && ssl->ctx)
	{
		if (ssl->ssl_inited)
		{
			mbedtls_ssl_close_notify(&ssl->ssl);

			if(ssl->ctx->verify_mode)
				mbedtls_x509_crt_free(ssl->ctx->ca_cert);
			mbedtls_ssl_free(&ssl->ssl);
			mbedtls_ssl_config_free(&ssl->ctx->conf);
			
#if defined(MBEDTLS_THREADING_ALT)
			mbedtls_threading_free_alt();
#endif
		}
	}
	
	return 0;
}

void CyaSSL_free(CYASSL*ssl)
{
	if(ssl)
	{
		hfmem_free(ssl);
	}
}

void CyaSSL_CTX_free(CYASSL_CTX* ctx)
{
	if(ctx)
	{
		if(ctx->verify_mode)
			hfmem_free(ctx->ca_cert);
		hfmem_free(ctx);
	}
}

int CyaSSL_Debugging_ON(void)
{
	ssl_debug_level = 1;
	
#if defined(MBEDTLS_DEBUG_C)
	mbedtls_debug_set_threshold(3);
#endif
	return 0;
}

void CyaSSL_Debugging_OFF(void)
{
	ssl_debug_level = 0;
	
#if defined(MBEDTLS_DEBUG_C)
	mbedtls_debug_set_threshold(0);
#endif
}

int CyaSSL_get_error(CYASSL*ssl, int mode)
{
	if(ssl && ssl->ctx)
	{
		return ssl->ssl_error;
	}
	return 0;
}

char* CyaSSL_ERR_error_string(unsigned long err, char* string)
{
#if defined(MBEDTLS_ERROR_C)
	int error = (int)err;
	mbedtls_strerror(error, string, 64);
	return string;
#endif

	return "";
}

