 /* joylinktest.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <hsf.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include "joylink_softap.h"
#include "joylink_thread.h"
#include "joylink_socket.h"
#include "joylink.h"
#include "joylink_extern.h"
#include "joylink_softap_start.h"
#include "joylink_ble_sdk.h"
#include "joylink_extern_ota.h"

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE];

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
#error "invalid project !you must define module type(__LPT270__ or __LPT170__ or __LPT271__ or __LPB170__ or __LPB175__ or __LPT570__ )"
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

char dhcp_ok_flag=0;
HF_JD_CONFIG g_hf_jdconfig;

hftimer_handle_t local_20ms_timer=NULL;
hftimer_handle_t local_05s_timer=NULL;
hftimer_handle_t local_1s_timer=NULL;

#define LOCAL_20MS_TIMER_ID (2)
#define LOCAL_05S_TIMER_ID (1)
#define LOCAL_1S_TIMER_ID (3)

int press_reload_button=0;
char enter_softap_flag = 0;
char enter_smtble_flag = 0;
char reset_factory_flag = 0;
char button_cnt=0;
uint8_t joylink_server_send_flag=0;
int has_softap_flag=0;
unsigned int jd_sys_time = 0;


void hfble_scan_callback()
{}

void hf_jd_softap_start(void)
{
	uint8_t softap_flag=0x22;
	hffile_userbin_write(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
	g_hf_config_file.wmode_mode=0;//ap
	joylink_softap_init_t();
	u_printf("hf_jd_softap_start***********\r\n");
	msleep(100);
	hfsys_reset();
}

void hf_jd_smartble_start(void)
{
	uint8_t softap_flag=0x11;
	hffile_userbin_write(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
	g_hf_config_file.wmode_mode=0;//ap
	joylink_softap_init_t();
	u_printf("hf_jd_smartble_start***********\r\n");
	msleep(100);
	hfsys_reset();
}


static int hf_atcmd_start_jd_softap(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		extern void cmd_reply(char *reply);
	    cmd_reply("+ok");
		hf_jd_softap_start();
		return 0;
	}
	return -3;
}
static int hf_atcmd_start_jd_smartble(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		extern void cmd_reply(char *reply);
	    cmd_reply("+ok");
		hf_jd_smartble_start();
		return 0;
	}
	return -3;
}


char* read_prikey(void)
{  
   return g_hf_jdconfig.jd_prikey;
}

char* read_mac(void)
{  
   return g_hf_jdconfig.jd_mac;
}

void write_prikey(char* mac,char *prikey)
{
	memset(g_hf_jdconfig.jd_prikey,0,78);
	hffile_userbin_write(JD_PRIVATE_ADDR,(char *)&g_hf_jdconfig,sizeof(g_hf_jdconfig));
	memcpy(g_hf_jdconfig.jd_mac,mac,12);
	memcpy(g_hf_jdconfig.jd_prikey,prikey,64);
	hffile_userbin_write(JD_PRIVATE_ADDR,(char *)&g_hf_jdconfig,sizeof(g_hf_jdconfig));
}

static int hf_atcmd_setprikey(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		sprintf(rsp,"=%s,%s",read_mac(),read_prikey());
		return 0;
	}
	else if(argc == 2)
	{
		u_printf("argv[0]=%s,argv[1]=%s\r\n",argv[0],argv[1]);
		write_prikey(argv[0],argv[1]);
		return 0;
	}

	return -3;
}

static int hf_atcmd_power_ctl(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if(argc==0)
	{ 
		if(user_dev.OnOff_state)
			user_dev.OnOff_state = 0;
		else
			user_dev.OnOff_state = 1;
		
		joylink_server_send_flag = 1;

		return 0;
	}
	return -3;
}

/* json format must is key@mac */
void product_para_jdkey(int valueint, char *valuestring)
{
	write_prikey(valuestring,valuestring+13);
}

const hfproduct_cmd_t user_define_product_cmds_table[]=
{
	{"jdkey",  product_para_jdkey},
	{NULL, NULL} //the last item must be null
};

