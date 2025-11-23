 /* mbedtls_compatible_alios.c
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

#include "mbedtls/config.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/net.h"
#include "hsf.h"

#if defined(MBEDTLS_THREADING_ALT)
#include "mbedtls/threading.h"
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#endif

#define SSL_DEBUG_LEVEL    3

#define SSL_PARAM_MAGIC    0x54321212

typedef struct _ssl_param_t {
    size_t magic;
    mbedtls_net_context net;
    mbedtls_net_context client_fd;
    mbedtls_x509_crt ca_cert;
	mbedtls_x509_crt owncert;
    mbedtls_ssl_config conf;
    mbedtls_ssl_context ssl;
	mbedtls_pk_context pkey;
} ssl_param_t;

static void * mbedtls_mem_calloc(size_t n, size_t size)
{
    void *p = hfmem_malloc(n*size);
	if(p == NULL)
		return NULL;

	memset(p,0,n*size);
	return p;
}

void mbedtls_mem_free( void *ptr )
{
	hfmem_free(ptr);
}

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

void *app_mbedtls_ssl_connect(void *tcp_fd, const char *ca_cert,int ca_cert_len,const char *thing_cert,int thing_cert_len,const char *private_cert,int private_cert_len)
{
    int ret;
    unsigned int result;
    ssl_param_t *ssl_param = NULL;

    if ((int)tcp_fd < 0) 
	{
        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: invalid tcp fd - %d\r\n", (int)tcp_fd);
        return NULL;
    }

#if defined(MBEDTLS_PLATFORM_MEMORY)
    // extern void * mbedtls_mem_calloc(size_t n, size_t size);
    // extern void mbedtls_mem_free( void *ptr );
    mbedtls_platform_set_calloc_free(mbedtls_mem_calloc, mbedtls_mem_free);
#endif

#if defined(MBEDTLS_DEBUG_C)
    mbedtls_debug_set_threshold(SSL_DEBUG_LEVEL);
#endif

#if defined(MBEDTLS_THREADING_ALT)
    mbedtls_threading_set_alt(threading_mutex_init,
                              threading_mutex_free,
                              threading_mutex_lock,
                              threading_mutex_unlock);
#endif

    ssl_param = hfmem_malloc(sizeof(ssl_param_t));
	HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: malloc(%d)\r\n", sizeof(ssl_param_t));

    if (NULL == ssl_param) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: malloc(%d) fail\r\n", sizeof(ssl_param_t));
        return NULL;
    } else {
        memset(ssl_param, 0, sizeof(ssl_param_t));

        if (ca_cert && ca_cert_len > 0)
            mbedtls_x509_crt_init(&ssl_param->ca_cert);
        
        if(thing_cert && thing_cert_len > 0)
            mbedtls_x509_crt_init(&ssl_param->owncert);

        if(private_cert && private_cert_len > 0)
            mbedtls_pk_init(&ssl_param->pkey);

        mbedtls_ssl_config_init(&ssl_param->conf);
        mbedtls_ssl_init(&ssl_param->ssl);
        ssl_param->magic = SSL_PARAM_MAGIC;
        mbedtls_net_init(&ssl_param->net);
        mbedtls_net_init(&ssl_param->client_fd);
    }

    /*
     * Initialize the connection
     */
    ssl_param->net.fd = (int)tcp_fd;

    /*
     * Initialize certificates
     */
#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(10, "[SSL] ...... Loading the CA root certificate ... \r\n");
#endif

    if (ca_cert && ca_cert_len > 0) 
	{
		HF_Debug(10, "[SSL] ...... Loading the rsa\r\n");
        ret = mbedtls_x509_crt_parse(&ssl_param->ca_cert,(unsigned char *)ca_cert, (size_t)ca_cert_len);
        if (ret < 0)
		{
            HF_Debug(10, "[SSL] ssl_connect: root parse failed- 0x%x\r\n", -ret);
            goto _err;
        } 
    }

    if(thing_cert && thing_cert_len > 0)
    {
        ret = mbedtls_x509_crt_parse(&ssl_param->owncert, (unsigned char *)thing_cert,(size_t)thing_cert_len);
        if (ret < 0)
        {
            HF_Debug(10, "[SSL] ssl_connect: x509 parse failed- 0x%x\r\n", -ret);
            goto _err;
        }
    }

    if(private_cert && private_cert_len > 0)
    {
        ret = mbedtls_pk_parse_key(&ssl_param->pkey, (unsigned char *)private_cert, private_cert_len,NULL, 0);
        if (ret != 0)
        {
            HF_Debug(10, "[SSL] ssl_connect: x509 parse failed- 0x%x\r\n", -ret);
            goto _err;
        }
    }

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ok (skipped)\r\n");
#endif
    /*
     * setup stuff
     */
