 /* websocketclient.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <string.h>
#include "hsf.h"
#include "websocketclient.h"


#define WEBSOCKET_DEBUG u_printf

#define WEBSOCKET_BUFFER_PRE_PADDING 14


static const char encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			     "abcdefghijklmnopqrstuvwxyz0123456789+/";
/*static const char decode[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW"
			     "$$$$$$XYZ[\\]^_`abcdefghijklmnopq";*/

int websockets_b64_encode_string(const char *in, int in_len, char *out, int out_size)
{
	unsigned char triple[3];
	int i;
	int len;
	int line = 0;
	int done = 0;

	while (in_len) {
		len = 0;
		for (i = 0; i < 3; i++) {
			if (in_len) {
				triple[i] = *in++;
				len++;
				in_len--;
			} else
				triple[i] = 0;
		}
		if (!len)
			continue;

		if (done + 4 >= out_size)
			return -1;

		*out++ = encode[triple[0] >> 2];
		*out++ = encode[((triple[0] & 0x03) << 4) |
					     ((triple[1] & 0xf0) >> 4)];
		*out++ = (len > 1 ? encode[((triple[1] & 0x0f) << 2) |
					     ((triple[2] & 0xc0) >> 6)] : '=');
		*out++ = (len > 2 ? encode[triple[2] & 0x3f] : '=');

		done += 4;
		line += 4;
	}

	if (done + 1 >= out_size)
		return -1;

	*out++ = '\0';

	return done;
}

static int websockets_recv_handshake(int fd, char *buf, int len, int timeout_ms)
{
	fd_set fdR;
	struct timeval timeout;
	int ret, tmpLen, recvLen = 0;
	
	while(1)
	{
		FD_ZERO(&fdR);
		FD_SET(fd,&fdR);
		if(recvLen <= 0)
		{
			timeout.tv_sec = timeout_ms/1000;
			timeout.tv_usec = timeout_ms%1000*1000;
		}
		else
		{
			//fast close
			timeout.tv_sec = 0;
			timeout.tv_usec =500*1000;
		}

		ret = select(fd+1, &fdR, NULL, NULL, &timeout);	
		if (ret <= 0)
		{
			break;
		}
		else if(FD_ISSET(fd, &fdR))
		{
			tmpLen = recv(fd, buf, len-recvLen, 0);
			if(tmpLen <= 0)
				return -1;

			recvLen += tmpLen;
			if(recvLen > 4 && buf[recvLen-4] == '\r' && buf[recvLen-3] =='\n' && buf[recvLen-2] == '\r' && buf[recvLen-1] =='\n')
			{
				return recvLen;
			}
		}
	}

	return  recvLen;
}

static void websockets_generate_handshake_key(char *websocket_key)
{
	char hash[20];
	int n;
	
	for (n = 0; n < 16; n++)
		hash[n] = (unsigned char)rand();

	websockets_b64_encode_string(hash, 16, websocket_key, WEBSOCKET_KEY_MAX_LEN);
}

static void websockets_generate_handshake_response_key(char *websocket_key, char *websocket_response_key)
{
	sprintf(websocket_response_key, "%s258EAFA5-E914-47DA-95CA-C5AB0DC85B11", websocket_key);
}

static void websockets_xor_data(unsigned char *mask, char *data, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		data[i] = (char) (data[i] ^ mask[i % 4]);
	}
}

WEBSOCKET_C * websocket_client_new(char *host, char *path, char *protocol, int version)
{
	WEBSOCKET_C *websocket = NULL;

	if(strlen(host) <=0 || strlen(host) > WEBSOCKET_HOST_MAX_LEN)
		return NULL;
	if(strlen(path) <=0 || strlen(path) > WEBSOCKET_PATH_MAX_LEN)
		return NULL;
	if(strlen(protocol) <=0 || strlen(protocol) > WEBSOCKET_PROTOCOL_MAX_LEN)
		return NULL;
	if(version != WEBSOCKET_PROTOCOL_VERSION)
		return NULL;
	
	if((websocket = (WEBSOCKET_C *)hfmem_malloc(sizeof(WEBSOCKET_C))) == NULL)
		return NULL;
	
	memset(websocket, 0, sizeof(WEBSOCKET_C));
	strcpy(websocket->host, host);
	strcpy(websocket->path, path);
	strcpy(websocket->protocol, protocol);
	websocket->version = version;
	websocket->buf_max = WEBSOCKET_BUF_MAX_LEN;
	websocket->data_type = WEBSOCKET_DATA_TXT;
	websocket->need_mask = WEBSOCKET_NEED_MASK;
	websocket->mask[0] = (unsigned char)rand();
	websocket->mask[1] = (unsigned char)rand();
	websocket->mask[2] = (unsigned char)rand();
	websocket->mask[3] = (unsigned char)rand();

	return websocket;
}

