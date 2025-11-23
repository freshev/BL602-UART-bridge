/******************************************************************************
  Copyright (C) SUNING

  文 件 名   : snlink_defs.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2017年10月25日
  最近修改   : 
******************************************************************************/

#ifndef _SNLINK_DEFS_H_
#define _SNLINK_DEFS_H_

//#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#define SN_OK                       0             //! No error occurred.
#define SN_NOK                     -1             //! General error.
#define SN_ERROR_1                 -2             //! snlink define error.

#define WIFI_VER	"38"
#define MCU_VER		"0"
#define SN_PID		"0077001400060001"
#define APP_ID		"hf2019"
#define APP_SECRET	"k41yAiH6eurSTvXp"

#define USER_LED 		(HFGPIO_F_USER_DEFINE)
#define USER_LINK 		(HFGPIO_F_USER_DEFINE+1)
#define USER_RELOAD 	(HFGPIO_F_USER_DEFINE+2)

#define POWER_REPORT "{\"SN_POWER\":\"%d\"}"
#define USER_OFFSET (1024)

extern char sn_connect_flag;
extern char close_ble_flag;
extern char bind_flag;
extern char power_flag;
extern char sn_server_send_flag;
extern char upload_cnt;


#ifndef _STDBOOL_H    //mxchip
#ifndef _STDBOOL_H_   //qcom
#ifndef __BASIC_TYPES_H__ //realtek
typedef unsigned char BOOL;
#endif
#endif
#endif

#ifndef _STDINT         //realtek
#ifndef _STDINT_H       //mxchip
#ifndef _STDINT_H_      //qcom
#ifndef _GCC_STDINT_H   //boliu
typedef unsigned int uint32_t;
typedef signed int int32_t;
#endif
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
#endif
typedef unsigned long long int uint64_t;
typedef signed long long int64_t;
#endif
#endif

#ifndef SN_STACKSIZE
#define SN_STACKSIZE        1024
#endif

typedef char asciiStr_t;

#define MAX_PWDLEN              64
#define SNLINK_MAX_SSIDS        32
#define MAX_SSIDLEN             32
#define MAX_BSSIDLEN            6
#define MAX_AP_CFG_DATALEN      200
#define MAX_QR_CFG_DATALEN      280
#define MAX_USERTOKEN_DETALEN   44

/*
 * SnLink解码成功后的结果
 */
typedef struct
{
    char pwd[MAX_PWDLEN+1];         /* wifi密码，以'\0'结尾 */
    char ssid[MAX_SSIDLEN+1];       /* wifi ssid，以'\0'结尾 */
    unsigned char pwd_length;       /* wifi密码长度 */
    unsigned char ssid_length;      /* wifi ssid长度 */
    int security_type;              /* 加密类型 */
    unsigned char reserved;         /* 保留值 */
} snlink_result_t;

#define SN_WIFICFG_NONE         0       //无需配网
#define SN_WIFICFG_WIFISNIFFER  0x01    //wifi广播配网
#define SN_WIFICFG_BLE          0x02    //ble配网
#define SN_WIFICFG_AP           0x04    //ap配网
#define SN_WIFICFG_QRCODE       0x08    //二维码配网


typedef struct
{
    char mac[13];                   /* mac地址,字符串 */
    char wifiModVer[12];            /* wifi模块版本号,字符串*/
    char snPid[20];                 /* pid,字符串 */
    char cusModeType[32];           /* 用户自定义模块类型,字符串 */
    char ID2[30];                   /* 阿里ID2,字符串 */
    char appId[20];
    char accessSecret[20];
    char wifiCfgType;               /*wifi配网方式*/
    char mcuVer[12];                /*电控板固件版本号,字符串*/
    char ext[40];                   /*用户自定义字段*/
} snCloud_initPara_t;

/*
 * @brief  The structure is used to describe the scan result of the AP.
 */
typedef struct snlink_ap_info{
    uint8_t ssid[MAX_SSIDLEN+1];
    uint8_t bssid[MAX_BSSIDLEN+1];/** The network BSSID(eg,mac), represented as a 6-byte array. */
    uint32_t channel;/** The network channel. */
    int security_type;    /*the encryto method*/
    uint16_t strength;
}snlink_ap_info_t;
typedef struct snlink_scanResult{
    int itemNum;
    snlink_ap_info_t pItems[SNLINK_MAX_SSIDS];//snlink_scan_result *pItems;
}snlink_scanResult_t;


/*
 * SnLink设备注册信息
 */
typedef struct
{
    char devID[24];          /* device ID*/
    char regData1[20];       /* 注册分配信息*/
} snlink_devRegInfo_t;

/*
 * snlink 配网状态
 */