const hfat_cmd_t user_define_at_cmds_table[]=
{
	{"STARTJDSOFTAP", hf_atcmd_start_jd_softap, "   AT+STARTJDSOFTAP: start jd softap.\r\n",NULL},
	{"STARTJDSMARTBLE", hf_atcmd_start_jd_smartble, "   AT+STARTJDSMARTBLE: start jd STARTJDSMARTBLE.\r\n",NULL},
	{"SETPRIKEY", hf_atcmd_setprikey, "   AT+PRIKEY: write prikey.\r\n",NULL},
	{"POWER", hf_atcmd_power_ctl, "   AT+POWER: jd POWER ctl.\r\n",NULL},
	{NULL,NULL,NULL,NULL} //the last item must be null
};

#define WLAN_FW_SUCCESSFUL                                        0 
#define WLAN_FW_TX_AUTH_FRAME_ALLOCATE_FAIILURE                   1 
#define WLAN_FW_AUTHENTICATION_FAIILURE                           2
#define WLAN_FW_AUTH_ALGO_FAIILURE                                3
#define WLAN_FW_TX_ASSOC_FRAME_ALLOCATE_FAIILURE                  4 
#define WLAN_FW_ASSOCIATE_FAIILURE                                5
#define WLAN_FW_DEAUTH_BY_AP_WHEN_NOT_CONNECTION                  6
#define WLAN_FW_DEAUTH_BY_AP_WHEN_CONNECTION                      7
#define WLAN_FW_4WAY_HANDSHAKE_ERROR_PSK_TIMEOUT_FAILURE          8
#define WLAN_FW_4WAY_HANDSHAKE_TX_DEAUTH_FRAME_TRANSMIT_FAILURE   9
#define WLAN_FW_4WAY_HANDSHAKE_TX_DEAUTH_FRAME_ALLOCATE_FAIILURE 10
#define WLAN_FW_AUTH_OR_ASSOC_RESPONSE_TIMEOUT_FAILURE           11
#define WLAN_FW_SCAN_NO_BSSID_AND_CHANNEL                        12
#define WLAN_FW_CREATE_CHANNEL_CTX_FAILURE_WHEN_JOIN_NETWORK     13
#define WLAN_FW_JOIN_NETWORK_FAILURE                             14
#define WLAN_FW_ADD_STA_FAILURE                                  15
#define WLAN_FW_BEACON_LOSS                                      16
#define WLAN_FW_JOIN_NETWORK_SECURITY_NOMATCH                    17
#define WLAN_FW_JOIN_NETWORK_WEPLEN_ERROR                        18
#define WLAN_FW_DISCONNECT_BY_USER_WITH_DEAUTH                   19
#define WLAN_FW_DISCONNECT_BY_USER_NO_DEAUTH                     20
#define WLAN_FW_DISCONNECT_BY_FW_PS_TX_NULLFRAME_FAILURE         21

