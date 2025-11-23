/******************************************************************************
  Copyright (C) SUNING

  文 件 名   : snlink_notify.c
  版 本 号   : 
  作    者   : 
  生成日期   : 
  最近修改   : 
******************************************************************************/
//#include "stdio.h"
//#include <lwip_netconf.h>
#include <hsf.h>
#include <stdlib.h>
#include <time.h>
#include "snlink_notify.h"
#include "httpclient.h"

#define OTA_STATUS_START 		"{\"SN_OTASTART\":\"1\"}"
#define OTA_STATUS_DL 			"{\"SN_OTADL\":\"%d\"}"
#define OTA_STATUS_W 			"{\"SN_OTAW\":\"%d\"}"
#define OTA_STATUS_RET_0 		"{\"SN_OTARET\":\"0\"}"
#define OTA_STATUS_RET_1 		"{\"SN_OTARET\":\"1\"}"
#define OTA_STATUS_RET_2 		"{\"SN_OTARET\":\"2\"}"

char g_ota_url[200]={0};
extern char state_report[7];
extern char ble_ack[6];
extern char wifi_open[7];
extern char wifi_close[7];
extern char state_report[7];

void snlinkNotify_snCmd(char *data, uint32_t len)
{
    u_printf("[%s] get snCmd:[%s] \r\n", __FUNCTION__, data);
	char rsp[64]={0};
	char write_d=0;
    if(0 == strcmp(data, "unbind"))
	{
        u_printf("device unbind \r\n");
		hf_sn_blelink_start();
    }
	else
	{
        u_printf("[%s] unknown cmd[%s] \r\n", __FUNCTION__, data);
    }
    return;
}

void snlinkNotify_MsgArrive(uint8_t *data, uint32_t bytes)
{
	char *json=NULL;
	
    u_printf("[%s][%d] bytes:%d\n", __FUNCTION__, __LINE__, bytes);
    u_printf("%s\n",data);
	
	json=strstr((char *)data,"POWER");	
	if(json != NULL)
		json+=8;
	
	if(json[0] == 0x31)
	{	
		power_flag = 1;
		hfgpio_fset_out_low(USER_LED);
		hfuart_send(HFUART0,wifi_open,7,0);
	}
	else
	{
		power_flag = 0;
		hfgpio_fset_out_high(USER_LED);
		hfuart_send(HFUART0,wifi_close,7,0);
	}
	
}

void snlinkNotify_NetStatus(sn_SdkNetStatus_t status)
{
    switch(status)
    {
        case DISCONNECTED:
            u_printf("[%s][%d] Disconnected to server.\n", __FUNCTION__, __LINE__);
			sn_connect_flag = 0;
            break;
        case CONNECTING:
            u_printf("[%s][%d] Connecting to server.\n", __FUNCTION__, __LINE__);
            break;
        case CONNECTED_PUSHS:
            u_printf("[%s][%d] Connected to server.\n", __FUNCTION__, __LINE__);
			state_report[4]=3;
			hfuart_send(HFUART0,state_report,7,0);
			sn_connect_flag = 1;
			bind_flag = 1;
			hfgpio_fset_out_low(USER_LINK);
            break;
        case NET_STATUS_NUM:
            u_printf("[%s][%d] NET_STATUS_NUM.\n", __FUNCTION__, __LINE__);
            break;
        default:
            u_printf("[%s][%d] status:%d\n", __FUNCTION__, __LINE__, status);
            break;
    }
}