#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ...... Setting up the SSL/TLS structure ... \r\n");
#endif

    ret = mbedtls_ssl_config_defaults(
              &ssl_param->conf,
              MBEDTLS_SSL_IS_CLIENT,
              MBEDTLS_SSL_TRANSPORT_STREAM,
              MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0)
	{
        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: set ssl config failed - %d\r\n", ret);
        goto _err;
    }

#if defined(CONFIG_SSL_DEBUG)
   HF_Debug(DEBUG_SSL, "[SSL] ok\r\n");
#endif

    if (ca_cert && ca_cert_len > 0)
	{
        mbedtls_ssl_conf_authmode(&ssl_param->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
        mbedtls_ssl_conf_ca_chain(&ssl_param->conf, &ssl_param->ca_cert, NULL);

        if(thing_cert && thing_cert_len > 0 && private_cert && private_cert_len > 0)
		    mbedtls_ssl_conf_own_cert(&ssl_param->conf, &ssl_param->owncert, &ssl_param->pkey);
    }
    else
        mbedtls_ssl_conf_authmode(&ssl_param->conf, MBEDTLS_SSL_VERIFY_NONE);
    
    mbedtls_ssl_conf_rng(&ssl_param->conf, ssl_random, NULL);

#if defined(MBEDTLS_DEBUG_C)
    mbedtls_ssl_conf_dbg(&ssl_param->conf, ssl_debug, NULL);
#endif

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
    // ret = mbedtls_ssl_conf_max_frag_len(&ssl_param->conf, MBEDTLS_SSL_MAX_FRAG_LEN_4096);
    // if (ret != 0) 
	// {
    //     HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_conf_max_frag_len returned - %d\r\n", ret);
    //     goto _err;
    // }
#endif
    ret = mbedtls_ssl_setup(&ssl_param->ssl, &ssl_param->conf);
    if (ret != 0)
	{
        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_setup returned - %d\r\n", ret);
        goto _err;
    }
    
    mbedtls_ssl_set_bio(&ssl_param->ssl, &ssl_param->net, ssl_send, ssl_recv, NULL);
    /*
     * handshake
     */
#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ...... Performing the SSL/TLS handshake ... \r\n");
#endif
  /*if(ret = mbedtls_ssl_get_record_expansion(&ssl_param->ssl) >= 0)
  {
      HF_Debug("    [ Record expansion is %d ]\n", ret);
  }	
  else
  {
   	  HF_Debug("    [ Record expansion is unknown (compression) ]\n");
  }*/
	while ((ret = mbedtls_ssl_handshake(&ssl_param->ssl)) != 0)
	{
	    if ((ret != MBEDTLS_ERR_SSL_WANT_READ) && (ret != MBEDTLS_ERR_SSL_WANT_WRITE))
		{
	        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: mbedtls_ssl_handshake returned -0x%x\r\n", -ret);
	        goto _err;
	    }
	}
#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ok\r\n");
#endif

    /*
     * verify the server certificate
     */
#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ...... Verifying peer X.509 certificate ... \r\n");
#endif

    result = mbedtls_ssl_get_verify_result(&ssl_param->ssl);
    if (result != 0) 
	{
        HF_Debug(DEBUG_SSL, "[SSL] ssl_connect: verify result not confirmed - %d\r\n", result);
        goto _err;
    }

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ok\r\n");
#endif

    return (void *)ssl_param;

_err:
    if (ssl_param != NULL) 
	{
        if (ca_cert && ca_cert_len > 0) 
            mbedtls_x509_crt_free(&ssl_param->ca_cert);

        if(thing_cert && thing_cert_len > 0)
            mbedtls_x509_crt_free(&ssl_param->owncert);

        if(private_cert && private_cert_len > 0)
            mbedtls_pk_free(&ssl_param->pkey);

        mbedtls_ssl_free(&ssl_param->ssl);
        mbedtls_ssl_config_free(&ssl_param->conf);

        hfmem_free(ssl_param);
        ssl_param = NULL;
    }

    return NULL;
}

