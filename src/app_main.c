 /* app_main.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <hsf.h>
#include <hfsys.h>
#include <stdlib.h>
#include <string.h>
#include <hf_debug.h>

const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE];

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

const hfat_cmd_t user_define_at_cmds_table[]=
{
	{NULL,NULL,NULL,NULL} //the last item must be null
};

int hfble_scan_callback(PBLE_SCAN_RESULT_ITEM item) {
	return 0;
}


void app_init(void) {
	u_printf("app_init\n");
}

extern int bl_uart_data_send(uint8_t id, uint8_t data);

/*static int USER_FUNC uart_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len) {
	if(event == HFNET_UART0_DATA_READY) {
	    bl_uart_data_send(0, '0');
	    for(int i = 0; i < len; i++) bl_uart_data_send(1, data[i]);
	}

	else if(event == HFNET_UART1_DATA_READY) {
		// HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart 1 recv %d bytes data %d\n",event,len,buf_len);
		bl_uart_data_send(0, '1');
		for(int i = 0; i < len; i++) bl_uart_data_send(0, data[i]);
	}
	if(hfsys_get_run_mode() == HFSYS_STATE_RUN_CMD)
		return len;
	return len;
}*/

USER_FUNC void uart_bridge(void* arg) {

	hfuart_handle_t huart0 = NULL;
	hfuart_handle_t huart1 = NULL;
	char *buf0 = NULL;
	char *buf1 = NULL;
	int recv_bytes;

	huart0 = hfuart_open(0);
	if(!huart0) {
		u_printf("open UART0 fail\n");
		goto exit_thread;
	}

	huart1 = hfuart_open(1);
	if(!huart1) {
		u_printf("open UART1 fail\n");
		goto exit_thread;
	}
	//HF_Debug(DEBUG_ERROR,"UART 1 opened\n");

	#if (BAUDRATE != 115200) && (BAUDRATE != 9600)
	#error BAUDRATE should be 9600 or 115200 
	#endif
	#if (DATABITS != 7) && (DATABITS != 8)
	#error DATABITS should be 7 or 8
	#endif

	hfuart_config(huart0, BAUDRATE, COMPARITY_NONE, DATABITS - 5, COMSTOPBITS_1, COMUARTNFC); // debug here
	hfuart_config(huart1, BAUDRATE, COMPARITY_NONE, DATABITS - 5, COMSTOPBITS_1, COMUARTNFC); // debug here
	
	buf0 = (char*)hfmem_malloc(1000);
	if(!buf0) {
		u_printf("memory alloc fail\n");
		goto exit_thread;
	}
	buf1 = (char*)hfmem_malloc(1000);
	if(!buf1) {
		u_printf("memory alloc fail\n");
		goto exit_thread;
	}

	while(1) {
		recv_bytes = hfuart_recv(huart0, buf0, 1000, 1000);
		if(recv_bytes > 0) {
			for(int i = 0; i < recv_bytes; i++) bl_uart_data_send(1, buf0[i]);
		}
		recv_bytes = hfuart_recv(huart1, buf1, 1000, 1000);
		if(recv_bytes > 0) {
			for(int i = 0; i < recv_bytes; i++) bl_uart_data_send(0, buf1[i]);
		}
	}
	
exit_thread:
	if(buf0 != NULL) hfmem_free(buf0);
	if(buf1 != NULL) hfmem_free(buf1);
	if(huart0) hfuart_close(huart0);
	if(huart1) hfuart_close(huart1);
	hfthread_destroy(NULL);
	return;
}


int USER_FUNC app_main (void) {	
    hfdbg_set_level(1);
    hfgpio_configure_pin(0x3830015,0x20000000); // To power on Air780e onboard chip 

	if(hfgpio_fmap_check(g_module_id)!=0) {
		while(1) {
			HF_Debug(DEBUG_ERROR,"gpio map file error\n");
			msleep(1000);
		}
	}
	// if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS) HF_Debug(DEBUG_WARN,"start uart fail!\r\n");
	hfthread_create(uart_bridge, "uart_bridge", 256, NULL, HFTHREAD_PRIORITIES_LOW, NULL,NULL);
	while(true) msleep(100);
	return 1;
}