typedef enum {
    SNLINK_CFG_LOCKING_CH = 0,  //正在锁定信道
    SNLINK_CFG_GET_LEN,         //获取配网数据
    SNLINK_CFG_GET_DATA,        //获取配网数据
    SNLINK_CFG_COMPLETE,        //配网成功
    SNLINK_CFG_FAILED           //配网失败
} sn_wifi_cfg_status_t;

typedef enum{
    DL_NONE,
    DL_ERR,
    DL_INFO,
    DL_WARN,
    DL_DEBUG
}sn_DebugLevel;

typedef enum{
    SERVER_ENV_PRD = 0,
    SERVER_ENV_PRE,
    SERVER_ENV_SIT
}sn_ServerEnv_t;

typedef enum {
    SN_WIFI_SECURITY_OPEN = 0,
    SN_WIFI_SECURITY_WPA_TKIP,
    SN_WIFI_SECURITY_WPA_AES,
    SN_WIFI_SECURITY_WPA2_TKIP,
    SN_WIFI_SECURITY_WPA2_AES,    
    SN_WIFI_SECURITY_WPA_WPA2_MIX,
    SN_WIFI_SECURITY_UNKNOW
} sn_wifi_security_t;

typedef enum {
    SNLINK_AP_CHECK = 0,       //继续监听
    SNLINK_AP_COMPLETE,        //成功
    SNLINK_AP_FAILED           //失败，继续监听
} sn_ap_cfg_status_t;

typedef enum {
    /*emq push event*/
    SN_EVENT_REPORT_HEX = 1,
    SN_EVENT_REPORT_JASON,
    SN_EVENT_REPORT_MAP,
    SN_EVENT_REPORT_CUSTOM,
    SN_EVENT_REPORT_EVENT
} e_DeviceDataType_t;


typedef enum {
    SNLINK_BLE_INVALID = 0,     //无效数据
    SNLINK_BLE_CONTINUE,        //数据未全部接收完毕
    SNLINK_BLE_CHECK,           //鉴权成功
    SNLINK_BLE_CFGWIFI,         //WiFi信息,接收完毕,需调用snlinkCFG_getResult接口获取SSID和PWD
    SNLINK_BLE_COMPLETE,        //配网流程全部结束
    SNLINK_BLE_FAILED,          //数据错误
    SNLINK_BLE_FAILED_BOUND = 2104  //绑定失败,设备已被其它用户绑定
} sn_ble_rev_status_t;

    
/*通过ble通道，将wifi连接状态上报给手机*/
typedef enum {
    SNBLE_WIFI_CONNECT_SUC = 0,                 //连接路由器成功
    SNBLE_WIFI_CANNOT_FIND_ROUTER,              //连接路由器失败---找不到目标路由器
    SNBLE_WIFI_PWD_WRONG,                       //连接路由器失败---密码错误
    SNBLE_WIFI_CONNECT_FAILED_OHTER = 101       //连接路由器失败---其他原因
} e_snBle_wifiStatus_t;

typedef enum {
    SNLINK_QR_COMPLETE = 0,         //成功
    SNLINK_QR_FAILED                //失败
} sn_qr_cfg_status_t;


/*======================================================*/
/* Make FD_SETSIZE match NUM_SOCKETS in socket.c */
#define SN_MAX_NUM_NETCONN                 1024     //最大的支持socket创建数
#define SN_FD_SETSIZE    SN_MAX_NUM_NETCONN

typedef struct{
    unsigned char fd_bits [(SN_FD_SETSIZE+7)/8];
}sn_fd_set;

struct sn_timeval{
  long    tv_sec;         /* seconds */
  long    tv_usec;        /* and microseconds */
};

typedef struct{
    uint32_t s_addr;
}sn_in_addr;

#define SIN_ZERO_LEN 8
struct sn_sockaddr_in{
  uint8_t         sin_len;
  uint8_t         sin_family;
  uint16_t        sin_port;
  sn_in_addr      sin_addr;
  char            sin_zero[SIN_ZERO_LEN];
};


typedef struct{
    uint8_t        sa_len;
    uint8_t        sa_family;
    char           sa_data[14];
}sn_sockaddr;

typedef enum {
    SN_DEV_WIFI_MOD = 0,    
    SN_DEV_MCU_BOARD,
} sn_device_type_t;

typedef struct
{
    char *p_md5;
    char *p_updataUrl;
    char *p_ver;
    int updataMode;
    sn_device_type_t deviceType;
} snlink_ota_t;

/*======================================================*/
typedef void (*thread_Entry)(void *parm);
//typedef void (*sn_timer_fun)(void *timer_arg);
typedef void* SN_THREAD_MUTEX;
typedef void* SN_QUEUE_HANDLE;
typedef void * SNTIMER_HANDLE_T;