static unsigned short ErrorCode;
char scan_suc = 0;
int hf_atcmd_wscan_callback(PWIFI_SCAN_RESULT_ITEM ap,void *ctx)
{
	if(strcmp(ap->ssid,(char *)g_hf_config_file.sta_ssid)==0)
	{
		char data[50];
		sprintf(data,"%d_%ddBm",ErrorCode,ap->rssi_dbm);
		u_printf("E_JL_NET_CONF_ST_CONFIG_FAILED_INFO\r\n");
		jl_send_net_config_state(E_JL_NET_CONF_ST_CONFIG_FAILED_INFO,(uint8_t *)data,strlen(data));
		scan_suc = 1;
	}
	return 0;
}
static int sys_event_callback( uint32_t event_id,void * param)
{
	switch(event_id)
	{
		case HFE_WIFI_STA_CONNECTED:
			u_printf("wifi sta connected!!\n");
			break;
		case HFE_WIFI_STA_DISCONNECTED:
			u_printf("wifi sta disconnected!!\n");
			break;
		case HFE_CONFIG_RELOAD:
			u_printf("reload!\n");
			break;
		case HFE_DHCP_OK:
			{
				uint32_t *p_ip;
				int rssi=0,dbm=0;
				dhcp_ok_flag = 1;
				p_ip = (uint32_t*)param;
				rssi = hfwifi_sta_get_current_rssi(&dbm);
				u_printf("dhcp ok %s rssi %d!\n", inet_ntoa(*p_ip),dbm);
				uint8_t data[2]={0x00,0x00};
				data[0] = dbm&0xFF;
				data[1] = (dbm>>8)&0xFF;
				if(has_softap_flag>0){
					u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_SUCCEED!\n");
					jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_SUCCEED,NULL,0);
					msleep(100);
					u_printf("E_JL_NET_CONF_ST_WIFI_RSSI!\n");
					jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_RSSI,data,2);
				}
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
		case HFE_BLE_CONNECTED:
			{
				u_printf("ble connect!\n");
			}
			break;
		case HFE_BLE_DISCONNECTED:
			{
				u_printf("ble disconnect!\n");
			}
			break;	
	}
	return 0;
}
/*
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
*/
static uint8_t bt_ntf_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len)
{
	if(event==HFNET_BT_NTF_DATA_READY)
	{	
		HF_Debug(DEBUG_LEVEL_LOW,"hf ble recv %d bytes %d\n",len,buf_len);

		jl_write_data( (unsigned char *)data,  (int)len);

	}	
	else if(event==HFNET_BT_NTF_DATA_ENABLE)
		u_printf("hf ble ntf connected!\n");
	else if(event==HFNET_BT_NTF_DATA_DISENABLE)
		u_printf("hf ble ntf disconnected!\n");
	
	return 0;
}

hfthread_hande_t jl_send_thread_handle;
char jl_ble_send_thread = 0;

static uint8_t bt_ind_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len)
{
	if(event==HFNET_BT_IND_DATA_READY)
	{	
		HF_Debug(DEBUG_LEVEL_LOW,"hf ble ind recv %d bytes %d\n",len,buf_len);

		jl_write_data( (unsigned char *)data,  (int)len);
	}
	else if(event==HFNET_BT_IND_DATA_ENABLE)
	{		
		u_printf("hf ble ind connected!\n");
		
		if(hfthread_create((PHFTHREAD_START_ROUTINE)jl_send_thread, "jl_send_thread", 512*4, NULL, HFTHREAD_PRIORITIES_LOW,&jl_send_thread_handle,NULL)!= HF_SUCCESS)
			u_printf("JD_SOFTAP_THREAD create failed!\r\n");
		else
			jl_ble_send_thread = 1;
	}
	else if(event==HFNET_BT_IND_DATA_DISENABLE)
	{		
		u_printf("hf ble ind disconnected!\n");
		jl_disconnet_reset();
		if(jl_ble_send_thread==1)
		{
			u_printf("hfthread_destroy jl_send_thread_handle!\n");
			hfthread_destroy(jl_send_thread_handle);
			jl_ble_send_thread=0;
//			has_softap_flag = -2;
	//		hfgpio_fset_out_low(USER_LINK);	
		//	hf_close_ble();
		}
	}	
	return 0;
}