static int sn_update_thread(void *arg)
{
	msleep(1000);
	snlinCloud_reportOTAStatus(OTA_STATUS_START);
	msleep(100);
	
	httpc_req_t  http_req;
	char *content_data=NULL;
	char *temp_buf=NULL;
	parsed_url_t url={0};
	http_session_t hhttp=0;
	int total_size,read_size=0;

	bzero(&http_req,sizeof(http_req));
	http_req.type = 1;//GET
	http_req.version=HTTP_VER_1_1;
	
	if((temp_buf = (char*)hfmem_malloc(256))==NULL)
		goto exit;
	int temp_buf_len=sizeof(temp_buf);
	memset(temp_buf,0,temp_buf_len);
	if(hfhttp_parse_URL(g_ota_url,temp_buf , 256, &url)!=HF_SUCCESS)
		goto exit;

	if(hfhttp_open_session(&hhttp,g_ota_url,0,NULL,3)!=HF_SUCCESS)
		goto exit;
    hfthread_disable_softwatchdog(NULL);
	hfupdate_start(HFUPDATE_SW);
	http_req.resource = url.resource;
	hfhttp_prepare_req(hhttp,&http_req,HDR_ADD_CONN_CLOSE);
		
	if(hfhttp_send_request(hhttp,&http_req)!=HF_SUCCESS)
		goto exit;
	
	content_data = (char*)hfmem_malloc(1024);
	if(content_data==NULL)
		goto exit;
	
	total_size=0;
	bzero(content_data,1024);
	while((read_size=hfhttp_read_content(hhttp,content_data,1024))>0)
	{
		hfupdate_write_file(HFUPDATE_SW, total_size,(uint8_t *)content_data, read_size);
		total_size+=read_size;
		if(upload_cnt)
		{
			//snlinCloud_reportOTAStatus(OTA_STATUS_DL, 1+total_size*100/file_size);
			upload_cnt = 0;
		}	
		msleep(10);
	}

	if(hfupdate_complete(HFUPDATE_SW,total_size)!=HF_SUCCESS)
	{
		u_printf("UPDAE DEBUG: do_update_version fail!\r");
	}
	else
	{
		u_printf("UPDAE DEBUG: do_update_version success, reset module!\r");
		
		snlinCloud_reportOTAStatus(OTA_STATUS_RET_0);
						
		msleep(2000);
		hfsys_reset();
	}
	
exit:
	snlinCloud_reportOTAStatus(OTA_STATUS_RET_2);
	hfsys_reset();
	
	if(temp_buf!=NULL)	
		hfmem_free(temp_buf);
	if(content_data!=NULL)
		hfmem_free(content_data);
	if(hhttp!=0)
		hfhttp_close_session(&hhttp);	

    hfthread_enable_softwatchdog(NULL,30);
	hfthread_destroy(NULL);
	return 0;
}

void snlinkNotify_OtaInfo(snlink_ota_t s_OtaInfo)
{
    u_printf("[%s] url:%s,md5:%s,ver:%s,deviceType=%d,updataMode=%d\n", __FUNCTION__, 
           s_OtaInfo.p_updataUrl,s_OtaInfo.p_md5,s_OtaInfo.p_ver,s_OtaInfo.deviceType,s_OtaInfo.updataMode);

	memcpy(g_ota_url,s_OtaInfo.p_updataUrl,sizeof(g_ota_url));

	if(HF_SUCCESS != hfthread_create(sn_update_thread,(char const *)"sn_update_thread",1024*4,NULL,HFTHREAD_PRIORITIES_LOW,NULL,NULL))
		u_printf("sn_update_thread create failed!\r\n");
}

int snlinkNotify_SetLockChannel(int channel)
{
    u_printf("[%s][%d] [%d]\n", __FUNCTION__, __LINE__, channel);
    return -1;
}

int snlinkNotify_deleteTask(SN_TASK_t sntask)
{
    u_printf("[%s][%d] sntask=%d\r\n", __FUNCTION__, __LINE__, sntask);
    return SN_OK;
}

int snlinkQuery_DeviceStatus(void){
    u_printf("[%s][%d]\n", __FUNCTION__, __LINE__);
    return SN_NOK;
}

int snlinkNotify_getAuthCode(char *authcode)
{
	//user get authcode to parameter ''char *authcode'
	//success return SN_ON;failed return SN_NOK
	return SN_NOK;
}

void snlinkNotify_Extra(char *extra)
{
	u_printf("[%s][%d] extra = %s\r\n", __FUNCTION__, __LINE__, extra);
}

void snlinkNotify_ID2Random(char *ID2Random)
{
	u_printf("[%s][%d] ID2Random = %s\r\n", __FUNCTION__, __LINE__, ID2Random);
}



