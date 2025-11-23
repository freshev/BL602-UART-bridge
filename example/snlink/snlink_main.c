 /* app_main.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <hsf.h>
#include <stdlib.h>
#include <string.h>
#include "snlink_defs.h"
#include "snlink_notify.h"
#include "snlink_platform.h"
#include "snlink_api.h"

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE];

#ifdef __LPT270__
int g_module_id = HFM_TYPE_LPT270;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	LPX70_GPIO12,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	LPX70_GPIO14,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO5,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPT170__
int g_module_id = HFM_TYPE_LPT170;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	HFM_NOPIN,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	HFM_NOPIN,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO5,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPT271__
int g_module_id = HFM_TYPE_LPT271;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	LPX70_GPIO12,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	LPX70_GPIO14,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,		//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,		//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO22,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPT272__
int g_module_id = HFM_TYPE_LPT272;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	HFM_NOPIN,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	HFM_NOPIN,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,		//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,		//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO5,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPB170__
int g_module_id = HFM_TYPE_LPB170;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	LPX70_GPIO12,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	LPX70_GPIO14,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO5,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPB175__
int g_module_id = HFM_TYPE_LPB175;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	HFM_NOPIN,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	HFM_NOPIN,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	HFM_NOPIN,		//HFGPIO_F_NLINK
	HFM_NOPIN,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};

#elif defined __LPT570__
int g_module_id = HFM_TYPE_LPT570;

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,		//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,		//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,		//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	LPX70_GPIO16,	//HFGPIO_F_UART0_TX
	HFM_NOPIN,		//HFGPIO_F_UART0_RTS
	LPX70_GPIO7,		//HFGPIO_F_UART0_RX
	HFM_NOPIN,		//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,  		//HFGPIO_F_SPI_MISO
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,	  	//HFGPIO_F_SPI_CS
	HFM_NOPIN,  		//HFGPIO_F_SPI_MOSI
	
	LPX70_GPIO17,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,		//HFGPIO_F_UART1_RTS,
	LPX70_GPIO11,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,		//HFGPIO_F_UART1_CTS,
	
	LPX70_GPIO5,		//HFGPIO_F_NLINK
	LPX70_GPIO4,		//HFGPIO_F_NREADY
	LPX70_GPIO3,		//HFGPIO_F_NRELOAD
	HFM_NOPIN,	    	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	   	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,	    	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	   	//HFGPIO_F_USER_DEFINE
};
#else
#error "invalid project !you must define module type(__LPT270__ or __LPT170__ 
or __LPT271__ or __LPB170__ or __LPB175__ or __LPT570__ )"
#endif

#ifdef _DELETE_SOCKETA_
void hfnet_register_socketa_atcmd(void){}
#endif

#ifdef _DELETE_SOCKETB_
void hfnet_register_socketb_atcmd(void){}
#endif

#ifdef _DELETE_MDNS_
int hfsmtaplk_response(void)
{
	return -1;
}
#endif

#ifdef _DELETE_SMARTAPLINK_
int hfsmtaplk_main_loop(void)
{
	return -1;
}
#endif

#ifdef _DELETE_SMARTLINK_
int hfsmtlk_main_loop(void)
{
	return -1;
}
#endif

#ifdef _DELETE_HTTPD_
int httpd_start(uint32_t uxpriority)
{
	return -1;
}
#endif

#ifdef _DELETE_BLE_
int32_t hf_start_ble(void)
{
	return 0;
}
#endif

#ifdef _DELETE_WPS_
int hfwifi_wps_main(void)
{
	return 0;
}
#endif


#define LOCAL_BLELK_TIMER_ID (3)
#define LOCAL_20MS_TIMER_ID (2)
#define LOCAL_1S_TIMER_ID (1)

hftimer_handle_t local_blelk_timer=NULL;
hftimer_handle_t local_20ms_timer=NULL;
hftimer_handle_t local_1s_timer=NULL;
char button_cnt=0;
char press_reload_button=0;
char enter_softap_flag = 0;
char sn_connect_flag = 0;
char close_ble_flag = 0;
char close_cnt = 0;
char bind_flag = 0;
char power_flag = 0;
char sn_server_send_flag = 0;
char upload_cnt = 0;
char stop_advertise_flag = 0;

char ble_ack[6]={0xa5,0x5a,0x03,0x04,0x5a,0xa5};
char wifi_open[7]={0xa5,0x5a,0x04,0x01,0x00,0x5a,0xa5};
char wifi_close[7]={0xa5,0x5a,0x04,0x01,0x01,0x5a,0xa5};
char state_report[7]={0xa5,0x5a,0x04,0x07,0x00,0x5a,0xa5};

void hfble_scan_callback()
{}

static int hf_atcmd_power_ctl(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		if(power_flag)
		{	
			power_flag = 0;
			hfgpio_fset_out_high(USER_LED);
		}
		else
		{		
			power_flag = 1;
			hfgpio_fset_out_low(USER_LED);
		}		
		sn_server_send_flag = 1;

		return 0;
	}
	return -3;
}

static int hf_atcmd_unbind_ctl(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		enter_softap_flag=1;
		return 0;
	}
	return -3;
}

static int hf_cmd_get_version(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		sprintf(rsp,"=%s(%s %s)","SN_BLE_SDK_1.0",__DATE__,__TIME__);

		return 0;
	}
	return -3;
}

const hfat_cmd_t user_define_at_cmds_table[]=
{
	{"POWER", hf_atcmd_power_ctl, "   AT+POWER: SN POWER ctl.\r\n",NULL},
	{"UNBIND", hf_atcmd_unbind_ctl, "   AT+UNBIND: SN UNBIND ctl.\r\n",NULL},
	{"APPVER", hf_cmd_get_version, "   AT+APPVER: SN APPVER.\r\n",NULL},
	
	{NULL,NULL,NULL,NULL} //the last item must be null
};

char dhcp_ok_flag = 0;

static int sys_event_callback( uint32_t event_id,void * param)
{
	switch(event_id)
	{
		case HFE_WIFI_STA_CONNECTED:
			u_printf("wifi sta connected!!\n");
			break;
		case HFE_WIFI_STA_DISCONNECTED:
			u_printf("wifi sta disconnected!!\n");
			snlink_reportNetStatus(0);
			break;				
		case HFE_BLE_CONNECTED:
			u_printf("ble connected!!\n");
			break;
		case HFE_BLE_DISCONNECTED:
			u_printf("ble disconnected!!\n");
			break;	
		case HFE_CONFIG_RELOAD:
			u_printf("reload!\n");
			break;
		case HFE_DHCP_OK:
			{
				uint8_t *p_ip;
				p_ip = (uint8_t*)param;
				
				u_printf("dhcp ok %s [%d]!\n", p_ip,hfsys_get_time());
				if(strstr((char *)p_ip,"0.0.0.0")==NULL)
				{
					snlink_reportNetStatus(1);
					dhcp_ok_flag=1;
				}
				msleep(100);				
			}
			break;
		case HFE_SMTLK_OK:
			{
				u_printf("smtlk ok!\n");
				char *pwd=(char*)param;
				if(pwd == NULL)
					u_printf("key is null!\n");
				else
				{
					int i;
					for(i=0; i<(int)strlen(pwd); i++)
					{
						if(pwd[i]==0x1b)
							break;
					}
					for(i++; i<(int)strlen(pwd); i++)
						u_printf("user info 0x%02x-[%c]\n", pwd[i], pwd[i]);
				}
				msleep(100);
				return 1;
			}
			break;
	}
	return 0;
}


static int USER_FUNC socketa_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len)
{
	if(event==HFNET_SOCKETA_DATA_READY)
		HF_Debug(DEBUG_LEVEL_LOW,"socketa recv %d bytes %d\n",len,buf_len);
	else if(event==HFNET_SOCKETA_CONNECTED)
		u_printf("socket a connected!\n");
	else if(event==HFNET_SOCKETA_DISCONNECTED)
		u_printf("socket a disconnected!\n");
	
	return len;
}

static int USER_FUNC socketb_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len)
{
	if(event==HFNET_SOCKETB_DATA_READY)
		HF_Debug(DEBUG_LEVEL_LOW,"socketb recv %d bytes %d\n",len,buf_len);
	else if(event==HFNET_SOCKETB_CONNECTED)
		u_printf("socket b connected!\n");
	else if(event==HFNET_SOCKETB_DISCONNECTED)
		u_printf("socket b disconnected!\n");
			
	return len;
}

extern HF_CONFIG_FILE  g_hf_config_file;
void sn_conn2AP()
{
    snlink_result_t re = {0};

	if(SN_OK==snlinkCFG_getResult(&re))
	{
/*		char router_ssid[50]={0};
		char router_key[50]={0};
		char rsp[50]={0};
	
		sprintf(router_ssid,"AT+WSSSID=%s\r\n",re.ssid);
		sprintf(router_key,"AT+WSKEY=WPA2PSK,AES,%s\r\n",re.pwd);
				
		hfat_send_cmd(router_ssid, strlen(router_ssid), rsp, sizeof(rsp));
		msleep(200);
		hfat_send_cmd(router_key, strlen(router_key), rsp, sizeof(rsp));
		msleep(200);
		hfat_send_cmd("AT+WMODE=STA\r\n", strlen("AT+WMODE=STA\r\n"), rsp, sizeof(rsp));
*/

		g_hf_config_file.pmk_av = 0;

		u_printf("need_pmk\r\n");

		g_hf_config_file.wsauth = WAUTH_WPA2PSK;
		g_hf_config_file.wsencry = WENCRY_AES;
		bzero(g_hf_config_file.sta_key,sizeof(g_hf_config_file.sta_key));
		strcpy((char *)(g_hf_config_file.sta_key),re.pwd);

		memcpy(g_hf_config_file.sta_ssid,re.ssid,strlen(re.ssid));
				
		hfconfig_file_save();