static int USER_FUNC uart_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len)
{
	if(event == HFNET_UART0_DATA_READY)
		HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart 0 recv %d bytes data %d\n",event,len,buf_len);
	else if(event == HFNET_UART1_DATA_READY)
		HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart 1 recv %d bytes data %d\n",event,len,buf_len);
	if(hfsys_get_run_mode() == HFSYS_STATE_RUN_CMD)
		return len;
	
	return len;
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

static void clear_softap()
{
	uint8_t softap_flag=0;
	hffile_userbin_write(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
}

void joylink_softap_thread(void)
{
	clear_softap();
	joylink_softap_start(300000);
	while(1)
	{

		msleep(10);
	}
}

extern hfthread_mutex_t sock_send_recv_mutex;

void ismode_soaftap()
{
	uint8_t softap_flag=0;
	uint8_t magic_flag=0;
	char rsp[64]={0};
	hffile_userbin_read(JD_MAGIC_ADDR,(char *)&magic_flag,1);
	hffile_userbin_read(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
	hffile_userbin_read(JD_PRIVATE_ADDR,(char *)&g_hf_jdconfig,sizeof(g_hf_jdconfig));
	u_printf("softap_flag=%d\n",softap_flag);
	u_printf("magic_flag=%d\n",magic_flag);
	u_printf("mac=%s g_dev_prikey=%s\n",g_hf_jdconfig.jd_mac,g_hf_jdconfig.jd_prikey);
	
	if(magic_flag != MAGIC_VALUE)
	{
		u_printf("first in\r\n");
		magic_flag = MAGIC_VALUE;
		hffile_userbin_write(JD_MAGIC_ADDR,(char *)&magic_flag,1);
		msleep(100);
		memset(&jdArgs,0,sizeof(JLPInfo_t));
		hffile_userbin_write(JDCONFIG_OFFSET, (char*)&jdArgs, sizeof(JLPInfo_t));
		msleep(100);
		enter_smtble_flag=1;
	}
	else
	{
		if(softap_flag == 0x11)
		{
			memset(g_hf_config_file.sta_ssid,0,33);
			memset(g_hf_config_file.sta_key,0,65);
	 		hfconfig_file_save();
			
			memset(jdArgs.feedid,0,JL_MAX_FEEDID_LEN);
			hffile_userbin_write(JDCONFIG_OFFSET, (char*)&jdArgs, sizeof(JLPInfo_t));
			
			u_printf("ble config\r\n");
			clear_softap();
			has_softap_flag=1;
			hf_start_ble();
		}
		else if(softap_flag == 0x22)
		{
			memset(g_hf_config_file.sta_ssid,0,33);
			memset(g_hf_config_file.sta_key,0,65);
	 		hfconfig_file_save();
			
			memset(jdArgs.feedid,0,JL_MAX_FEEDID_LEN);
			hffile_userbin_write(JDCONFIG_OFFSET, (char*)&jdArgs, sizeof(JLPInfo_t));
			
			u_printf("ap config\r\n");
			if(hfthread_create((PHFTHREAD_START_ROUTINE)joylink_softap_thread, "JD_SOFTAP_THREAD", 1024*2, NULL, HFTHREAD_PRIORITIES_LOW,NULL,NULL)!= HF_SUCCESS)
			{
				u_printf("JD_SOFTAP_THREAD create failed!\r\n");
			}	
		}
		else
		{
			hfat_send_cmd("AT+WMODE\r\n", strlen("AT+WMODE\r\n"), rsp, sizeof(rsp));
			if(strstr("+ok=AP",rsp)!=NULL)
			{
				hfat_send_cmd("AT+WMODE=STA\r\n", strlen("AT+WMODE=STA\r\n"), rsp, sizeof(rsp));
				hfat_send_cmd("AT+Z\r\n", strlen("AT+Z\r\n"), rsp, sizeof(rsp));
			}
			u_printf("not ap config\r\n");
		}
		hfthread_mutext_new(&sock_send_recv_mutex);		//socket接收发送互斥锁
	}
}


void app_init(void)
{
	u_printf("app_init\n");
}

jl_gap_data_t g_gap_data;

void app_fill_ble_adv_data(void)
{
	jl_dev_info_t dev_info;
	int i;
	uint8_t mac_temp[12]={0};
	
	memset(&dev_info,0,sizeof(dev_info));
	memset(&g_gap_data,0,sizeof(g_gap_data));
	
	for(i=0;i<12;i++)
		char2hex(g_hf_jdconfig.jd_mac[i],&mac_temp[i]);

	for(i=0;i<12;i++)
		u_printf("%02X ",mac_temp[i]);
	u_printf("\r\n");

	dev_info.mac[0] = mac_temp[1] + mac_temp[0]*16;
	dev_info.mac[1] = mac_temp[3] + mac_temp[2]*16;
	dev_info.mac[2] = mac_temp[5] + mac_temp[4]*16;
	dev_info.mac[3] = mac_temp[7] + mac_temp[6]*16;
	dev_info.mac[4] = mac_temp[9] + mac_temp[8]*16;
	dev_info.mac[5] = mac_temp[11] + mac_temp[10]*16;
	
	memcpy((char *)&dev_info.product_uuid,JLP_UUID,6);
	
	u_printf("\r\nproduct_uuid\r\n");
	for(i=0;i<6;i++) 
		u_printf("%02X ",dev_info.product_uuid[i]);
	u_printf("\r\n");
	
	u_printf("mac \r\n");
	for(i=0;i<6;i++)
		u_printf("%02X ",dev_info.mac[i]);
	u_printf("\r\n");

	jl_init(&dev_info);
	jl_get_gap_config_data(&g_gap_data);
	
	u_printf("manufacture_data\r\n");
	for(i=0;i<14;i++)
		u_printf("%02X ",g_gap_data.manufacture_data[i]);
	u_printf("\r\n");
	
	u_printf("service_uuid16\r\n");
	for(i=0;i<2;i++)
		u_printf("%02X ",g_gap_data.service_uuid16[i]);
	u_printf("\r\n");

	// user fill self ble adv data
	static uint8_t raw_adv1[23] = {0x02,0x01,0x06,
	0x0F,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x03,0x03,0x00,0x00};
	static uint8_t raw_adv[4] = {0x03,0x09,'J','D'};
	
	extern GAPP_DISC_DATA_T Advertisement_Data;
	
	raw_adv1[5]	= g_gap_data.manufacture_data[0];
	raw_adv1[6]	= g_gap_data.manufacture_data[1];
	raw_adv1[7]	= g_gap_data.manufacture_data[2];
	raw_adv1[8]	= g_gap_data.manufacture_data[3];
	raw_adv1[9]	= g_gap_data.manufacture_data[4];
	raw_adv1[10] = g_gap_data.manufacture_data[5];
	raw_adv1[11] = g_gap_data.manufacture_data[6];
	raw_adv1[12] = g_gap_data.manufacture_data[7];
	raw_adv1[13] = g_gap_data.manufacture_data[8];
	raw_adv1[14] = g_gap_data.manufacture_data[9];
	raw_adv1[15] = g_gap_data.manufacture_data[10];
	raw_adv1[16] = g_gap_data.manufacture_data[11];
	raw_adv1[17] = g_gap_data.manufacture_data[12];
	raw_adv1[18] = g_gap_data.manufacture_data[13];
	
	raw_adv1[21] = g_gap_data.service_uuid16[0];
	raw_adv1[22] = g_gap_data.service_uuid16[1];

	memset(Advertisement_Data.advData,0,sizeof(Advertisement_Data.advData));
	memcpy(Advertisement_Data.advData,raw_adv1,sizeof(raw_adv1));
	Advertisement_Data.advDataLen = sizeof(raw_adv1);
	
	memset(Advertisement_Data.advrspData,0,sizeof(Advertisement_Data.advrspData));
	memcpy(Advertisement_Data.advrspData,raw_adv,sizeof(raw_adv));
	Advertisement_Data.advrspDataLen = sizeof(raw_adv);
	
}

void ssid_reset()
{
	char rsp[64]={0};
	
	msleep(200);
	hfat_send_cmd("AT+WSSSID=UPGRADE-AP\r\n", strlen("AT+WSSSID=UPGRADE-AP\r\n"), rsp, sizeof(rsp));
	msleep(200);
	hfat_send_cmd("AT+WSKEY=OPEN,NONE\r\n", strlen("AT+WSKEY=OPEN,NONE\r\n"), rsp, sizeof(rsp));
	msleep(200);

}

char down_present = 0;
extern char joylink_config_flag;
char get_wifi_info = 0;
void jd_thread()
{
	char softap_flag = 0,no_ssid_cnt=0,psk_error_cnt=0;;
	unsigned int cnt=0,wifi_cnt=0;
	hffile_userbin_read(JD_SOFTAP_ADDR,(char *)&softap_flag,1);
	while(1)
	{
		msleep(10);
		if(joylink_server_send_flag)
		{
			joylink_server_upload_req();
			u_printf("/////////////////upload_data///////////////\r\n");
			joylink_server_send_flag = 0;
		}
		
		if(reset_factory_flag)
		{
			memset(&jdArgs,0,sizeof(JLPInfo_t));
			//hffile_userbin_write(JDCONFIG_OFFSET, (char*)&jdArgs, sizeof(JLPInfo_t));
			u_printf("/////////////////ssid_reset///////////////\r\n");
			ssid_reset();
			enter_smtble_flag = 1;
		}
		
		if(enter_softap_flag)
			hf_jd_softap_start();
		if(enter_smtble_flag)
			hf_jd_smartble_start();

		if(down_present != 0 && down_present != 100){
			cnt++;
			if(cnt == 100){
				cnt = 0;
				joylink_ota_report_status(OTA_STATUS_DOWNLOAD, down_present, "Downloading...");
			}
		}
		
		if(has_softap_flag>0)
		{
			cnt++;
			
			if(cnt == JD_CONFIG_TIMEOUT*100)//30min timeout
			{
				if(dhcp_ok_flag!=1)
				{
					u_printf("E_JL_NET_CONF_ST_TIMEOUT_EXIT!\n");
					jl_send_net_config_state(E_JL_NET_CONF_ST_TIMEOUT_EXIT,NULL,0);
					msleep(1000);
					hfsys_reset();
				}
			}
			
			if(joylink_config_flag==0)//收到wifi disconnected
			{
				joylink_config_flag = 1;
				ErrorCode=hfwifi_get_disconnect_code();
				u_printf("ErrorCode %d!\n",ErrorCode);
				if(ErrorCode == WLAN_FW_SCAN_NO_BSSID_AND_CHANNEL){
					no_ssid_cnt++;
					u_printf("no_ssid_cnt %d!\n",no_ssid_cnt);
				}
				else if(ErrorCode == WLAN_FW_DEAUTH_BY_AP_WHEN_NOT_CONNECTION || \
					ErrorCode == WLAN_FW_4WAY_HANDSHAKE_ERROR_PSK_TIMEOUT_FAILURE || \
					ErrorCode == WLAN_FW_4WAY_HANDSHAKE_TX_DEAUTH_FRAME_TRANSMIT_FAILURE || \
					ErrorCode == WLAN_FW_4WAY_HANDSHAKE_TX_DEAUTH_FRAME_ALLOCATE_FAIILURE || \
					ErrorCode == WLAN_FW_JOIN_NETWORK_SECURITY_NOMATCH)
				{
					psk_error_cnt++;
					u_printf("psk_error_cnt %d!\n",psk_error_cnt);
				}
			}
			
			if(get_wifi_info == 1 && dhcp_ok_flag!=1)//收到SSID，1min配网超时
			{
				wifi_cnt++;
				if(wifi_cnt!=100*JD_CONFIG_NET_TIMEOUT)
					continue;
				if(no_ssid_cnt!=0||psk_error_cnt!=0)
				{
					if(no_ssid_cnt>=psk_error_cnt){
						u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_SSID_ERROR!\n");
						jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_SSID_ERROR,NULL,0);
					}else{
						u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_PSK_ERROR!\n");
						jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_PSK_ERROR,NULL,0);
					}
					no_ssid_cnt = 0;
					psk_error_cnt = 0;
				}
				else
				{
					u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_FAILED!\n");
					jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_FAILED,NULL,0);
				}
			
				msleep(100);
				scan_suc = 0;
				hfwifi_scan_ex(hf_atcmd_wscan_callback, NULL, 0, 5);

				if(scan_suc == 0){
					char data[50];
					u_printf("can not scan this ssid\n");
					sprintf(data,"%d_%ddBm",ErrorCode,0);
					u_printf("E_JL_NET_CONF_ST_CONFIG_FAILED_INFO!\n");
					jl_send_net_config_state(E_JL_NET_CONF_ST_CONFIG_FAILED_INFO,(uint8_t *)data,strlen(data));
				}

				has_softap_flag = -4;
				enter_smtble_flag=1;
			}
		}
	}
}


