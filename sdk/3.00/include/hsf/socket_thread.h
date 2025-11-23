/* socket_thread.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _SOCKET_THREAD_H_
#define _SOCKET_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif


#define SOCK_MAX_RECV_NUM 2800//1500
#define SOCK_MAX_CLIENT_NUM 5

#define SOCK_ONE_PACK_SIZE 1400
typedef struct CLIENT_SOCKET
{
	int fd;
	uint32_t time_to;
	struct sockaddr_in addr;
	uint8_t active;
}client_socket;

typedef struct SOCKET_THREAD_HANDLE
{
	int m2m_socket;
	int m2m_active;
	char m2m_net_recv[SOCK_MAX_RECV_NUM+32];
	int m2m_is_connected;
	int m2m_need_reconnect;
	int m2m_disable_connect;
	
	int netrecvnum;
	int netreadnum;
	int netnum;
	
	int m2m_client_num;
	client_socket m2m_client_sockets[SOCK_MAX_CLIENT_NUM];

	struct sockaddr_in m2m_udp_toaddr;
	void *m2m_tls_handle;
}socket_handle_t;

extern socket_handle_t *socket_thread_handle;


/**
 * @brief start socketA.
 *
 * @param[in] uxpriority: the uxpriority of socketa thread
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI start_socketa(uint32_t uxpriority);

/**
 * @brief check whether or not socketA is started.
 *
 * @param[in] None
 * @return[out] 0-not start, 1-have started
 * @see None.
 * @note None.
 */
int HSF_IAPI socketa_is_started(void);

/**
 * @brief send data to SOCKETA.
 *
 * @param[in] data: the data buffer you want send
 *			 len: the size of send buffer
 * @return[out] the size send out by SOCKETA
 * @see None.
 * @note None.
 */
int HSF_IAPI socketa_send(char *data, uint32_t len);

/**
 * @brief check the string is a valid IP address.
 *
 * @param[in] ipaddr: the ip address string
 * @return[out] 0-not a IP address, 1-is a IP address
 * @see None.
 * @note None.
 */
int HSF_IAPI is_ipaddress(const char * ipaddr);

/**
 * @brief check the string is a valid IP broadcast address.
 *
 * @param[in] ipaddr: the ip address string
 *			 maskaddr: the mask address string
 * @return[out] 0-not a IP broadcast address, 1-is a IP broadcast address
 * @see None.
 * @note None.
 */
int HSF_IAPI is_broadcast_ip(const char *ipaddr, const char *maskaddr);

/**
 * @brief check socket is valid.
 *
 * @param[in] socket: the socket handled
 * @return[out] 0-invalid, 1-is a valid socket
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_is_valid(int socket);

/**
 * @brief close socket and set socket invalid.
 *
 * @param[in] socket: a pointer to socket handled
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_close(int *socket);

/**
 * @brief create a tcp client socket and connect to server.
 *
 * @param[in] hostname: the host name, support ip address and domain name
 *			 port: the port, <65535
 * @return[out] >= 0-the number of create socket, means create and connect success, <0-failed, as follow value
 * ==========================================================
 * | -1            | dns failed if 'hostname' is domain name|
 * |--------------------------------------------------------|
 * | -2            | create socket fail                     |
 * |--------------------------------------------------------|
 * | -3            | connect fail                           |
 * ==========================================================
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_create_tcp_client(char *hostname, unsigned short port);

/**
 * @brief create a tcp server socket.
 *
 * @param[in] port: the local listen port, <65535
 *			 listen: listen number
 * @return[out] >= 0-the number of create socket, means create socket success, <0-failed, as follow value
 * ==========================================================
 * | -1            | create socket fail   |
 * |--------------------------------------------------------|
 * | -2            | bind socket fail                     |
 * |--------------------------------------------------------|
 * | -3            | listen socket fail                             |
 * ==========================================================
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_create_tcp_server(unsigned short port, int listen);

/**
 * @brief create a udp socket.
 *
 * @param[in] port: the local port, <65535
 * @return[out] >= 0-the number of create socket, means create socket success, <0-failed, as follow value
 * ==========================================================
 * | -1            | create socket fail                     |
 * |--------------------------------------------------------|
 * | -2            | bind socket fail                            |
 * ==========================================================
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_create_udp(unsigned short port);
int HSF_IAPI sock_create_udp_igmp(char *hostname,unsigned short port);


/**
 * @brief transform hostname to unsigned 32bit address number.
 *
 * @param[in] hostname: hostname string
 *			 addr: a pointer to store 32bit address number
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note this system is not need.
 */
int HSF_IAPI sock_hostname_to_addr(char *hostname, uint32_t *addr);

/**
 * @brief get a rand local port.
 *
 * @param[in] None
 * @return[out] local port, the range is [1000-65535]
 * @see None.
 * @note this system is not need.
 */
unsigned short HSF_IAPI sock_get_rand_local_port(void);

/**
 * @brief enable TCP keepalive.
 *
 * @param[in] sock: the handle of socket
 *			 idle: the number of seconds a connection needs to be idle before TCP begins sending out keep-alive probes
 *			 interval: the number of seconds between TCP keep-alive probes
 *			 count: the maximum number of TCP keep-alive probes to send before giving up and killing the connection if no response is obtained from the other end
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_enable_tcp_keepalive(int sock, int idle, int interval, int count);

/**
 * @brief disable TCP keepalive.
 *
 * @param[in] sock: the handle of socket
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_disable_tcp_keepalive(int sock);

/**
 * @brief set TCP socket send timeout.
 *
 * @param[in] sock: the handle of socket
 *			 timeout: send timeout, in seconds
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_enable_tcp_sendtimeout(int sock, int timeout);

/**
 * @brief set TCP socket recv timeout.
 *
 * @param[in] sock: the handle of socket
 *			 timeout: recv timeout, in seconds
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_IAPI sock_enable_tcp_recvtimeout(int sock, int timeout);

void m2m_net_recv_buff_clean();
void mqttc_ping_thread(void* arg);

#ifdef __cplusplus
}
#endif

#endif