void *app_mbedtls_ssl_server(char *srv_ip,char *srv_port,const char *ca_cert,int ca_cert_len,const char *srv_cert,int srv_cert_len,const char *pkey,int pkey_len)
{
    int ret = 0;
    ssl_param_t *ssl_param = NULL;

    ssl_param = hfmem_malloc(sizeof(ssl_param_t));
    if(ssl_param == NULL)
        return NULL;
    
    memset(ssl_param,0,sizeof(ssl_param_t));

#if defined(MBEDTLS_PLATFORM_MEMORY)
    mbedtls_platform_set_calloc_free(mbedtls_mem_calloc, mbedtls_mem_free);
#endif
    if(ca_cert && ca_cert_len > 0)
        mbedtls_x509_crt_init(&ssl_param->ca_cert);

    if(srv_cert && srv_cert_len > 0)
        mbedtls_x509_crt_init(&ssl_param->owncert);
    
    if(pkey && pkey_len > 0)
        mbedtls_pk_init(&ssl_param->pkey);

    mbedtls_net_init(&ssl_param->net);
    mbedtls_net_init(&ssl_param->client_fd);
    mbedtls_ssl_config_init(&ssl_param->conf);
    mbedtls_ssl_init(&ssl_param->ssl);
    ssl_param->magic = SSL_PARAM_MAGIC;

    if(ca_cert && ca_cert_len > 0)
    {
        ret = mbedtls_x509_crt_parse(&ssl_param->ca_cert,(unsigned char *)ca_cert,(size_t)ca_cert_len);
        if(ret != 0)
            goto _err;
    }

    if(srv_cert && srv_cert_len > 0)
    {
        ret = mbedtls_x509_crt_parse(&ssl_param->owncert,(unsigned char *)srv_cert,(size_t)srv_cert_len);
        if(ret != 0)
            goto _err;
    }

    if(pkey && pkey_len > 0)
    {
        ret = mbedtls_pk_parse_key(&ssl_param->pkey,(unsigned char *)pkey,(size_t)pkey_len,NULL,0);
        if(ret != 0)
            goto _err;
    }

    ret = mbedtls_net_bind(&ssl_param->net,srv_ip,srv_port,MBEDTLS_NET_PROTO_TCP);
    if(ret != 0)
        goto _err;

    ret = mbedtls_ssl_config_defaults(&ssl_param->conf,
                                MBEDTLS_SSL_IS_SERVER,
                                MBEDTLS_SSL_TRANSPORT_STREAM,
                                MBEDTLS_SSL_PRESET_DEFAULT);
    if(ret != 0)
        goto _err;

    mbedtls_ssl_conf_rng(&ssl_param->conf, ssl_random, NULL);

    mbedtls_ssl_conf_ca_chain(&ssl_param->conf, &ssl_param->ca_cert, NULL);

    ret = mbedtls_ssl_conf_own_cert(&ssl_param->conf,&ssl_param->owncert,&ssl_param->pkey);
    if(ret != 0)
        goto _err;

    ret = mbedtls_ssl_setup(&ssl_param->ssl,&ssl_param->conf);
    if(ret != 0)
        goto _err;

_reset:
    mbedtls_net_free(&ssl_param->client_fd);

    mbedtls_ssl_session_reset(&ssl_param->ssl);

    ret = mbedtls_net_accept(&ssl_param->net,&ssl_param->client_fd,NULL,0,NULL);
    if(ret != 0)
        goto _err;
    
    mbedtls_ssl_set_bio(&ssl_param->ssl, &ssl_param->client_fd, ssl_send, ssl_recv, NULL);

    while((ret = mbedtls_ssl_handshake(&ssl_param->ssl)) != 0)
    {
        if(ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
            goto _reset;
    }

    return ssl_param;
    
_err:
    if(ssl_param != NULL) 
	{
        mbedtls_ssl_close_notify(&ssl_param->ssl);
        mbedtls_net_free(&ssl_param->net);
        mbedtls_net_free(&ssl_param->client_fd);
        mbedtls_x509_crt_free(&ssl_param->ca_cert);
        mbedtls_x509_crt_free(&ssl_param->owncert);
        mbedtls_pk_free(&ssl_param->pkey);
        mbedtls_ssl_free(&ssl_param->ssl);
        mbedtls_ssl_config_free(&ssl_param->conf);
        hfmem_free(ssl_param);
        ssl_param = NULL;
    }

    return NULL;
}

int app_mbedtls_ssl_send(void *ssl, const char *buffer, int length)
{
    int ret;
    int total_len = 0;
    int retry = 0;
    ssl_param_t *ssl_param;

    if (ssl == NULL || buffer == NULL || length <= 0) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl_send: invalid input args\n");
        return -1;
    }

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ...... > Send to server: ");
#endif

    ssl_param = (ssl_param_t *)ssl;
    if (ssl_param->magic != SSL_PARAM_MAGIC) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl_send: invalid magic - 0x%x\n", ssl_param->magic);
        return -1;
    }

    do {
        ret = mbedtls_ssl_write(&ssl_param->ssl,
                                (const unsigned char *)buffer, (size_t)(length - total_len));
        if (ret > 0) {
            total_len += ret;
            buffer += ret;
        } else if (ret == 0) {
            /* EOF */
            break;
        } else {
            if (ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
                retry ++;
                msleep(10);
                continue;
            }

            if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
                /*
                 * indicate that write already complete,
                 * if call read again, it will return 0(EOF))
                 */
                break;
            }

            HF_Debug(DEBUG_SSL, "[SSL] ssl_send: mbedtls_ssl_write failed - 0x%x\n", -ret);

            return -1;
        }
    } while (total_len < length && retry < 10);

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] %d bytes sent retry %d\n", ret, retry);
#endif

