 /* websocketclient.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _WEBSOCKETCLIENT_H_
#define _WEBSOCKETCLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif


enum
{
	WEBSOCKET_FAILURE         =  -1,
	WEBSOCKET_SUCCESS         =  0,
};

enum
{
	WEBSOCKET_ERRNO_NORECV_HANDSHAKE         =  0,
	WEBSOCKET_ERRNO_HANDSHAKE_FAILURE         =  1,
	WEBSOCKET_ERRNO_SEND_PACKET_OVERFLOW,
	WEBSOCKET_ERRNO_SEND_FAILURE,
	WEBSOCKET_ERRNO_RECV_PACKET_OVERFLOW,
	WEBSOCKET_ERRNO_UNSUPPORT_MULTI_PACKET,
	WEBSOCKET_ERRNO_RECV_PACKET_TOO_SMALL,
	WEBSOCKET_ERRNO_RECV_PACKET_PART,
	WEBSOCKET_ERRNO_CLOSED
};


#define WEBSOCKET_HOST_MAX_LEN 128
#define WEBSOCKET_PATH_MAX_LEN 128
#define WEBSOCKET_PROTOCOL_MAX_LEN 128
#define WEBSOCKET_KEY_MAX_LEN 64
#define WEBSOCKET_BUF_MAX_LEN 1460

#define WEBSOCKET_PROTOCOL_VERSION 13

enum
{
	WEBSOCKET_DATA_ATTACH         =  0,
	WEBSOCKET_DATA_TXT         =  1,
	WEBSOCKET_DATA_HEX
};

enum
{
	WEBSOCKET_NONEED_MASK         =  0,
	WEBSOCKET_NEED_MASK         =  1,
};

typedef struct {
	int fd;
	char host[WEBSOCKET_HOST_MAX_LEN+1];
	char path[WEBSOCKET_PATH_MAX_LEN+1];
	char protocol[WEBSOCKET_PROTOCOL_MAX_LEN+1];
	int version;
	int data_type;
	int need_mask;
	unsigned char mask[4];
	int errno;
	int buf_max;
	char buf[WEBSOCKET_BUF_MAX_LEN+1];

	char key[WEBSOCKET_KEY_MAX_LEN+1];
	char key_response[WEBSOCKET_KEY_MAX_LEN*2+1];
}WEBSOCKET_C;


WEBSOCKET_C * websocket_client_new(char *host, char *path, char *protocol, int version);

int websocket_client_free(WEBSOCKET_C *websocket);
	
int websocket_client_set_fd(WEBSOCKET_C *websocket, int fd);

int websocket_client_connect(WEBSOCKET_C *websocket, char *local_ip);

int websocket_client_write(WEBSOCKET_C *websocket, char *buf, int len);

int websocket_client_read(WEBSOCKET_C *websocket, char *buf, int len);

int websocket_client_ping(WEBSOCKET_C *websocket);

int websocket_client_get_error(WEBSOCKET_C *websocket);


#ifdef __cplusplus
}
#endif

#endif