void USER_FUNC timer_callback( hftimer_handle_t htimer )
{	
	if(hftimer_get_timer_id(htimer)==LOCAL_20MS_TIMER_ID)
	{
		if(hfgpio_fpin_is_high(USER_RELOAD))
		{
			if(press_reload_button)
			{
				button_cnt++;
				if(button_cnt==3)
				{
					if(hfgpio_fpin_is_high(USER_RELOAD))
					{	
						u_printf("release the reload button!\n");
					
						if(press_reload_button > 50 && press_reload_button <100)
						{	
							enter_smtble_flag = 1;
							u_printf("enter_softap!\n");
						}
						else if(press_reload_button > 100)
						{	
							reset_factory_flag = 1;
							u_printf("reset_factory!\n");
						}
						
						if(user_dev.OnOff_state)
						{
							user_dev.OnOff_state = 0;
							hfgpio_fset_out_high(USER_LINK);
							joylink_server_send_flag = 1;
						}
						else
						{
							user_dev.OnOff_state = 1;
							hfgpio_fset_out_low(USER_LINK);
							joylink_server_send_flag = 1;
						}
						
						if(has_softap_flag>2){
							has_softap_flag = -4;
							u_printf("E_JL_NET_CONF_ST_EXIT\r\n");
							jl_send_net_config_state(E_JL_NET_CONF_ST_EXIT,NULL,0);
							msleep(1000);
							hfsys_reset();
						}
						press_reload_button = 0;
					}
					button_cnt = 0;
				}
			}
		}
		else
		{
			button_cnt++;
			if(button_cnt==3)
			{		
				press_reload_button++;
				//u_printf("press the reload button!\n");
				button_cnt = 0;
			}
		}
	}
	if(hftimer_get_timer_id(htimer)==LOCAL_05S_TIMER_ID)
	{
		if(has_softap_flag>0 && has_softap_flag<JD_CONFIG_TIMEOUT*2)//30MIN
		{
			if(hfgpio_fpin_is_high(USER_LINK))
				hfgpio_fset_out_low(USER_LINK);
			else
				hfgpio_fset_out_high(USER_LINK);	
			has_softap_flag++;
		}
	}
	if(hftimer_get_timer_id(htimer)==LOCAL_1S_TIMER_ID)
		jd_sys_time++;
}

