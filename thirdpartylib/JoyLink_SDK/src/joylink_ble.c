#include "joylink_ble.h"
#include "joylink_log.h"

#include <sys/time.h>
#include <fcntl.h>
#include "hsf.h"

#include "joylink_softap.h"
#include "joylink_extern.h"
#include "joylink_ble_sdk.h"



int32_t HSF_IAPI hf_send_ble_ind_data(uint8_t *send_data, uint16_t len);

/*************************************************
Function: jl_ble_send_data
Description: SDK适配接口，GATTS Characteristic发送数据
Calls: GATTS Characteristic发送数据接口
Called By: @jl_send_frame：SDK内部函数
Input: @data：发送的数据
       @data_len：发送的数据长度
Output: None
Return: 0：成功
       -1：失败
Others:
*************************************************/
int32_t jl_ble_send_data(uint8_t* data, uint32_t data_len)
{
    int ret = 0,i=0;
	u_printf("jl_adapter_send_data \r\n");
	for(i=0;i<data_len;i++)
		u_printf("%02X ",data[i]);
	u_printf("\r\n");
	
    ret = hf_send_ble_ind_data(data, data_len);
	u_printf("\r\njl_adapter_send_data ret %d\r\n",ret);
	
	return ret;
}

/*************************************************
Function: jl_ble_set_config_data
Description: SDK适配接口，获取配网与绑定参数
Calls: 传递配网信息接口
Called By: @jl_process_user_data：SDK内部函数
Input: @data->ssid：配网数据，WiFi SSID
       @data->password：配网数据，WiFi密码
Output: None
Return: 0：成功
       -1：失败
*************************************************/
extern char get_wifi_info;
int32_t jl_ble_set_config_data(uint8_t *ssid, uint8_t *password)
{
	memset((char *)g_hf_config_file.sta_ssid, 0, 33);
	memcpy((char *)g_hf_config_file.sta_ssid, (const char *)ssid, strlen((char *)ssid));
	g_hf_config_file.connect_flag = 0;
	
	if(password != NULL)
	{
		g_hf_config_file.wsauth=WAUTH_WPA2PSK;
		g_hf_config_file.wsencry=WENCRY_AES;
	}
	else
	{
		g_hf_config_file.wsauth = WAUTH_OPEN;
		g_hf_config_file.wsencry = WENCRY_NONE;
	}
	bzero(g_hf_config_file.sta_key,sizeof(g_hf_config_file.sta_key));
	strcpy((char *)(g_hf_config_file.sta_key),(char *)password);
	g_hf_config_file.pmk_av= 0;  


	g_hf_config_file.wmode_mode = CONFIG_WMODE_STA;

	get_wifi_info = 1;
	
	hfconfig_file_save();
	
	if(has_softap_flag>0){
		u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_START!\n");
		jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_START,NULL,0);
	}

	msleep(200);
	hfwifi_stop();
	msleep(500);
	hfwifi_start();
	
//    joylink_dev_active_start(data->url, data->token);
    return 0;
}

/*************************************************
Function: jl_ble_set_system_time
Description: SDK适配接口，设置系统时间
Calls: 设置系统时间接口
Called By: SDK内部函数
Input: @time->second：秒
       @time->usecond：微妙
Output: None
Return: 0：成功
       -1：失败
Others: None
*************************************************/
int32_t jl_ble_set_system_time(jl_timestamp_t *time)
{
#if 0
    struct timeval now = { .tv_sec = time->second , .tv_usec = time->usecond};
    settimeofday(&now, NULL);

    struct tm *lt;
    lt = localtime(&lt);
    printf("%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
 #endif
    return 0;
}