/*
		msleep(500);
		hfwifi_stop();
		msleep(500);
		hfwifi_start();
*/
		state_report[4]=1;
		hfuart_send(HFUART0,state_report,7,0);

/*
		memset(&wifi_config, 0, sizeof(wifi_config_t));
		memcpy((uint8_t *)wifi_config.sta.ssid, re.ssid, re.ssid_length );
		memcpy((uint8_t *)wifi_config.sta.password, re.pwd , re.pwd_length );
		ESP_LOGI(TAG, "ssid:%s, pwd:%s\n", wifi_config.sta.ssid, wifi_config.sta.password);
	  if(strlen((char *)wifi_config.sta.ssid)>0)
	  {
		ESP_ERROR_CHECK(esp_wifi_disconnect());
		do_reconnect=1;
		snlink_reportNetStatus(0);
		ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
		ESP_ERROR_CHECK(esp_wifi_connect());
	  }
	  else
	   ESP_LOGI(TAG, "ssid error\n");
*/
	}
	else
		HF_Debug(DEBUG_LEVEL_LOW, "snlinkCFG_getResult fail\n");

}

static uint8_t bt_ntf_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len)
{
	int Index;

	if(event==HFNET_BT_NTF_DATA_READY)
	{
		HF_Debug(DEBUG_LEVEL_LOW,"hf ble ntf recv %d bytes %d\n",len,buf_len);
		for(Index=0;Index<buf_len;Index++)
		{
			u_printf("%02X ", data[Index]);
		}
		u_printf("\r\n");
		
		int _return;
		_return = snlinkBLE_DataInteraction( (unsigned char *)data,  (int)len);
		u_printf("_return %d\r\n",_return);
		if(_return==SNLINK_BLE_CHECK)
		{
			u_printf("/************SNLINK_BLE_CHECK************/\r\n");
		}
		else if(_return==SNLINK_BLE_COMPLETE)
		{
			u_printf("/************SNLINK_BLE_COMPLETE************/\r\n");
			bind_flag = 1;
			hffile_userbin_write(USER_OFFSET, &bind_flag, sizeof(bind_flag));			
			msleep(100);
			hf_close_ble();
			stop_advertise_flag = 1;
		}
		else if(_return==SNLINK_BLE_CFGWIFI)
		{
			u_printf("/************SNLINK_BLE_CFGWIFI************/\r\n");
			sn_conn2AP();
		}
		else if(_return==SNLINK_BLE_INVALID)
		{
			u_printf("/************SNLINK_BLE_INVALID************/\r\n");
		}
		else if(_return==SNLINK_BLE_FAILED)
		{
			u_printf("/************SNLINK_BLE_FAILED************/\r\n");
		}
		else if(_return==SNLINK_BLE_FAILED_BOUND)
		{
			u_printf("/************SNLINK_BLE_FAILED_BOUND************/\r\n");
		}
	}	
	else if(event==HFNET_BT_NTF_DATA_ENABLE)
		u_printf("hf ble ntf connected!\n");
	else if(event==HFNET_BT_NTF_DATA_DISENABLE)
		u_printf("hf ble ntf disconnected!\n");
	return 0;
}

