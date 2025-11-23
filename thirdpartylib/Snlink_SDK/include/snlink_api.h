/******************************************************************************
  Copyright (C) SUNING

  文 件 名   : snlink_api.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   :
  最近修改   : 
******************************************************************************/

#ifndef _SNLINK_API_H_
#define _SNLINK_API_H_

#include <stdint.h>
#include <stdbool.h>
#include "snlink_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
* 函 数 名: snlinkCloud_init()
* 功能描述: cloud服务对接，变量初始化
* 输入参数：
* 输出参数：无
* 返回值：成功返回SN_OK,失败返回SN_NOK
* 其它说明：无
***********************************************************************/
int snlinkCloud_init(snCloud_initPara_t initPara);


/***********************************************************************
* 函 数 名: snlink_emqpushThread()
* 功能描述: 云端和推送线程函数
* 输入参数：arg
* 输出参数：无
* 返 回 值：
* 其它说明：
***********************************************************************/
void snlink_emqpushThread(void* arg);

/***********************************************************************
* 函 数 名: snlink_localPushThread()
* 功能描述: 局域网线程函数
* 输入参数：arg
* 输出参数：无
* 返 回 值：
* 其它说明：
***********************************************************************/
void snlink_localPushThread(void *arg);

/***********************************************************************
* 函 数 名: snlinkCloud_reportStatus()
* 功能描述: 上报云端设备状态
* 输入参数：hexData 实际的状态帧(内容为HEX数组)
            dataLen  实际状态帧的长度
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_reportStatus(uint8_t *hexData, int dataLen);

/***********************************************************************
* 函 数 名: snlinkCloud_reportStatusJson()
* 功能描述: json串上报上报云端设备状态（内容为字符串）
* 输入参数：pJson是一个json串
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_reportStatusJson(char *pJson);

/***********************************************************************
* 函 数 名: snlinkCloud_reportMap()
* 功能描述: 上报点阵地图数据
* 输入参数：packetData 地图数据内容
            packetLen 地图数据长度
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_reportMap(uint8_t *packetData, int packetLen);

/***********************************************************************
* 函 数 名: snlinkCloud_reportEventJson()
* 功能描述: json串上报上报云端设备事件（内容为字符串）
* 输入参数：pJson是一个json串
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_reportEventJson(char *pJson);

/***********************************************************************
* 函 数 名: snlinkM2P_reportStatus()
* 功能描述: 上报手机设备状态
* 输入参数：data 实际的状态帧
            dataLen  实际状态帧的长度
            datatype:   SN_EVENT_REPORT_HEX = 1,
    					SN_EVENT_REPORT_JASON,
    					SN_EVENT_REPORT_MAP,
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkM2P_reportStatus(uint8_t *data, int dataLen, e_DeviceDataType_t datatype);

/***********************************************************************
* 函 数 名: snlinkCloud_reportDataCustom()
* 功能描述: 上报用户数据到云端
* 输入参数：pData是一个字符串
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_reportDataCustom(uint8_t *pData,int packetLen);


/***********************************************************************
* 函 数 名: snlinCloud_reportOTAStatus()
* 功能描述: json串上报wifi模块OTA进度
* 输入参数：pJson是一个json串
*			开始ota升级 {"SN_ OTASTART":"1"}
*			下载进度		{"SN_OTADL":"10"}   进度为百分比
*			写flash进度 {"SN_OTAW":"10"}		进度为百分比
*			OTA升级结果 {"SN_OTARET":"0"}       0:成功；1:下载失败；2:升级失败
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinCloud_reportOTAStatus(char *pJson);

/***********************************************************************
* 函 数 名: snlinkCloud_deviceUnbind()
* 功能描述: 调用此接口来与服务器解除绑定
* 输入参数：
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCloud_deviceUnbind(void);


/***********************************************************************
* 函 数 名: snlinkCloud_getUTCtime_sync()
* 功能描述: 获取UTC时间
* 输入参数：无
* 输出参数：无
* 返 回 值：NULL/UTC时间(Jason字符串)
* 其它说明：获取失败返回NULL；获取成功返回UTC时间(Jason字符串)
***********************************************************************/
char* snlinkCloud_getUTCtime_sync(void);

