#ifndef _SNLINK_PLATFORM_H_
#define _SNLINK_PLATFORM_H_


#include "snlink_defs.h"

#define INADDR_ANY_SN          ((uint32_t)0x00000000UL)
#ifdef __cplusplus
extern "C" {
#endif


void * sn_platform_malloc(uint32_t size);
void sn_platform_free(void *ptr);
void *sn_platform_memset(void* ptr, int value, unsigned int num);
void *sn_platform_memcpy(void* dst, const void* src, unsigned int num);
int sn_platform_memcmp(const void* ptr1, const void* ptr2, unsigned int num);

int sn_platform_printf(const char *fmt, ...);
void sn_platform_msleep(uint32_t ms);
void sn_platform_reboot(void);

int sn_platform_mutex_init(SN_THREAD_MUTEX  *pMutex);
int sn_platform_mutex_lock(SN_THREAD_MUTEX  *pMutex);
int sn_platform_mutex_unlock(SN_THREAD_MUTEX  *pMutex);
void sn_platform_mutex_destroy(SN_THREAD_MUTEX  *pMutex);

int sn_platform_queue_create(SN_QUEUE_HANDLE *pQueue, uint32_t queue_num, uint32_t item_size);
int sn_platform_queue_send(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts);
int sn_platform_queue_recv(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts);
int sn_platform_queue_destory(SN_QUEUE_HANDLE *pQueue);

int sn_platform_config_read(char *pStrName, char *pData, int dataLen);
int sn_platform_config_write(char *pStrName, char *pData, int dataLen);

int sn_platform_timer_create( SNTIMER_HANDLE_T *htimer, const char *name, uint32_t period, uint8_t auto_reload, SN_TIMER_CALLBACK p_callback, void* timer_arg);
void sn_platform_timer_delete( SNTIMER_HANDLE_T *htimer);
int sn_platform_timer_start(SNTIMER_HANDLE_T *htimer);
void sn_platform_timer_stop(SNTIMER_HANDLE_T *htimer);
int sn_platform_timer_changeperiod(SNTIMER_HANDLE_T *htimer,int32_t new_period);

void sn_platform_gettimeofday(struct sn_timeval* tv);
unsigned int sn_platform_time(void);

int sn_platform_gethostbyname(char *hostname, sn_in_addr *inaddr);
int sn_platform_socket(int domain, int type, int protocol);
int sn_platform_connect(int s, const sn_sockaddr *name, uint32_t namelen);
int sn_platform_send(int s, const void *dataptr, int size, int flags);
int sn_platform_recv(int s, void *mem, int len, int flags);
int sn_platform_select(int maxfdp1, sn_fd_set *readset, sn_fd_set *writeset, sn_fd_set *exceptset, struct sn_timeval *timeout);
int sn_platform_close(int s);
int sn_platform_sendto(int s, const void *data, uint32_t size, int flags, const sn_sockaddr *to, uint32_t tolen);
int sn_platform_recvfrom(int s, void *mem, uint32_t len, int flags, sn_sockaddr *from, uint32_t *fromlen);
int sn_platform_bind(int s, const sn_sockaddr *my_addr, uint32_t addrlen);
int sn_platform_setsockopt(int socket, int level, int option_name, const void *option_value, int option_len);
uint32_t sn_platform_htonl(uint32_t hostlong);
uint32_t sn_platform_ntohl(uint32_t netlong);
uint16_t sn_platform_htons(uint16_t hostshort);
uint16_t sn_platform_ntohs(uint16_t netshort);
int sn_platform_blesend(const void *data, uint32_t size);
void sn_platform_FD_SET(int handle, sn_fd_set *sn_set);
void sn_platform_FD_CLR(int handle, sn_fd_set *sn_set);
int sn_platform_FD_ISSET(int handle, sn_fd_set *sn_set);
void sn_platform_FD_ZERO(sn_fd_set *sn_set);

#ifdef __cplusplus
}
#endif

#endif