static uint8_t bt_ind_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len)
{

	if(event==HFNET_BT_IND_DATA_READY)
		HF_Debug(DEBUG_LEVEL_LOW,"hf ble ind recv %d bytes %d\n",len,buf_len);
	else if(event==HFNET_BT_IND_DATA_ENABLE)
		u_printf("hf ble ind connected!\n");
	else if(event==HFNET_BT_IND_DATA_DISENABLE)
		u_printf("hf ble ind disconnected!\n");
	return 0;
}

void uart_data_handle(uint8_t *rec_data,int len)
{
	switch(rec_data[2])
	{
		case 0x03:
			if(rec_data[3]==0x02)//peiwang
			{			
				hfuart_send(HFUART0,ble_ack,6,0);
				msleep(200);
				hf_sn_blelink_start();
			}
			break;
		case 0x04:
			if(rec_data[3]==0x02)//kaiji
			{	
				if(rec_data[4]==0x00)
				{
					power_flag = 1;
					hfgpio_fset_out_low(USER_LED);
					sn_server_send_flag = 1;
					//hfuart_send(HFUART0,wifi_open,7,0);
				}
				else//guanji
				{
					power_flag = 0;
					hfgpio_fset_out_high(USER_LED);
					sn_server_send_flag = 1;
					//hfuart_send(HFUART0,wifi_close,7,0);
				}
			}
			break;
		default:
			break;
	}
}