/***********************************************************************
* 函 数 名: snlink_getSNSDKVersion()
* 功能描述: 获取snlink版本信息
* 输入参数：无
* 输出参数：无
* 返 回 值：版本号字符串,示例1.2.3，2为连云库版本，3为配网库版本
* 其它说明：
***********************************************************************/
const char* snlink_getSNSDKVersion(void);

/***********************************************************************
* 函 数 名: snlinkCFG_reportApList()
* 功能描述: 将周围的 AP 信息发给snlink SDK
* 输入参数：p_list: ap信息列表地址,请在配网结束后再释放此内存空间,
                    snlink_lib.a中直接使用此内存地址
            apNum : ap数量
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：p_list指向的内存地址，请在配网结束后再释放，snlink_lib.a中
            会直接使用此段内存
***********************************************************************/
int snlinkCFG_reportApList(snlink_ap_info_t* p_list, int apNum);

/***********************************************************************
* 函 数 名: snlinkCFG_recvPacket()
* 功能描述: 解析处理wifi packet，获取需要的数据
* 输入参数：frame:标准的wifi帧; length:帧长度，
            chn:信道号(预留功能，可以传正确的信道号，也可以直接传 0)
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCFG_recvPacket(const void* frame, unsigned short length, int chn);

/***********************************************************************
* 函 数 名: snlinkCFG_getApListByBeacon()
* 功能描述: wifi原厂SDK不提供scan aplist API接口时，可使用此函数获取aplist
* 输入参数：frame:标准的802.11 wifi头, len:帧长度
            p_list:存储ap list的空间
            pApNum:存储已扫描到的Ap 数量
            maxApNum：最大Ap数量
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCFG_getApListByBeacon(const void* frame, unsigned short len, 
                                    snlink_ap_info_t* p_list, int *pApNum,int maxApNum);



/***********************************************************************
* 函 数 名: snlinkCFG_getResult()
* 功能描述: 获取 wifi配网信息
* 输入参数：无
* 输出参数：wifi配网信息
* 返 回 值：SN_OK/SN_NOK
* 其它说明：
***********************************************************************/
int snlinkCFG_getResult(snlink_result_t* result);

/***********************************************************************
* 函 数 名: snlinkCFG_getCfgStatus()
* 功能描述: 获取当前配网的状态
* 输入参数：无
* 输出参数：无
* 返 回 值：当前配网状态，枚举sn_wifi_cfg_status_t
* 其它说明：
***********************************************************************/
sn_wifi_cfg_status_t snlinkCFG_getCfgStatus(void);

/***********************************************************************
* 函 数 名: snlink_reportNetStatus()
* 功能描述: 通知snlink SDK,当前与路由器的连接状态
* 输入参数：0 未连接AP ；1 已连接AP
* 输出参数：无
* 返 回 值：
* 其它说明：连接路由器成功以及断开路由器之后需要调用此函数
***********************************************************************/
void snlink_reportNetStatus(int val);


void snlinkCFG_snifferInit(void);

/***********************************************************************
* 函 数 名: snlinkAP_DataInteraction()
* 功能描述: AP配网时处理手机APP与模块之间数据交互，最终获得SSID和PWD
* 输入参数：inbuf:接收到手机APP的数据
            inlen:接收到手机APP的数据长度
            outbuf:需要发送给手机APP的数据，buf空间至少128 bytes
            outlen:需要发送给手机APP的实际数据长度
* 输出参数：无
* 返 回 值：typedef enum {
            SNLINK_AP_CHECK = 0, //进行中，需要发送outbuf给手机APP
            SNLINK_AP_COMPLETE,  //成功，需要发送outbuf给手机APP，然后调用
                                    snlinkCFG_getResult接口获取SSID和PWD
            SNLINK_AP_FAILED     //失败，需要发送outbuf给手机APP
            } sn_ap_cfg_status_t;
* 其它说明：返回SNLINK_AP_COMPLETE后，调用snlinkCFG_getResult接口获取SSID和PWD
***********************************************************************/
sn_ap_cfg_status_t snlinkAP_DataInteraction (char *inbuf,int inlen,char outbuf[128],int *outlen);

