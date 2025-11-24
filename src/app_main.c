 /* 
 * Copyright (C) freshev@github.com
 */

#include <hsf.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ble_ntf_thread.h>
#include <ble_ind_thread.h>
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

extern int bl_uart_data_send(uint8_t id, uint8_t data);

#ifdef DEBUG_VIA_BLE

static int hf_debug_level = 0;
static hfthread_mutex_t g_debug_lock = NULL_MUTEX;
static char hf_debug_buf[512];

void HSF_API HF_Debug(int debug_level, const char *format, ... ) {
  size_t len;

  va_list args;
  va_start(args, format);  

  if ((hf_debug_level <= debug_level) && (0 < hf_debug_level)) {
    if (g_debug_lock == (hfthread_mutex_t)0x0) {
      hfthread_mutext_new(&g_debug_lock);
    }
    hfthread_mutext_wait(g_debug_lock,0xffffffff);
    memset(hf_debug_buf, 0, 512);
    vsnprintf(hf_debug_buf, 511, format, args);
    len = strlen(hf_debug_buf);
    // if (g_hf_config_file.uart1_debug == 1) huart = HFUART1;
    // else huart = HFUART0;
    //hfuart_send(huart, hf_debug_buf, len, 1000);    
    hf_send_ble_data((uint8_t*)hf_debug_buf, len);
    hfthread_mutext_unlock(g_debug_lock);
  }
  va_end(args);
}

/*void HF_Debug(int debug_level, const char *format, ...) {
  size_t len;
  hfuart_handle_t huart;

  va_list args;
  va_start(args, format);  

  if ((hf_debug_level <= debug_level) && (0 < hf_debug_level)) {
    if (g_debug_lock == (hfthread_mutex_t)0x0) {
      hfthread_mutext_new(&g_debug_lock);
    }
    hfthread_mutext_wait(g_debug_lock,0xffffffff);
    memset(hf_debug_buf, 0, 512);
    vsnprintf(hf_debug_buf, 511, format, args);
    len = strlen(hf_debug_buf);
    if (g_hf_config_file.uart1_debug == 1) huart = HFUART1;
    else huart = HFUART0;
    hfuart_send(huart, hf_debug_buf, len, 1000);
    hfthread_mutext_unlock(g_debug_lock);
  }
  va_end(args);
}*/

int hfdbg_get_level(void) {
  if (hfconfig_is_valid()) {
    uint8_t config_debug_level = g_hf_config_file.debug_level;
    if(config_debug_level != hf_debug_level) {
    	hf_debug_level = config_debug_level;
    }
  }
  return hf_debug_level;
}
void hfdbg_set_level(int level) {
  if (level < 0) level = 0;
  g_hf_config_file.debug_level = (uint8_t)level;
  hf_debug_level = level;
  hfconfig_file_save();
  return;
}

int hfdbg_get_uartno(void) {
  if (hfconfig_is_valid()) return (int)g_hf_config_file.uart1_debug;
  else return 0;
}

#endif


void app_init(void) {
	u_printf("app_init\n");
}

/*static int USER_FUNC uart_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len) {
	if(event == HFNET_UART0_DATA_READY) {
	    bl_uart_data_send(0, '0');
	    for(int i = 0; i < len; i++) bl_uart_data_send(1, data[i]);
	}

	else if(event == HFNET_UART1_DATA_READY) {
		// u_printf("[%d]uart 1 recv %d bytes data %d\n",event,len,buf_len);
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
	//u_printf("UART 1 opened\n");

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
	// utils_bin2hex
	// hf_send_ble_data -> hf_ble_tp_notify_write  (UUID: 00002B10, READ, NOTIFY) not acknowledged by client
	// send_at_notify_data -> hf_ble_tp_notify_at_write
	// hf_send_ble_ind_data -> hf_ble_tp_indicate_write (UUID: 0000FED6, INDICATE) should by acknowledged by client
	
exit_thread:
	if(buf0 != NULL) hfmem_free(buf0);
	if(buf1 != NULL) hfmem_free(buf1);
	if(huart0) hfuart_close(huart0);
	if(huart1) hfuart_close(huart1);
	hfthread_destroy(NULL);
	return;
}

static uint32_t bt_ntf_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len) {
	if(event==HFNET_BT_NTF_DATA_READY) {
		// hf_send_ble_data(data,len);
		u_printf("\nhf ble ntf recv %d bytes %d\n",len,buf_len);
	}	
	else if(event==HFNET_BT_NTF_DATA_ENABLE) u_printf("\nhf ble ntf connected!\n");
	else if(event==HFNET_BT_NTF_DATA_DISENABLE) u_printf("\nhf ble ntf disconnected!\n");
	return len;
}

static uint32_t bt_ind_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len) {
	if(event==HFNET_BT_IND_DATA_READY) {
		// hf_send_ble_ind_data(data,len);
		u_printf("\nhf ble ind recv %d bytes %d\n",len,buf_len);
	}	
	else if(event==HFNET_BT_IND_DATA_ENABLE) u_printf("\nhf ble ind connected!\n");
	else if(event==HFNET_BT_IND_DATA_DISENABLE) u_printf("\nhf ble ind disconnected!\n");
	return len;
}

int USER_FUNC app_main (void) {	
    hfdbg_set_level(1);
    hfgpio_configure_pin(0x3830015,0x20000000); // To power on Air780e onboard chip 

	if(hfgpio_fmap_check(g_module_id)!=0) {
		while(1) {
			u_printf("gpio map file error\n");
			msleep(1000);
		}
	}

    if(hfnet_start_ble_ntf(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ntf_recv_callback)!=HF_SUCCESS)	{
		u_printf("start ble ntf fail\r\n");
	} else u_printf("start ble ntf success\r\n");
	
	if(hfnet_start_ble_ind(HFTHREAD_PRIORITIES_LOW,(hfble_callback_t)bt_ind_recv_callback)!=HF_SUCCESS)	{
		u_printf("start ble ind fail\r\n");
	} else u_printf("start ind success\r\n");
	
	if(hf_ble_start_switch() == CONFIG_BLE_ON && hf_get_ble_run_mode() == HF_BLE_RUN_THROUGHT_MODE)	{
		hf_start_ble();
	} else u_printf("start ble success\r\n");

	msleep(10000); // to manually start BLE scanner
	
	// if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS) u_printf("start uart fail!\r\n");
	hfthread_create(uart_bridge, "uart_bridge", 256, NULL, HFTHREAD_PRIORITIES_LOW, NULL,NULL);

	while(true) msleep(100);
	return 1;
}