#if defined(CONFIG_SSL_DEBUG)
    int i = 0;
    unsigned char *data = (unsigned char *)buffer;

    HF_Debug(DEBUG_SSL, "[SSL] send msg(%d %d): \n", length, ret);
    for (i = 0; i < ret; i++) {
        HF_Debug(DEBUG_SSL, "[SSL]  %02x ", data[i]);
    }
    HF_Debug(DEBUG_SSL, "[SSL] \n");
#endif

    return ret < 0 ? -1 : total_len;
}

int app_mbedtls_ssl_recv(void *ssl, char *buffer, int length)
{
    int ret;
    int total_len = 0;
    ssl_param_t *ssl_param;

    if (ssl == NULL || buffer == NULL || length <= 0) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl_recv: invalid input args\n");
        return -1;
    } else {
        ssl_param = (ssl_param_t *)ssl;
        if (ssl_param->magic != SSL_PARAM_MAGIC) {
            HF_Debug(DEBUG_SSL, "[SSL] ssl_recv: invalid magic - 0x%x\n", ssl_param->magic);
            return -1;
        }
    }

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] ...... < Read from server: ");
#endif

    do {
        ret = mbedtls_ssl_read(&ssl_param->ssl,
                               (unsigned char *)buffer, (size_t)length);
        if (ret > 0) {
            total_len = ret;
            break;
        } else if (ret == 0) {
            /* EOF */
            return 0;
        } else {
            if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
                return -EAGAIN;
            }

            if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
                /*
                 * indicate that read already complete,
                 * if call read again, it will return 0(EOF))
                 */
                break;
            }

            HF_Debug(DEBUG_SSL, "[SSL] ssl_recv: mbedtls_ssl_read failed - 0x%x\n", -ret);

            return -1;
        }
    } while (0);

#if defined(CONFIG_SSL_DEBUG)
    HF_Debug(DEBUG_SSL, "[SSL] %d bytes read\n", total_len);
#endif

#if defined(CONFIG_SSL_DEBUG)
    int i = 0;
    unsigned char *data = (unsigned char *)buffer;

    HF_Debug(DEBUG_SSL, "[SSL] recv msg(%d %d): \n", length, total_len);
    for (i = 0; i < total_len; i++) {
        HF_Debug(DEBUG_SSL, "[SSL]  %02x ", data[i]);
    }
    HF_Debug(DEBUG_SSL, "[SSL] \n");
#endif

    return total_len;
}

int app_mbedtls_ssl_close(void *ssl)
{
    ssl_param_t *ssl_param;

    if (ssl == NULL) {
        return 0;
    }

    ssl_param = (ssl_param_t *)ssl;
    if (ssl_param->magic != SSL_PARAM_MAGIC) {
        HF_Debug(DEBUG_SSL, "[SSL] ssl_close: invalid magic - 0x%x\n", ssl_param->magic);
        return -1;
    }

    mbedtls_ssl_close_notify(&ssl_param->ssl);
    mbedtls_net_free(&ssl_param->net);
    mbedtls_net_free(&ssl_param->client_fd);
    mbedtls_x509_crt_free(&ssl_param->ca_cert);
	mbedtls_x509_crt_free(&ssl_param->owncert);
    mbedtls_pk_free(&ssl_param->pkey);
    mbedtls_ssl_free(&ssl_param->ssl);
    mbedtls_ssl_config_free(&ssl_param->conf);

    memset(ssl_param, 0, sizeof(ssl_param_t));
    hfmem_free(ssl_param);

#if defined(MBEDTLS_THREADING_ALT)
    mbedtls_threading_free_alt();
#endif

    return 0;
}

