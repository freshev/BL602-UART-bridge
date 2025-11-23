#include <hsf.h>
#include <stdlib.h>
#include <string.h>
#include "joylink_string.h"
#include "joylink_memory.h"
#include "joylink_softap.h"
#include "joylink_extern.h"

int joylink_softap_init_t(void)
{
	memset(g_hf_config_file.ap_ssid, 0, sizeof(g_hf_config_file.ap_ssid));
	strcpy((char *)g_hf_config_file.ap_ssid, DEV_SOFTAP_SSID);
	g_hf_config_file.ap_pmk_av= 0;
	g_hf_config_file.wap_mode=CONFIG_WAMOD_11BGN;
	g_hf_config_file.wap_channel=0;
	g_hf_config_file.ap_enable_hide=0;

	g_hf_config_file.waauth = WAUTH_OPEN;
	g_hf_config_file.waencry = WENCRY_NONE;
	hfconfig_file_save();
	
	return TRUE;
}

/**
 * @brief:set wifi mode to AP mode.
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_enter_ap_mode(void)
{
    // open wifi whit AP mode
	//char rsp[64]={0};
	uint8_t softap_flag=0x22;
	hffile_userbin_write(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
	g_hf_config_file.wmode_mode=0;//ap
	joylink_softap_init_t();
	msleep(500);
	hfsys_reset();
	
    return 0;
}


/**
 * @brief:System is expected to get product information that user regiested in Cloud platform.
 *
 * @param[out]: UUID , max length: 8
 * @param[out]: BRAND, max length: 8 
 * @param[out]: CID,   max length: 8
 * @param[out]: dev_soft_ssid max length: 32
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_get_product_info(char *uuid, char *brand, char *cid, char *dev_soft_ssid)
{
    char *_uuid = "F4AA74";
    jl_platform_strcpy(uuid, _uuid);
    
    char* _dev_soft_ssid="JDChaZuo4807";
    jl_platform_strcpy(dev_soft_ssid, _dev_soft_ssid);
    
    char *_cid = "102010";
    jl_platform_strcpy(cid, _cid);

    char *_brand="448";
    jl_platform_strcpy(brand, _brand);

    return 0;
}

/**
 * @brief:System is expected to connect wifi router with the in parameters.
 *
 * @param[in]: ssid of wifi router
 * @param[in]: passwd  of wifi router
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_connect_wifi_router(char *ssid, char *passwd)
{
	memset((char *)g_hf_config_file.sta_ssid, 0, 33);
	memcpy((char *)g_hf_config_file.sta_ssid, (const char *)ssid, strlen(ssid));
	g_hf_config_file.connect_flag = 0;
	
	if(passwd != NULL)
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
	strcpy((char *)(g_hf_config_file.sta_key),passwd);
	g_hf_config_file.pmk_av= 0;  


	g_hf_config_file.wmode_mode = CONFIG_WMODE_STA;
	
	hfconfig_file_save();
	
	msleep(200);
	hfwifi_stop();
	msleep(500);
	hfwifi_start();


    return 0;
}
