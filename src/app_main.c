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
static uint8_t send_buf[512];

void HSF_API HF_Debug(int debug_level, const char *format, ... ) {  

  if ((hf_debug_level <= debug_level) && (0 < hf_debug_level)) {
    va_list args;
    va_start(args, format);
    va_end(args);
    size_t len;

    if (g_debug_lock == NULL_MUTEX) hfthread_mutext_new(&g_debug_lock);    
    hfthread_mutext_lock(g_debug_lock);

    memset(hf_debug_buf, 0, sizeof(hf_debug_buf));
    vsnprintf(hf_debug_buf, sizeof(hf_debug_buf) - 1, format, args);
    len = strlen(hf_debug_buf);
    hf_send_ble_data((uint8_t*)hf_debug_buf, len); // send notify
    hfthread_mutext_unlock(g_debug_lock);
  }  
}

/*void HF_Debug(int debug_level, const char *format, ...) {
  size_t len;
  hfuart_handle_t huart;

  if ((hf_debug_level <= debug_level) && (0 < hf_debug_level)) {
    va_list args;
    va_start(args, format);  

    if (g_debug_lock == NULL_MUTEX) hfthread_mutext_new(&g_debug_lock);    
    hfthread_mutext_lock(g_debug_lock);

    memset(hf_debug_buf, 0, sizeof(hf_debug_buf));
    vsnprintf(hf_debug_buf, sizeof(hf_debug_buf) - 1, format, args);
    len = strlen(hf_debug_buf);
    if (g_hf_config_file.uart1_debug == 1) huart = HFUART1;
    else huart = HFUART0;
    hfuart_send(huart, hf_debug_buf, len, 1000);
    hfthread_mutext_unlock(g_debug_lock);
    va_end(args);
  }  
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

// utils_bin2hex
// hf_send_ble_data -> hf_ble_tp_notify_write  (UUID: 00002B10, READ, NOTIFY) not acknowledged by client
// send_at_notify_data -> hf_ble_tp_notify_at_write
// hf_send_ble_ind_data -> hf_ble_tp_indicate_write (UUID: 0000FED6, INDICATE) should by acknowledged by client

extern char * utils_bin2hex(uint8_t *dst, uint8_t *src, size_t count);
uint8_t * utils_bin2hex_space(uint8_t *dst, uint8_t *src, size_t count) {
  uint8_t *char2;
  uint8_t *lastchar;
  uint8_t char1;
  
  lastchar = (uint8_t *)((int)src + count);
  char2 = dst;
  for (; (uint8_t *)src != lastchar; src = (void *)((int)src + 1)) {
    char1 = "0123456789ABCDEF"[*src & 0xf];
    *char2 = "0123456789ABCDEF"[*src >> 4];
    char2[1] = char1;
    char2[2] = ' ';
    char2 = char2 + 3;
  }
  return dst + count * 3;
}

void send_ind_data(int direction, uint8_t* buf, int len) {
    uint8_t timebuf[8];
	if(hf_debug_level > 0) {
	    memset(send_buf, 0, sizeof(send_buf));
	    uint32_t t = hfsys_get_time();
	    utils_bin2hex(timebuf, (uint8_t*)&t, 8);
	    send_buf[0] = timebuf[6];
	    send_buf[1] = timebuf[7];
	    send_buf[2] = timebuf[4];
	    send_buf[3] = timebuf[5];
	    send_buf[4] = timebuf[2];
	    send_buf[5] = timebuf[3];
	    send_buf[6] = timebuf[0];
	    send_buf[7] = timebuf[1];
	    send_buf[8] = ' ';
	    send_buf[9] = (direction == 0) ? '0' : '1';
	    send_buf[10] = ':';
	    send_buf[11] = ' ';
	    int minlen = LWIP_MIN(sizeof(send_buf) - 13, len );
	    uint8_t *lastchar = utils_bin2hex_space(send_buf + 12, buf, minlen);
	    *(lastchar + 1) = '0';
	    hf_send_ble_ind_data(send_buf, strlen((char*)send_buf));
	    u_printf((char*)send_buf);
	}
}

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
			if(hf_debug_level > 0) send_ind_data(0, (uint8_t*)buf0, recv_bytes);
		}
		recv_bytes = hfuart_recv(huart1, buf1, 1000, 1000);
		if(recv_bytes > 0) {
			for(int i = 0; i < recv_bytes; i++) bl_uart_data_send(0, buf1[i]);
			if(hf_debug_level > 0) send_ind_data(1, (uint8_t*)buf1, recv_bytes);
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

// notification
static uint32_t bt_ntf_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len) {
	if(event==HFNET_BT_NTF_DATA_READY) u_printf("hf ble ntf recv %d bytes %d\n",len,buf_len);
	else if(event==HFNET_BT_NTF_DATA_ENABLE) u_printf("hf ble ntf connected!\n");
	else if(event==HFNET_BT_NTF_DATA_DISENABLE) u_printf("hf ble ntf disconnected!\n");
	return len;
}

// indication
static uint32_t bt_ind_recv_callback( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len) {
	if(event==HFNET_BT_IND_DATA_READY) u_printf("hf ble ind recv %d bytes %d\n",len,buf_len);
	else if(event==HFNET_BT_IND_DATA_ENABLE) u_printf("hf ble ind connected!\n");
	else if(event==HFNET_BT_IND_DATA_DISENABLE) u_printf("hf ble ind disconnected!\n");
	return len;
}

int USER_FUNC app_main (void) {	
    hfdbg_set_level(1);
    hfgpio_configure_pin(0x3830015,0x20000000); // To power on Air780e onboard chip 

	if(hfgpio_fmap_check(g_module_id) != 0) {
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

	// msleep(10000); // to manually start BLE scanner
	
	// if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS) u_printf("start uart fail!\r\n");
	hfthread_create(uart_bridge, "uart_bridge", 256, NULL, HFTHREAD_PRIORITIES_LOW, NULL,NULL);

	while(true) msleep(100);
	return 1;
}