void gpio_config()
{
	hfgpio_configure_fpin(USER_LINK,HFM_IO_OUTPUT_1);
	hfgpio_configure_fpin(USER_READY,HFM_IO_TYPE_INPUT);
	hfgpio_configure_fpin(USER_RELOAD,HFM_IO_TYPE_INPUT);
}

void off_lowpower()
{
	char rsp[64]={0};
	hfat_send_cmd("AT+DISPS\r\n", strlen("AT+DISPS\r\n"), rsp, sizeof(rsp));
	if(strstr(rsp,"Auto")!=NULL)
	{
		hfat_send_cmd("AT+DISPS=YES\r\n", strlen("AT+DISPS=YES\r\n"), rsp, sizeof(rsp));
	}
}

void uuid_init()
{
	char rsp[64] = {0};
	char reset_cnt = 0;
	
	hfat_send_cmd("AT+BLENTFUUIDS\r\n",sizeof("AT+BLENTFUUIDS\r\n"),rsp,sizeof(rsp));
	if(strstr(rsp,"+ok=0000FE7000001000800000805F9B34FB") == NULL)
	{
		hfat_send_cmd("AT+BLENTFUUIDS=0000FE7000001000800000805F9B34FB\r\n",sizeof("AT+BLENTFUUIDS=0000FE7000001000800000805F9B34FB\r\n"),rsp,sizeof(rsp));
		reset_cnt++;
	}
	hfat_send_cmd("AT+BLEINDUUIDW\r\n",sizeof("AT+BLEINDUUIDW\r\n"),rsp,sizeof(rsp));
	if(strstr(rsp,"+ok=0000FE7100001000800000805F9B34FB") == NULL)
	{
		hfat_send_cmd("AT+BLEINDUUIDW=0000FE7100001000800000805F9B34FB\r\n",sizeof("AT+BLEINDUUIDW=0000FE7100001000800000805F9B34FB\r\n"),rsp,sizeof(rsp));
		reset_cnt++;
	}
	hfat_send_cmd("AT+BLEINDUUIDR\r\n",sizeof("AT+BLEINDUUIDR\r\n"),rsp,sizeof(rsp));
	if(strstr(rsp,"+ok=0000FE7200001000800000805F9B34FB") == NULL)
	{
		hfat_send_cmd("AT+BLEINDUUIDR=0000FE7200001000800000805F9B34FB\r\n",sizeof("AT+BLEINDUUIDR=0000FE7200001000800000805F9B34FB\r\n"),rsp,sizeof(rsp));
		reset_cnt++;
	}
	if(reset_cnt)
	 	hfsys_reset();
}

