/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010-2014 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */
#include <string.h>
#include "websocket/private-libwebsockets.h"

#ifdef LWS_OPENSSL_SUPPORT
int openssl_websocket_private_data_index;

LWS_VISIBLE void
libwebsockets_decode_ssl_error(void)
{
}

static int lws_context_init_client_ssl_pem_passwd_cb(char * buf, int size, int rwflag, void * userdata)
{
	struct lws_context_creation_info * info = (struct lws_context_creation_info *)userdata;
   
	const int passLen = (int)strlen(info->ssl_private_key_password);
	const int minimumLen = passLen < size ? passLen : size;
	strncpy(buf, info->ssl_private_key_password, minimumLen);
   
	if (minimumLen < size)
	{
		buf[minimumLen] = '\0';
       return minimumLen;
   }
   
    return minimumLen;
}

int lws_context_init_client_ssl(struct lws_context_creation_info *info,
			    struct libwebsocket_context *context)
{
	CYASSL_METHOD *method;

	if (info->port != CONTEXT_PORT_NO_LISTEN)
		return 0;

	//CyaSSL_Debugging_ON();

	CyaSSL_Init();
	
	method = (CYASSL_METHOD *)CyaTLSv1_2_client_method();
	if (!method) {
		//error = SSL_get_error();
		lwsl_err("problem creating ssl method.\n");
		return 1;
	}
	/* create context */
	context->ssl_client_ctx = CyaSSL_CTX_new(method);
	if (!context->ssl_client_ctx) {
		//error = SSL_get_error();
		lwsl_err("problem creating ssl context.\n");
		return 1;
	}

	CyaSSL_CTX_set_verify(context->ssl_client_ctx, SSL_VERIFY_NONE, 0);

	context->protocols[0].callback(context, NULL,
		LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS,
		context->ssl_client_ctx, NULL, 0);
	
	return 0;
}

LWS_VISIBLE int
lws_ssl_capable_read(struct libwebsocket *wsi, unsigned char *buf, int len)
{
	int n;

	if (!wsi->ssl)
		return lws_ssl_capable_read_no_ssl(wsi, buf, len);

	n = SSL_read(wsi->ssl, buf, len);
	if (n >= 0)
		return n;

	n = SSL_get_error(wsi->ssl, n);
	if (n ==  SSL_ERROR_WANT_READ || n ==  SSL_ERROR_WANT_WRITE)
		return LWS_SSL_CAPABLE_MORE_SERVICE;

	return LWS_SSL_CAPABLE_ERROR; 
}

LWS_VISIBLE int
lws_ssl_capable_write(struct libwebsocket *wsi, unsigned char *buf, int len)
{
	int n;

	if (!wsi->ssl)
		return lws_ssl_capable_write_no_ssl(wsi, buf, len);
	
	n = SSL_write(wsi->ssl, buf, len);
	if (n >= 0)
		return n;

	n = SSL_get_error(wsi->ssl, n);
	if (n == SSL_ERROR_WANT_READ || n == SSL_ERROR_WANT_WRITE) {
		if (n == SSL_ERROR_WANT_WRITE)
			lws_set_blocking_send(wsi);
		return LWS_SSL_CAPABLE_MORE_SERVICE;
	}

	return LWS_SSL_CAPABLE_ERROR;
}

LWS_VISIBLE int
lws_ssl_pending(struct libwebsocket *wsi)
{
	if (wsi->ssl)
		return SSL_pending(wsi->ssl);
	return 0;
}

LWS_VISIBLE int
lws_ssl_close(struct libwebsocket *wsi)
{
	int n;

	if (!wsi->ssl)
		return 0; /* not handled */

	n = SSL_get_fd(wsi->ssl);
	SSL_shutdown(wsi->ssl);
	compatible_close(n);
	SSL_free(wsi->ssl);

	return 1; /* handled */
}

LWS_VISIBLE void
lws_ssl_context_destroy(struct libwebsocket_context *context)
{
	if (context->ssl_client_ctx)
			SSL_CTX_free(context->ssl_client_ctx);
}
#endif