int websocket_client_free(WEBSOCKET_C *websocket)
{
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;
	
	hfmem_free(websocket);
	return WEBSOCKET_SUCCESS;
}
	
int websocket_client_set_fd(WEBSOCKET_C *websocket, int fd)
{
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;

	websocket->fd = fd;
	return WEBSOCKET_SUCCESS;
}

int websocket_client_connect(WEBSOCKET_C *websocket, char *local_ip)
{
	char *p = websocket->buf;
	int ret;
	
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;

	/* create handshake packet */
	websockets_generate_handshake_key(websocket->key);
	
	p += sprintf(p, "GET %s HTTP/1.1\r\n", websocket->path);
	p += sprintf(p, "Host: %s\r\n", websocket->host);
	p += sprintf(p, "Pragma: no-cache\r\n");
	p += sprintf(p, "Cache-Control: no-cache\r\n");
	p += sprintf(p, "Upgrade: websocket\r\n");
	p += sprintf(p, "Connection: Upgrade\r\n");
	p += sprintf(p, "Sec-WebSocket-Key: %s\r\n", websocket->key);
	
	p += sprintf(p, "Origin: http://%s\r\n", local_ip);
	p += sprintf(p, "Sec-WebSocket-Protocol: %s\r\n", websocket->protocol);
	p += sprintf(p, "Sec-WebSocket-Version: %d\r\n", websocket->version);
	//p += sprintf(p, "Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits\r\n");
	p += sprintf(p, "\r\n");

	/* prepare the expected server accept response */
	websockets_generate_handshake_response_key(websocket->key, websocket->key_response);

	/* send handshake packet */
	send(websocket->fd, websocket->buf, strlen(websocket->buf), 0);

	/* recv handshake packet */
	ret = websockets_recv_handshake(websocket->fd, websocket->buf, websocket->buf_max, 5000);
	if(ret <= 0)
	{
		websocket->errno = WEBSOCKET_ERRNO_NORECV_HANDSHAKE;
		return WEBSOCKET_FAILURE;
	}

	websocket->buf[ret] = '\0';
	if (memcmp(websocket->buf, "HTTP/1.1 101", strlen("HTTP/1.1 101")) &&
		memcmp(websocket->buf, "HTTP/1.0 101", strlen("HTTP/1.0 101")))
	{
		websocket->errno = WEBSOCKET_ERRNO_HANDSHAKE_FAILURE;
		return WEBSOCKET_FAILURE;
	}

	return WEBSOCKET_SUCCESS;
}