static int USER_FUNC uart_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len)
{
	int i;
	uint8_t rec_data[50]={0};
	
	HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart recv %d bytes data %d\n",event,len,buf_len);
	if(hfsys_get_run_mode() == HFSYS_STATE_RUN_CMD)
	{	
		u_printf("at Mode\r\n");
		return len;
	}
	memcpy(rec_data,data,len);
	
	u_printf("recv ");
	for(i=0;i<len;i++)
	{
		u_printf("%02X ",rec_data[i]);
	}
	u_printf("\r\n");

	uart_data_handle(rec_data,len);

	return 0;
}

void app_fill_ble_adv_data()
{
	// user fill self ble adv data
	static uint8_t raw_adv1[24] = {0x02,0x01,0x06,
	0x14,0xff,0x53,0x4e,
	0x01,
	0x01,0x01,
	0x00,0x77,0x00,0x14,0x00,0x06,0x00,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00};
	static uint8_t raw_adv[20] = {0x13,0x09,'S','U','N','I','N','G','_','D','E','V','I','C','E','_','0','0','0','0'};
	static uint8_t mac[6]={0};
	static uint8_t pid[17]={0};
	int i;
	extern GAPP_DISC_DATA_T Advertisement_Data;

	hfwifi_read_sta_mac_address(mac);
	
	u_printf("\r\n");
	for(i=0;i<6;i++)
	{
		u_printf("%02X ",mac[i]);
	}
	u_printf("\r\n");
	
	raw_adv1[18]	= mac[0];
	raw_adv1[19]	= mac[1];
	raw_adv1[20]	= mac[2];
	raw_adv1[21]	= mac[3];
	raw_adv1[22]	= mac[4];
	raw_adv1[23]	= mac[5];

	raw_adv[16] = (mac[4]>>4);
	raw_adv[17] = (mac[4]&0x0f);
	raw_adv[18] = (mac[5]>>4);
	raw_adv[19] = (mac[5]&0x0f);

	for(i=16;i<20;i++)
	{
		if(raw_adv[i] > 9 )
			raw_adv[i] += 55;
		else
			raw_adv[i] += 0x30;
	}

	sprintf((char *)pid,"%s",SN_PID);

	for(i=0;i<17;i++)
	{
		if(pid[i] > 65 )
			pid[i] -= 55;
		else
			pid[i] -= 0x30;
	}
	
	raw_adv1[10]=(pid[0]<<4)+pid[1];
	raw_adv1[11]=(pid[2]<<4)+pid[3];
	raw_adv1[12]=(pid[4]<<4)+pid[5];
	raw_adv1[13]=(pid[6]<<4)+pid[7];
	raw_adv1[14]=(pid[8]<<4)+pid[9];
	raw_adv1[15]=(pid[10]<<4)+pid[11];
	raw_adv1[16]=(pid[12]<<4)+pid[13];
	raw_adv1[17]=(pid[14]<<4)+pid[15];

	u_printf("\r\n");
	for(i=10;i<18;i++)
	{
		u_printf("%02X ",raw_adv1[i]);
	}
	u_printf("\r\n");

	/*
	memset(Advertisement_Data.advData,0,sizeof(Advertisement_Data.advData));
	memcpy(Advertisement_Data.advData,raw_adv,sizeof(raw_adv));
	Advertisement_Data.advDataLen = sizeof(raw_adv);

	memset(Advertisement_Data.advrspData,0,sizeof(Advertisement_Data.advData));
	memcpy(Advertisement_Data.advrspData,raw_adv1,sizeof(raw_adv1));
	Advertisement_Data.advrspDataLen = sizeof(raw_adv1);
	*/

	memset(Advertisement_Data.advData,0,sizeof(Advertisement_Data.advData));
	memcpy(Advertisement_Data.advData,raw_adv1,sizeof(raw_adv1));
	Advertisement_Data.advDataLen = sizeof(raw_adv1);

	memset(Advertisement_Data.advrspData,0,sizeof(Advertisement_Data.advData));
	memcpy(Advertisement_Data.advrspData,raw_adv,sizeof(raw_adv));
	Advertisement_Data.advrspDataLen = sizeof(raw_adv);

	
}