typedef void *(*SN_MALLOC)(uint32_t size);
typedef void (*SN_FREE)(void *ptr);
typedef void *(*SN_MEMSET)(void* ptr, int value, unsigned int num);
typedef void *(*SN_MEMCPY)(void* dst, const void* src, unsigned int num);
typedef int (*SN_MEMCMP)(const void* ptr1, const void* ptr2, unsigned int num);

typedef int (*SN_PRINTF)(const char *format, ...);
typedef void (*SN_MSLEEP)(uint32_t ms);
typedef void (*SN_REBOOT)(void);

typedef int (*SN_INIT_MUTEX)(SN_THREAD_MUTEX  *pMutex);
typedef int (*SN_LOCK_MUTEX)(SN_THREAD_MUTEX  *pMutex);
typedef int (*SN_UNLOCK_MUTEX)(SN_THREAD_MUTEX  *pMutex);
typedef void (*SN_DEINIT_MUTEX)(SN_THREAD_MUTEX *pMutex);

typedef int (*SN_QUEUE_CREATE)(SN_QUEUE_HANDLE *pQueue, uint32_t queue_num, uint32_t item_size);
typedef int (*SN_QUEUE_SEND)(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts);
typedef int (*SN_QUEUE_RECV)(SN_QUEUE_HANDLE *pQueue, void* msgq, uint32_t timeouts);
typedef int (*SN_QUEUE_DESTROY)(SN_QUEUE_HANDLE *pQueue);

typedef int (*SN_CONFIG_READ)(char *pStrName, char *pData, int dataLen);
typedef int (*SN_CONFIG_WRITE)(char *pStrName, char *pData, int dataLen);

typedef void (*SN_TIMER_CALLBACK)( SNTIMER_HANDLE_T *htimer );
typedef int  (*SN_TIMER_CREATE)( SNTIMER_HANDLE_T *htimer, const char *name, uint32_t period, uint8_t auto_reload, SN_TIMER_CALLBACK p_callback, void* timer_arg);
typedef void  (*SN_TIMER_DELETE)(SNTIMER_HANDLE_T *htimer);
typedef int (*SN_TIMER_START)(SNTIMER_HANDLE_T *htimer);
typedef void  (*SN_TIMER_STOP)(SNTIMER_HANDLE_T *htimer);
typedef int (*SN_TIMER_CHANGEPERIOD)(SNTIMER_HANDLE_T *htimer, int32_t new_period);

typedef void (*SN_GETTIMEOFDAY)(struct sn_timeval* tv);
typedef unsigned int (*SN_TIME)(void);

/*======================================================*/
typedef int (*SN_GETHOSTBYNAME)(char *hostname, sn_in_addr *inaddr);
typedef int (*SN_SOCKET)(int domain, int type, int protocol);
typedef int (*SN_CONNECT)(int s, const sn_sockaddr *name, uint32_t namelen);
typedef int (*SN_SEND)(int s, const void *dataptr, int size, int flags);
typedef int (*SN_SELECT)(int maxfdp1, sn_fd_set *readset, sn_fd_set *writeset, sn_fd_set *exceptset, struct sn_timeval *timeout);
typedef int (*SN_RECV)(int s, void *mem, int len, int flags);
typedef int (*SN_CLOSE)(int s);
typedef int (*SN_SENDTO)(int s, const void *data, uint32_t size, int flags, const sn_sockaddr *to, uint32_t tolen);
typedef int (*SN_RECVFROM)(int s, void *mem, uint32_t len, int flags, sn_sockaddr *from, uint32_t *fromlen);
typedef int (*SN_BIND)(int s, const sn_sockaddr *my_addr, uint32_t addrlen);
typedef int (*SN_SETSOCKOPT)(int socket, int level, int option_name,const void *option_value, int option_len);
typedef uint32_t (*SN_HTONL)(uint32_t hostlong);
typedef uint32_t (*SN_NTOHL)(uint32_t hostlong);
typedef uint16_t (*SN_HTONS)(uint16_t hostshort);
typedef uint16_t (*SN_NTOHS)(uint16_t hostshort);
typedef void (*SN_FD_ZERO)(sn_fd_set *fd_set);
typedef void (*SN_FD_SET)(int fd, sn_fd_set *fd_set);
typedef void (*SN_FD_CLR)(int fd, sn_fd_set *fd_set);
typedef int (*SN_FD_ISSET)(int fd, sn_fd_set *fd_set);

typedef int (*SN_BLESEND)(const void *data, uint32_t size);

#endif /* SNLINK_DEFS_H_ */