int websocket_client_write(WEBSOCKET_C *websocket, char *buf, int len)
{
	if(websocket==NULL)
		return 0;
	
	unsigned char head[WEBSOCKET_BUFFER_PRE_PADDING]={0x80, 0x00};
	int tmpLen, sendLen = 0, headLen = 2;
	
	head[0] |= websocket->data_type;
	if(websocket->need_mask)
	{
		head[1] |= 0x80;
	}

	if(len < 126)
	{
		head[1] |= len;
	}
	else if(len <= 65535)
	{
		head[1] |= 126;
		head[headLen] = len/256;
		head[headLen+1] = len%256;
		headLen += 2;
	}
	else
	{
		websocket->errno = WEBSOCKET_ERRNO_SEND_PACKET_OVERFLOW;
		return WEBSOCKET_FAILURE;
	}

	if(websocket->need_mask)
	{
		memcpy(head+headLen, websocket->mask, 4);
		headLen += 4;
	}

	/* add head */
	memcpy(websocket->buf, head, headLen);
	if(len - sendLen > websocket->buf_max - WEBSOCKET_BUFFER_PRE_PADDING)
		tmpLen = websocket->buf_max - WEBSOCKET_BUFFER_PRE_PADDING;
	else
		tmpLen = len - sendLen;
	
	memcpy(websocket->buf+headLen, buf, tmpLen);
	websockets_xor_data(websocket->mask, websocket->buf+headLen, tmpLen);
	if(send(websocket->fd, websocket->buf, headLen+tmpLen, 0) < headLen+tmpLen)
	{
		websocket->errno = WEBSOCKET_ERRNO_SEND_FAILURE;
		return WEBSOCKET_FAILURE;
	}
	sendLen += (headLen+tmpLen);
	
	while(sendLen < len)
	{
		if(len - sendLen > websocket->buf_max)
			tmpLen = websocket->buf_max;
		else
			tmpLen = len - sendLen;

		memcpy(websocket->buf, buf+sendLen, tmpLen);
		websockets_xor_data(websocket->mask, websocket->buf, tmpLen);

		if(send(websocket->fd, websocket->buf, tmpLen, 0) < tmpLen)
			break;
		sendLen += tmpLen;
	}
	
	return len;
}

int websocket_client_read(WEBSOCKET_C *websocket, char *buf, int len)
{
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;
	
	int recvLen = recv(websocket->fd, websocket->buf, WEBSOCKET_BUF_MAX_LEN, 0);
	if (recvLen < 2)
	{
		websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_TOO_SMALL;
		return WEBSOCKET_FAILURE;
	}

	if (!(websocket->buf[0] & 0x80))
	{
		websocket->errno = WEBSOCKET_ERRNO_UNSUPPORT_MULTI_PACKET;
		return WEBSOCKET_FAILURE;
	}
	
	int opcode = websocket->buf[0] & 0x0F;
	int is_masked = (websocket->buf[1]&0x80) ? 1 : 0;
	int dataLen = websocket->buf[1] & 0x7F;
	int headLen = 2;
	
	if (opcode == 0x08)
	{
		websocket->errno = WEBSOCKET_ERRNO_CLOSED;
		return WEBSOCKET_FAILURE;
	}
	else if (opcode == 0x09)
	{
		char data[2]={0x0A, 0x00};
		send(websocket->fd, data, 2, 0);
		return WEBSOCKET_SUCCESS;
	}
	else if (opcode == 0x0A)
	{
		return WEBSOCKET_SUCCESS;
	}
	
	if (dataLen == 127)
	{
		websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_OVERFLOW;
		return WEBSOCKET_FAILURE;
	}
	else if (dataLen == 126)
	{
		if(recvLen >= 4)
		{
			dataLen = (int)((websocket->buf[2] & 0xFF) << 8 | (websocket->buf[3] & 0xFF));
			headLen = 4;
		}
		else
		{
			websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_TOO_SMALL;
			return WEBSOCKET_FAILURE;
		}
	}

	if (dataLen > (websocket->buf_max - 4))
	{
		websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_PART;
		return WEBSOCKET_FAILURE;
	}
	
	unsigned char mask[4];
	if(is_masked)
	{
		if(recvLen >= headLen+4)
		{
			memcpy(mask, websocket->buf+headLen, 4);
			headLen += 4;
		}
		else
		{
			websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_TOO_SMALL;
			return WEBSOCKET_FAILURE;
		}
		dataLen =  dataLen>recvLen-headLen ? (recvLen-headLen) : dataLen;
		websockets_xor_data(mask, websocket->buf+headLen, dataLen);
	}
	
	if(len < dataLen)
	{
		websocket->errno = WEBSOCKET_ERRNO_RECV_PACKET_PART;
	}
	else
		len = dataLen;
	
	memcpy(buf, websocket->buf+headLen, len);
	return len;
}

int websocket_client_ping(WEBSOCKET_C *websocket)
{
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;
	
	char data[2]={0x09, 0x00};
	if(send(websocket->fd, data, 2, 0) < 2)
		return WEBSOCKET_FAILURE;
	else
		return WEBSOCKET_SUCCESS;
};

int websocket_client_get_error(WEBSOCKET_C *websocket)
{
	if(websocket==NULL)
		return WEBSOCKET_FAILURE;
	
	return websocket->errno;
}

