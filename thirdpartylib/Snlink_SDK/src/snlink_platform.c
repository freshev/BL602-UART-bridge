#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "snlink_platform.h"
#include <hsf.h>
#include "lwip/netdb.h"

void * sn_platform_malloc(uint32_t size)
{
    return hfmem_malloc(size);
}

void sn_platform_free(void *ptr)
{
    if(ptr == NULL)	{
        u_printf("[%s][%d] ptr == NULL \n",__FUNCTION__,__LINE__);
    }else{
        hfmem_free(ptr);
    }
}

void *sn_platform_memset(void* ptr, int value, unsigned int num)
{
    return memset(ptr, value, num);
}

void *sn_platform_memcpy(void* dst, const void* src, unsigned int num)
{
    return memcpy(dst, src, num);
}

int sn_platform_memcmp(const void* ptr1, const void* ptr2, unsigned int num)
{
    return memcmp(ptr1, ptr2, num);
}

int sn_platform_printf(const char *fmt, ...)
{
    u_printf(fmt);
    return SN_OK;

}

void sn_platform_msleep(uint32_t ms)
{
    if (ms < 10)
        ms = 10;
    
    msleep( ms );
}

void sn_platform_reboot(void)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return ;
}

int sn_platform_queue_create(SN_QUEUE_HANDLE *pQueue, uint32_t queue_num, uint32_t item_size)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

int sn_platform_queue_send(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

int sn_platform_queue_recv(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

int sn_platform_queue_destory(SN_QUEUE_HANDLE *pQueue)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}


int sn_platform_config_read(char *pStrName, char *pData, int dataLen)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

int sn_platform_config_write(char *pStrName, char *pData, int dataLen)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}


int sn_platform_timer_create( SNTIMER_HANDLE_T *htimer, const char *name, uint32_t period, uint8_t auto_reload, 
    SN_TIMER_CALLBACK p_callback, void* timer_arg)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_OK;

}

void sn_platform_timer_delete( SNTIMER_HANDLE_T *htimer)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return ;
}

int sn_platform_timer_start(SNTIMER_HANDLE_T *htimer)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_OK;
}

void sn_platform_timer_stop(SNTIMER_HANDLE_T *htimer)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return ;
}

int sn_platform_timer_changeperiod(SNTIMER_HANDLE_T *htimer,int32_t new_period)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

void sn_platform_gettimeofday(struct sn_timeval* tv)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return;
}


unsigned int sn_platform_time(void)
{
    return hfsys_get_time();
}

int sn_platform_gethostbyname(char *hostname, sn_in_addr *inaddr)
{
    struct hostent *hp;
    uint32_t ip;
    char *addr;
    u_printf("[%s][%d]\n",__FUNCTION__,__LINE__);

    if(hostname == NULL||inaddr == NULL)
    {
        return SN_NOK;
    }
    hp = lwip_gethostbyname((const char*)hostname);
    if (hp == NULL)
    {
        u_printf("can't resolute the host address \n");
        return SN_NOK;
    }
    ip = *(uint32_t *)(hp->h_addr);
    inaddr->s_addr = ip;
    addr = inet_ntoa(*(unsigned int *)hp->h_addr);
    u_printf("Server name [%s]address: [%s]\r\n", hostname, addr);
    return SN_OK;

}

int sn_platform_socket(int domain, int type, int protocol)
{
    int res = socket(domain, type, protocol);
    u_printf("[%s][%d] [%d]\n",__FUNCTION__,__LINE__, res);
    return res;
}

int sn_platform_connect(int s, const sn_sockaddr *name, uint32_t namelen)
{
    int res = connect(s, (const struct sockaddr *)name, namelen);
    u_printf("[%s][%d] [%d]\n",__FUNCTION__,__LINE__, res);
    return res;
}
int sn_platform_send(int s, const void *dataptr, int size, int flags)
{
    int res = send(s, dataptr, size, flags);
    u_printf("[%s][%d] [%d]\n",__FUNCTION__,__LINE__, res);
    return res;
}

int sn_platform_recv(int s, void *mem, int len, int flags)
{
    int res = recv(s, mem, len, flags);
    u_printf("[%s][%d] [%d]\n",__FUNCTION__,__LINE__, res);
    return res;
}

int sn_platform_select(int maxfdp1, sn_fd_set *readset, sn_fd_set *writeset, sn_fd_set *exceptset, struct sn_timeval *timeout)
{
	int res;
    struct timeval timeout_t;

	timeout_t.tv_sec=timeout->tv_sec;
	timeout_t.tv_usec=timeout->tv_usec;

	res = select(maxfdp1, (fd_set *)readset, (fd_set *)writeset, (fd_set *)exceptset, &timeout_t);
    return res;
}

int sn_platform_sendto(int s, const void *data, uint32_t size, int flags, const sn_sockaddr *to, uint32_t tolen)
{
    u_printf("[%s][%d]\n",__FUNCTION__,__LINE__);
    return sendto(s, data, size, flags,(const struct sockaddr *)to,tolen);
}

int sn_platform_recvfrom(int s, void *mem, uint32_t len, int flags, sn_sockaddr *from, uint32_t *fromlen)
{
    return recvfrom(s, mem, len, flags,(struct sockaddr *)from,(socklen_t *)fromlen);
}

int sn_platform_bind(int s, const sn_sockaddr *my_addr, uint32_t addrlen)
{
    return bind(s, (const struct sockaddr *)my_addr, addrlen);
}

uint32_t sn_platform_htonl(uint32_t hostlong){
    return htonl(hostlong);
}

uint32_t sn_platform_ntohl(uint32_t netlong){
    return ntohl(netlong);
}

uint16_t sn_platform_htons(uint16_t hostshort){
    return htons(hostshort);
}

uint16_t sn_platform_ntohs(uint16_t netshort){
    return ntohs(netshort);
}

int sn_platform_close(int s)
{
    return close(s);
}

int sn_platform_mutex_init(SN_THREAD_MUTEX  *pMutex)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}
int sn_platform_mutex_lock(SN_THREAD_MUTEX  *pMutex)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}
int sn_platform_mutex_unlock(SN_THREAD_MUTEX  *pMutex)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return SN_NOK;
}

void sn_platform_mutex_destroy(SN_THREAD_MUTEX  *pMutex)
{
    /*Not basic function,some special projects use this*/
    u_printf("[%s] Not basic function,some special projects use \r\n",__FUNCTION__);
    return ;
}

int sn_platform_setsockopt(int socket, int level, int option_name,const void *option_value, int option_len){
    return setsockopt(socket, level, option_name, option_value, option_len);
}

int sn_platform_blesend(const void *data, uint32_t size)
{
    /*just for ble config*/
	int i,ret;
	unsigned char send_data[30];
	memcpy(send_data,data,size);
	
	u_printf("[%s] hf_fast_send_ble_data %d\r\n",__FUNCTION__,size);

	for(i=0;i<size;i++)
	{
		u_printf("%02X ", send_data[i]);
	}
	u_printf("\r\n");

	ret = hf_send_ble_data(send_data,size);
	u_printf("hf_send_ble_data %d\r\n",ret);
	msleep(100);
    return SN_OK;
}