/***********************************************************************
* 函 数 名: snlinkQR_DataDecode()
* 功能描述: 使用扫描二维码配网时解析二维码数据，最终获得SSID，PWD和TOKEN
* 输入参数：inbuf:扫描到的二维码数据
            inlen:扫描到的二维码数据长度
* 输出参数：无
* 返 回 值：typedef enum {
    			SNLINK_QR_COMPLETE = 0,        //成功
    			SNLINK_QR_FAILED           	   //失败
			} sn_qr_cfg_status_t;
            } sn_ap_cfg_status_t;
* 其它说明：返回SNLINK_QR_COMPLETE后，调用snlinkCFG_getResult接口获取SSID和PWD
***********************************************************************/
sn_qr_cfg_status_t snlinkQR_DataDecode (char *inbuf,int inlen);


/***********************************************************************
* 函 数 名: snlink_getDeviceID()
* 功能描述: 获取device ID
* 输入参数：无
* 输出参数：无
* 返 回 值：失败：NULL
            成功：deviceID 字符串地址
* 其它说明：
***********************************************************************/
char* snlink_getDeviceID(void);


/***********************************************************************
* 函 数 名: snlink_getOssDomainAddr()
* 功能描述: 获取Oss域名地址
* 输入参数：无
* 输出参数：无
* 返 回 值：失败：NULL
            成功：Oss域名地址（字符串）
* 其它说明：
***********************************************************************/
char* snlink_getOssDomainAddr(void);


/***********************************************************************
* 函 数 名: snlinkBLE_probe_status()
* 功能描述: 模块连接AP的结果回复
* 输入参数：status,连接AP的结果;
            reasonCode:当wifi连接失败时，按wifi协议的定义reasonCode填写
* 输出参数：无
* 返 回 值：SN_OK/SN_NOK
* 其它说明：调用此函数需要保证BLE已连接
***********************************************************************/
int snlinkBLE_probe_status(e_snBle_wifiStatus_t status,unsigned char reasonCode);


/***********************************************************************
* 函 数 名: snlinkBLE_DataInteraction()
* 功能描述: BLE配网时处理手机APP与模块之间数据交互，最终获得SSID和PWD
* 输入参数：inbuf:接收到手机APP的数据
            inlen:接收到手机APP的数据长度
* 输出参数：无
* 返 回 值：typedef enum {
            SNLINK_BLE_INVALID = 0,     //无效数据
            SNLINK_BLE_CONTINUE,        //数据未全部接收完毕
            SNLINK_BLE_CHECK,           //鉴权成功
            SNLINK_BLE_CFGWIFI,         //WiFi信息,接收完毕,需调用snlinkCFG_getResult接口获取SSID和PWD
            SNLINK_BLE_COMPLETE,        //配网流程全部结束
            SNLINK_BLE_FAILED           //数据错误
        } sn_ble_rev_status_t;
* 其它说明：调用此函数以获得需要连接的路由器的SSID和PWD，之前需
            调用snlinkCloud_init函数
***********************************************************************/
sn_ble_rev_status_t snlinkBLE_DataInteraction(unsigned char *inbuf,int inlen);

/***********************************************************************
* 功能描述: 处理getcustomconfig接口返回数据
* 输入参数：无
* 输出参数：无
* 返回值：成功SN_OK 失败SN_NOK
* 其它说明：无
***********************************************************************/
int snlinkCloud_getCustomConfig(void);


#ifdef __cplusplus
}
#endif

#endif  /*_SNLINK_API_H_*/