static void show_reset_reason(void)
{
	uint32_t reset_reason=0;
	reset_reason = hfsys_get_reset_reason();
	
#if 1
	u_printf("reset_reasion:%08x\n",reset_reason);
#else	
	if(reset_reason&HFSYS_RESET_REASON_ERESET)
	{
		u_printf("ERESET\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_IRESET0)
	{
		u_printf("IRESET0\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_IRESET1)
	{
		u_printf("IRESET1\n");
	}
	if(reset_reason==HFSYS_RESET_REASON_NORMAL)
	{
		u_printf("RESET NORMAL\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_WPS)
	{
		u_printf("RESET FOR WPS\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_SMARTLINK_START)
	{
		u_printf("RESET FOR SMARTLINK START\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_SMARTLINK_OK)
	{
		u_printf("RESET FOR SMARTLINK OK\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_WPS_OK)
	{
		u_printf("RESET FOR WPS OK\n");
	}
#endif
	
	return;
}

void app_init(void)
{
	u_printf("app_init\n");
}

void suning_init()
{
	unsigned char mac[6]={0}; //模块的mac
	char wifi_mac[13]={0}; //模块的mac
	char *pVersion = NULL;
	snCloud_initPara_t snCloudInitPara = {0};

	pVersion = (char *)snlink_getSNSDKVersion();
	HF_Debug(DEBUG_LEVEL,"\r\n***sdk Version=%s***\r\n",pVersion);  

	HF_Debug(DEBUG_LEVEL,"snlink_MainThread running!");
		
	if(HF_SUCCESS != hfthread_create(snlink_emqpushThread,(char const *)"snlink_emqpushThread",1024*2,NULL,HFTHREAD_PRIORITIES_LOW,NULL,NULL))
		u_printf("snlink_emqpushThread create failed!\r\n");

	hfwifi_read_sta_mac_address(mac);
	sprintf(wifi_mac,"%02X%02X%02X%02X%02X%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	HF_Debug(DEBUG_LEVEL,"\r\nsn_mac: %s\r\n",wifi_mac);

	strcpy(snCloudInitPara.mac, wifi_mac);
	strcpy(snCloudInitPara.wifiModVer, WIFI_VER);
	strcpy(snCloudInitPara.mcuVer, MCU_VER);
	strcpy(snCloudInitPara.snPid, SN_PID);
	strcpy(snCloudInitPara.appId, APP_ID);
	strcpy(snCloudInitPara.accessSecret, APP_SECRET);

	if(bind_flag==1)
		snCloudInitPara.wifiCfgType = SN_WIFICFG_NONE;
	else
		snCloudInitPara.wifiCfgType = SN_WIFICFG_BLE;

	snlinkCloud_init(snCloudInitPara);
}

void uuid_init()
{
	char rsp[64] = {0};
	char reset_cnt = 0;
	
	hfat_send_cmd("AT+UART\r\n",sizeof("AT+UART\r\n"),rsp,sizeof(rsp));
	if(strstr(rsp,"+ok=115200,8,1,None,NFC") == NULL)
	{
		hfat_send_cmd("AT+UART=115200,8,1,None,NFC\r\n",sizeof("AT+UART=115200,8,1,None,NFC\r\n"),rsp,sizeof(rsp));
		reset_cnt++;
	}
	hfat_send_cmd("AT+BLEADP\r\n",sizeof("AT+BLEADP\r\n"),rsp,sizeof(rsp));
	if(strstr(rsp,"+ok=0128016007") == NULL)
	{
		hfat_send_cmd("AT+BLEADP=0128016007\r\n",sizeof("AT+BLEADP=0128016007\r\n"),rsp,sizeof(rsp));
		reset_cnt++;
	}
	if(reset_cnt)
	 	hfsys_reset();
}

void USER_FUNC timer_callback( hftimer_handle_t htimer )
{	
	if(hftimer_get_timer_id(htimer)==LOCAL_20MS_TIMER_ID)
	{
		if(hfgpio_fpin_is_high(USER_RELOAD)==0)
		{
			if(press_reload_button)
			{
				button_cnt++;
				if(button_cnt==3)
				{
					u_printf("release the reload button!\n");
					button_cnt = 0;
					press_reload_button = 0;
				}
			}
		}
		else
		{
			button_cnt++;
			if(button_cnt==3)
			{		
				press_reload_button++;
				if(press_reload_button == 50)
					enter_softap_flag = 1;
				//u_printf("press the reload button!\n");
				button_cnt = 0;
			}
		}
	}
	if(hftimer_get_timer_id(htimer)==LOCAL_1S_TIMER_ID)
	{
		upload_cnt = 1;
		if(stop_advertise_flag)
		{	
			stop_advertise_flag = 0;
			hf_close_ble();
		}
		if(bind_flag == 0)
		{
			if(hfgpio_fpin_is_high(USER_LINK))
			{
				hfgpio_fset_out_low(USER_LINK);
			}
			else
			{
				hfgpio_fset_out_high(USER_LINK);
			}
		}
	}
	if(hftimer_get_timer_id(htimer)==LOCAL_BLELK_TIMER_ID)
	{
		u_printf("hf_sn_blelink_stop ******************\r\n");
		hf_close_ble();
		stop_advertise_flag = 1;
	}
}

void hf_sn_blelink_start()
{
	u_printf("hf_sn_blelink_start ******************\r\n");
	
	state_report[4]=0;
	hfuart_send(HFUART0,state_report,7,0);
	
	char rsp[64]={0};
	int write_d = 0;
	if(sn_connect_flag)
		snlinkCloud_deviceUnbind();

	hffile_userbin_write(USER_OFFSET,(char *)&write_d, sizeof(write_d));
	msleep(200);
	memset((char *)g_hf_config_file.sta_ssid, 0, sizeof(g_hf_config_file.sta_ssid));
	g_hf_config_file.wmode_mode = CONFIG_WMODE_STA;
	hfconfig_file_save();
//	hfat_send_cmd("AT+WMODE=AP\r\n",sizeof("AT+WMODE=AP\r\n"),rsp,sizeof(rsp));
	msleep(2000);
	hfsys_reset();
}

void sn_thread()
{
	char pJsonTest[100]={0};

	while(1)
	{
		if(enter_softap_flag)
		{	
			enter_softap_flag = 0;
			hf_sn_blelink_start();
		}
		if(sn_server_send_flag)
		{
			if(sn_connect_flag)
			{	
				sn_server_send_flag=0;
				sprintf(pJsonTest,POWER_REPORT,power_flag);
				snlinkCloud_reportStatusJson(pJsonTest);
			}		
		}
		if(dhcp_ok_flag)
		{
			state_report[4]=2;
			hfuart_send(HFUART0,state_report,7,0);
			dhcp_ok_flag = 0;
		}
		msleep(10);
	}

}

int USER_FUNC app_main (void)
{
	uint8_t ble_switch = g_hf_config_file.ble_switch;
	HF_Debug(DEBUG_LEVEL,"app_main sdk version(%s),the app_main start time is %s %s\n",hfsys_get_sdk_version(),__DATE__,__TIME__);
	if(hfgpio_fmap_check(g_module_id)!=0)
	{
		while(1)
		{
			HF_Debug(DEBUG_ERROR,"gpio map file error\n");
			msleep(1000);
		}
	}
	
	hfsys_register_system_event(sys_event_callback);
	show_reset_reason();

	if((local_20ms_timer = hftimer_create("LOCAL_20MS_TIMER_ID",20,TRUE,LOCAL_20MS_TIMER_ID,timer_callback,0))==NULL)
        u_printf("create LOCAL_20MS_TIMER_ID fail\n");
	else
		hftimer_start(local_20ms_timer);

	if((local_1s_timer = hftimer_create("LOCAL_1S_TIMER_ID",1000,TRUE,LOCAL_1S_TIMER_ID,timer_callback,0))==NULL)
        u_printf("create LOCAL_1S_TIMER_ID fail\n");
	else
		hftimer_start(local_1s_timer);


	while(hfsmtlk_is_start())
		msleep(100);
	
	if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start uart fail!\n");
	}

	hffile_userbin_read(USER_OFFSET,&bind_flag,sizeof(bind_flag));
	msleep(100);
	
	if(bind_flag)
	{		
		state_report[4]=1;
		hfuart_send(HFUART0,state_report,7,0);
	}	
	
	suning_init();
	uuid_init();
	
	if(bind_flag==0)
	{
		u_printf("device unbind *************\r\n");
		if(hfnet_start_ble_ntf(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ntf_recv_callback)!=HF_SUCCESS)
		{//udp
			HF_Debug(DEBUG_WARN,"start ble ntf fail\n");
		}

		if(hfnet_start_ble_ind(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ind_recv_callback)!=HF_SUCCESS)
		{//tcp
			HF_Debug(DEBUG_WARN,"start ble ntf fail\n");
		}

		hf_start_ble();
		

		if((local_blelk_timer = hftimer_create("LOCAL_BLELK_TIMER",600000,false,LOCAL_BLELK_TIMER_ID,timer_callback,0))==NULL)
			u_printf("create LOCAL_BLELK_TIMER fail\n");
		else
			hftimer_start(local_blelk_timer);
	}
	else
		u_printf("device already bind *************\r\n");

	if(hfthread_create((PHFTHREAD_START_ROUTINE)sn_thread, "SN_THREAD", 1024*2, NULL, HFTHREAD_PRIORITIES_LOW,NULL,NULL)!= HF_SUCCESS)
	{
		u_printf("SN_THREAD create failed!\r\n");
	}

	return 1;
}