int USER_FUNC app_main (void)
{	
	HF_Debug(DEBUG_LEVEL,"sdk version(%s) joylink(%s),the app_main start time is %s %s\r\n","1.0.0",hfsys_get_sdk_version(),__DATE__,__TIME__);
	
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
	//AT+UART uart0
	if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start uart fail!\r\n");
	}
	
	if((local_20ms_timer = hftimer_create("LOCAL_20MS_TIMER_ID",20,TRUE,LOCAL_20MS_TIMER_ID,timer_callback,0))==NULL)
        u_printf("create LOCAL_20MS_TIMER_ID fail\n");
	else
		hftimer_start(local_20ms_timer);

	if((local_05s_timer = hftimer_create("LOCAL_05S_TIMER_ID",500,TRUE,LOCAL_05S_TIMER_ID,timer_callback,0))==NULL)
        u_printf("create LOCAL_05S_TIMER_ID fail\n");
	else
		hftimer_start(local_05s_timer);
	
	if((local_1s_timer = hftimer_create("LOCAL_1S_TIMER_ID",1000,TRUE,LOCAL_1S_TIMER_ID,timer_callback,0))==NULL)
        u_printf("create LOCAL_1S_TIMER_ID fail\n");
	else
		hftimer_start(local_1s_timer);
	
	if(hfnet_start_ble_ntf(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ntf_recv_callback)!=HF_SUCCESS)
	{//udp
		HF_Debug(DEBUG_WARN,"start ble ntf fail\n");
	}
	
	if(hfnet_start_ble_ind(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ind_recv_callback)!=HF_SUCCESS)
	{//tcp
		HF_Debug(DEBUG_WARN,"start ble ntf fail\n");
	}

	uuid_init();
	ismode_soaftap();
	gpio_config();
	off_lowpower();
		
	if(hfthread_create((PHFTHREAD_START_ROUTINE)jd_thread, "JD_THREAD", 512*3, NULL, HFTHREAD_PRIORITIES_LOW,NULL,NULL)!= HF_SUCCESS)
	{
		u_printf("JD_THREAD create failed!\r\n");
	}	
	
	while(dhcp_ok_flag==0)
	{
		jl_platform_msleep(50);
	}
	
	u_printf("\r\n/************joylink_main_start!************/\r\n");
	jl_platform_msleep(500);
	joylink_dev_lan_active_switch(1);
	jl_thread_t task_id; 

	task_id.thread_task = (threadtask) joylink_main_start;
	task_id.stackSize = 512*6;
	task_id.priority = JL_THREAD_PRI_LOWEST;
	task_id.parameter = NULL;
	jl_platform_thread_start(&task_id);

	return 1;
}
