 /* sniffiertest.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <hsf.h>
#include <stdlib.h>
#include <string.h>

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

int hfble_scan_callback(PBLE_SCAN_RESULT_ITEM item)
{
	u_printf("---------------------\r\n");
	u_printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n",item->addr[0],item->addr[1],item->addr[2],item->addr[3],item->addr[4],item->addr[5]);
	u_printf("addr_type = %d,rssi = %d,evtype = %d,len = %d\r\n",item->addr_type,item->rssi,item->evtype,item->len);

	u_printf("\r\n");
	int i;
	for(i = 0; i < item->len; i++)
		u_printf("%02x ",item->data[i]);
	u_printf("\r\n");
	u_printf("---------------------\r\n");
	return 0;
}
const hfat_cmd_t user_define_at_cmds_table[]=
{
	{NULL,NULL,NULL,NULL} //the last item must be null
};

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
				p_ip = (uint32_t*)param;
				u_printf("dhcp ok %s!\n", inet_ntoa(*p_ip));
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

#define DATA_FROM_DS			(0x0200)
#define DATA_TO_DS				(0x0100)

void hfsniffer_recv_callback(uint8_t* pkt,uint32_t pkt_len)
{
	uint8_t *p_data = (uint8_t*)pkt;
	uint8_t  b_mac[6]= {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	uint8_t  m_mac[6]= {0x01, 0x00, 0x5e, 0x0,0x0,0x0};
	uint16_t frame_control = pkt?(p_data[1]<<8)|p_data[0]:0;
	uint8_t *appMac;
	uint8_t *bssid;
	uint8_t *dstMac;
	
	if(p_data && ((p_data[0]&0x0C)==0))
	{
		if((p_data[0]&0xF0)==0x80)
		{
			u_printf("beacon packet\r\n");
		}
		else if((p_data[0]&0xF0)==0x40)
		{
			u_printf("probe request packet\r\n");
		}
		else if((p_data[0]&0xF0)==0x50)
		{
			u_printf("probe response packet\r\n");
		}
		
		return;
	}
	
	if((frame_control&DATA_FROM_DS)&&((frame_control&DATA_TO_DS)!=DATA_TO_DS))
	{
		dstMac = p_data+4;
		bssid = p_data+4+6;
		appMac = p_data+4+6*2;
	}
	else if((frame_control&DATA_TO_DS)&&((frame_control&DATA_FROM_DS)!=DATA_FROM_DS))
	{
		dstMac = p_data+4+6*2;
		bssid = p_data+4;
		appMac = p_data+4+6;
	}
	else
		return;
	
	if(0 == memcmp(dstMac,b_mac,6))
	{
		u_printf("broadcast packet, appmac: %02X%02X%02X%02X%02X%02X, bssid: %02X%02X%02X%02X%02X%02X\r\n",
			appMac[0], appMac[1], appMac[2], appMac[3], appMac[4], appMac[5],
			bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
	}
	else if(0 == memcmp(dstMac,m_mac,3))
	{
		u_printf("multicast packet, appmac: %02X%02X%02X%02X%02X%02X, bssid: %02X%02X%02X%02X%02X%02X\r\n",
			appMac[0], appMac[1], appMac[2], appMac[3], appMac[4], appMac[5],
			bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
	}
	
	return ;
}

void app_init(void)
{
	u_printf("app_init\n");
	
	u_printf("start 802.11 sniffer test ...\r\n");
	hfsniffer_start(HFSNIFFER_RECE_MODE_BEACON_MANAG|HFSNIFFER_RECE_MODE_BROADCAST_DATA|HFSNIFFER_RECE_MODE_TO_DS|HFSNIFFER_RECE_MODE_FROM_DS, hfsniffer_recv_callback);
	
	int ch = 1;
	while(1)
	{
		u_printf("set ch %d\r\n", ch);
		hfsniffer_set_channel(ch, 0);
		msleep(300);
		
		ch++;
		if(ch > 13)
			ch = 1;
	}
}

int USER_FUNC app_main (void)
{	
	HF_Debug(DEBUG_LEVEL,"sdk version(%s),the app_main start time is %s %s\r\n",hfsys_get_sdk_version(),__DATE__,__TIME__);
	
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
	
	while(hfsmtlk_is_start())
		msleep(100);
	
	while(!hfnet_wifi_is_active())
	{
		msleep(50);
	}
	
	//See Wi-Fi Config tools APP for detailed usage of this thread
	if(hfnet_start_assis(ASSIS_PORT)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start assis fail\r\n");
	}
	
	//AT+NETP socket
	if(hfnet_start_socketa(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)socketa_recv_callback)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start socketa fail\r\n");
	}
	
	//AT+SOCKB socket
	if(hfnet_start_socketb(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)socketb_recv_callback)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start socketb fail\r\n");
	}
	
	//Web Server
	if(hfnet_start_httpd(HFTHREAD_PRIORITIES_MID)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start httpd fail\r\n");
	}
	
	return 1;
}

