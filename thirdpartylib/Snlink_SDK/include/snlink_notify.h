/******************************************************************************
  Copyright (C) SUNING

  文 件 名   : snlink_notify.h
  版 本 号   : 初稿
  作     者:
  生成日期   : 2017年10月25日
  最近修改   :
******************************************************************************/
#ifndef _SNLINK_NOTIFY_H_
#define _SNLINK_NOTIFY_H_


//#include <stdint.h>
#include "snlink_defs.h"
#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************
* 函 数 名: snlinkNotify_SetLockChannel()
* 功能描述: 切换到锁定信道
* 输入参数：channel
* 输出参数：无
* 返 回 值：SN_OK/ SN_NOK
* 其它说明：snlink_lib.a中会调用此函数锁定信道
***********************************************************************/
int snlinkNotify_SetLockChannel(int channel);


/***********************************************************************
* 函 数 名: snlinkNotify_SetLockChannel_bssid()
* 功能描述: 切换到锁定信道(部分芯片平台锁定信道时需要传bssid)
* 输入参数：channel bssid
* 输出参数：无
* 返 回 值：SN_OK/ SN_NOK
* 其它说明：snlink_lib.a中会调用此函数锁定信道
***********************************************************************/
int snlinkNotify_SetLockChannel_bssid(int channel, char *bssid);



/*
 * snlink SDK 连接服务器状态
 */
typedef enum sn_SdkNetStatus
{
    DISCONNECTED = 0,   //与服务器断开
    CONNECTING ,        //正在连接服务器
    CONNECTED_PUSHS,    //连接服务器成功
    NET_STATUS_NUM,     //总数哨兵
}sn_SdkNetStatus_t;

/***********************************************************************
* 函 数 名: snlinkNotify_NetStatus()
* 功能描述: 通知当前网络状态
* 输入参数：status
* 输出参数：无
* 返 回 值：无
* 其它说明：网络状态变化时，snlink_lib.a中会调用此函数通知电控板
***********************************************************************/
void snlinkNotify_NetStatus(sn_SdkNetStatus_t status);


/***********************************************************************
* 函 数 名: snlinkNotify_snCmd()
* 功能描述: 服务器端发送过来的snCmd(产品功能之外的命令)
* 输入参数：data：数据内容（字符串），len：长度
* 输出参数：无
* 返 回 值：无
* 其它说明：收到snCmd时，snlink_lib.a中会调用此函数
***********************************************************************/
void snlinkNotify_snCmd(char *data, uint32_t len);


/***********************************************************************
* 函 数 名: snlinkNotify_MsgArrive()
* 功能描述: 服务器端发送过来的msg
* 输入参数：data：数据内容，bytes：长度
* 输出参数：无
* 返 回 值：无
* 其它说明：收到msg时，snlink_lib.a中会调用此函数通知电控板
***********************************************************************/
void snlinkNotify_MsgArrive(uint8_t *data, uint32_t bytes);

/***********************************************************************
* 函 数 名: snlinkNotify_OtaInfo()
* 功能描述: 通知设备需要进行OTA升级
* 输入参数：
* 输出参数：无
* 返 回 值：无
* 其它说明：snlink_lib.a中会调用此函数
***********************************************************************/
void snlinkNotify_OtaInfo(snlink_ota_t s_OtaInfo);


typedef enum SN_TASK{
    TASK_SELF = 0X0,    //删除线程本身
    TASK_EMQ_PUSH       //删除snlink_emqpushThread 入口对应的线程
}SN_TASK_t;

/***********************************************************************
* 函 数 名: snlinkNotify_deleteTask()
* 功能描述: 删除线程
* 输入参数：苏宁的线程标识
* 输出参数：无
* 返 回 值：
* 其它说明：SDK中会调用该函数删除线程
***********************************************************************/

int snlinkNotify_deleteTask(SN_TASK_t sntask);

/***********************************************************************
* 函 数 名: snlinkQuery_DeviceStatus()
* 功能描述: 查询设备状态
* 输入参数：无
* 输出参数：无
* 返 回 值：SN_OK 或者 SN_NOK
* 其它说明：如果支持设备状态查询，请调用snlinkCloud_reportStatus
*（或者snlinkCloud_reportStatusJson）上报设备状态，并返回SN_OK；
* 否则请返回SN_NOK
***********************************************************************/
int snlinkQuery_DeviceStatus(void);

/***********************************************************************
* 函 数 名: snlinkNotify_getAuthCode(char *authcode)
* 功能描述: 用户从阿里服务器获取authcode
* 输入参数：authcode
* 输出参数：SN_ON/SN_NOK
* 返 回 值：
* 其它说明：
***********************************************************************/
int snlinkNotify_getAuthCode(char *authcode);

/***********************************************************************
* 函 数 名: snlinkNotify_Extra(char *extra)
* 功能描述: 通知用户阿里服务器用于生成authcode的extra
* 输入参数：extra
* 输出参数：无
* 返 回 值：
* 其它说明：
***********************************************************************/
void snlinkNotify_Extra(char *extra);

/***********************************************************************
* 函 数 名: snlinkNotify_ID2Random(char *ID2Random)
* 功能描述: 通知用户ID2Randoma
* 输入参数：ID2Random
* 输出参数：无
* 返 回 值：
* 其它说明：
***********************************************************************/
void snlinkNotify_ID2Random(char *ID2Random);



#ifdef __cplusplus
}
#endif


#endif /* SNLINK_NOTIFY_H_ */


