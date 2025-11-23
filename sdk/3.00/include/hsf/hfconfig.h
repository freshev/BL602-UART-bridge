/* hfconfig.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _HF_CONFIG_H_
#define _HF_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hfble.h>

#define CONFIG_HAVE_SETTIMEOFDAY 	1
#define CONFIG_HAVE_GETTIMEOFDAY 	1
//#define CONFIG_NO_STRUCT_TIMEZONE
#define SECRET_BUF_SIZE 3500


#define UPDATEFLAG 				2


#pragma pack(push)
#pragma pack(1)

typedef struct
{
	int8_t     updateflag; 		//update flag
	int8_t     validflag;		//valid flag
	int8_t	tmode_mode;
	int8_t     wmode_mode;
	//STA, 140 bytes
	uint8_t 	sta_ssid[33];	
	uint8_t 	sta_key[65];
	int8_t     wsauth;
	int8_t     wsencry;
	uint8_t	wslko;
	uint8_t	pmk_av;
	uint8_t	sta_padding[6];
	uint8_t	pmk[32];
	//AP, 144 bytes
	int8_t     wap_mode;
	int8_t     wap_channel;
	int8_t     waauth;
	int8_t     waencry;
	uint8_t	walk_led;
	uint8_t	max_sta_num;
	uint8_t	ap_enable_hide;
	uint8_t 	ap_ssid[33];
	uint8_t 	ap_key[65];
	uint8_t	ap_pmk_av;
	uint8_t	ap_pmk[32];
	uint8_t	ap_padding[6];
	//UART, 20 bytes
	int8_t     baudrate;
	int8_t     data_bits;
	int8_t     stop_bits;
	int8_t     parity;
	int8_t	ctsrts;
	
	int8_t     uart1_baudrate;
	int8_t     uart1_data_bits;
	int8_t     uart1_stop_bits;
	int8_t     uart1_parity;
	int8_t     uart1_debug;
	int8_t     uartfable;
	int8_t     fuartte_mode;
	uint16_t	uarttm;
	uint16_t	uartbuf;
	uint8_t	uart_padding[4];
	//NETP, 108 bytes
	int8_t     protocol;
	int8_t    	app_mode;
	uint8_t	maxsocket;
	char 	cipadd[101];
	uint16_t	pro_port;
	uint16_t   tcpto;
	//SOCKB, 112 bytes
	uint16_t	sockb_port;
	uint16_t	sockb_tcpto;
	int8_t	sockb_pro;
	char	 	sockb_cipadd[101];
	int8_t	tcpdis;
	int8_t	tcpdisb;
	
	uint16_t	udp_localporta;
	uint16_t	udp_localportb;
	//NETWORK, 108 bytes
	char		wann_ipaddr[16];
	char		wann_mask[16];
	char		wann_gateway[16];
	char     	lann_ipaddr[16];
	char	    	lann_mask[16];    
	uint8_t	wann_mode;
	uint8_t	network_padding[2];
	uint8_t	domain_name[21];
	uint32_t 	dns_addr;
	//UTILS, 124 bytes
	int8_t	echo;
	int8_t     rlden;
	uint8_t	debug_level;	
	char		wel_msg[11];
	uint8_t	event_onoff;
	uint8_t	noise_filter;
	uint8_t	wifi_switch;
	uint8_t	sta_dtim;
	uint8_t	utils_padding[40];
	uint8_t	dis_power_saving;
	int8_t	modechange;
	uint8_t	ps_interval;
	uint8_t	mid[21];
	uint8_t	aswd[21];
	uint8_t	cmdpw[21];
	//HTTPD, 36 bytes
	char		user_name[16];
	char		user_password[16];
	int8_t	web_switch;
	uint8_t	web_language;
	uint8_t	web_encode_format;
	uint8_t	httpd_padding;
	//DHCPD, 4 bytes
	int8_t	dhcpsw;
	uint8_t	dhcpd_addr_start;
	uint8_t	dhcpd_addr_end;
	uint8_t	dhcpd_padding;
	//UPDATE, 124 bytes
	char		update_url[101];
	char		update_file[21];
	uint8_t	update_padding[2];
	//NTP, 8 bytes
	uint8_t	ntp_time;
	uint8_t	ntp_enable;
	uint8_t	ntp_padding;
	int8_t	time_zone;
	uint32_t	ntpserver;
	//SMTLK, 16 bytes
	uint32_t	smtlk_sign;
	uint8_t	smtlk_mode;
	uint8_t	smtlk_protocol;
	uint8_t	smtlk_rtype;
	uint8_t	smtlk_ak_random;
	uint8_t	connect_flag;
	uint8_t	sta_channel;
	uint8_t	sta_bssid[6];
	//SMARTAPLINK, 44 bytes
	uint8_t	smartaplink_enable;
	uint8_t	smartaplink_padding;
	uint8_t	smartaplink_prefix[21];
	uint8_t	smartaplink_key[21];
	//NETPID, 24 bytes
	uint8_t	netpa_iden;
	char 	netpa_id[11];
	uint8_t	netpb_iden;
	char 	netpb_id[11];
	//NETPREG, 264 bytes
	uint8_t	netpa_regen;
	uint8_t	netpa_regtype;
	uint8_t	netpa_reg_padding;
	char		netpa_regdata[129];
	uint8_t	netpb_regen;
	uint8_t	netpb_regtype;
	uint8_t	netpb_reg_padding;
	char		netpb_regdata[129];
	//HEART, 124 bytes
	uint16_t	heart_netp_time;
	uint16_t	heart_sockb_time;
	uint16_t	heart_uart_time;
	char		heart_netp_data[39];
	char		heart_sockb_data[39];
	char		heart_uart_data[39];
	uint8_t	heart_padding;
	//HTTP, 236 bytes
	uint8_t	http_type;
	uint8_t	http_version;
	uint8_t	http_connect_type;
	uint8_t	http_recv_time;
	char		http_url[51];
	char		http_header[181];
	//MQTT, 224 bytes
	char		mqtt_username[33];
	char		mqtt_password[33];
	char 	mqtt_clientid[33];
	char		mqtt_pub_topic[61];
	char		mqtt_sub_topic[61];
	uint8_t	mqtt_qos;
	uint16_t	mqtt_heart_time;
	
	//BLE, 188 bytes
	uint16_t	conn_min;
	uint16_t	conn_max;
	uint16_t	conn_latency;
	uint16_t	supervisionTO;
	
	uint16_t	adver_min;
	uint16_t	adver_max;
	
	uint8_t	ble_name[27];
	uint8_t	ble_dms_name[27];
	uint8_t	ble_adver_data[27];
	
	uint8_t 	ble_adver_data_len;
	uint8_t 	ble_switch;
	uint8_t 	ble_uuid_server;
	uint8_t 	dms_type;
	uint8_t	ble_padding;
	
	uint8_t 	uuid_ntf_server[17];
	uint8_t 	uuid_ntf_read[17];
	uint8_t 	uuid_ntf_write[17];
	uint8_t 	uuid_ind_server[17];
	uint8_t 	uuid_ind_read[17];
	uint8_t 	uuid_ind_write[17];

	uint8_t	adver_type;
	uint8_t	adver_channel;
	uint8_t	ble_ind;
	uint8_t	smartconfiglink;

	uint8_t 	ble_conenable;
	uint8_t 	ble_conkey[BLE_CONKEYLEN];
	uint8_t 	ble_contimeout;
	uint8_t	netpc_iden;
	char 	netpc_id[11];
	uint8_t	netpc_idflag;
	
	uint8_t	ble_padding2[17];
	
	uint8_t mqtt_tls;
	uint8_t mqtt_padding[3];

	char		iot_productkey[12];
	char		iot_devicename[48];
	char		iot_devicesecret[48];
	char		iot_pubtopic[96];
	char		iot_subtopic[96];
	char		iot_mode;
	char		iot_padding[3];

	uint8_t  product_mode;
		
	int8_t  ctsrts_pin;

	char instance_flag;
	char instance_id[32];
	
	char	ntp_domain_server[33];
	int8_t	smk_find;

	uint32_t mcu_ota_size;
	uint8_t scan_ch14;
	char smp_flag;
	unsigned char key[16];
	uint8_t jump_change_user_web;
	uint8_t sta_login_web_flag;
	uint8_t	reserved1[41];
	uint8_t	validflag_magic;
	int8_t	validflag_end;		//valid flag
}HF_CONFIG_FILE;

typedef struct
{
	uint32_t magic_code;
	uint32_t crc32;
	uint32_t ver;
	uint32_t ota_flag;
	uint32_t run_mode;
	uint32_t upgrade_fw_addr;
	uint8_t  flash_test;
	uint8_t  reserved2;
	uint8_t  xmodem_upgrade_fw_flag;
	uint8_t  debug;
	uint8_t  rf_init;
	uint8_t  run_default_sw;
	uint8_t  run_rf_test_app;
	uint8_t  boot_wait_flag;
	int8_t    rf_table[48];
	uint8_t  reserved[48];
}HF_BOOT_CONFIG;

#pragma pack(pop)

extern int g_module_id;
extern HF_CONFIG_FILE  g_hf_config_file;

enum ENWAUTH
{
	WAUTH_OPEN = 0x00,
	WAUTH_SHARED,
	WAUTH_WPAPSK,
	WAUTH_WPA2PSK,
	WAUTH_WPAPSKWPA2PSK
};

enum ENWENCRY
{
	WENCRY_NONE = 0x00,
	WENCRY_WEP_A,
	WENCRY_WEP_H,
	WENCRY_TKIP,
	WENCRY_AES,
	WENCRY_TKIPAES,
	WENCRY_WEP
};

enum ENNETSETAPP
{
	NETSETAPP_SERVER = 0x00,
	NETSETAPP_CLIENT
};

enum ENNETSETPRO
{
	NETSETPRO_TCP = 0x00,
	NETSETPRO_UDP,
	NETSETPRO_HTTPC,
	NETSETPRO_MQTT,
	NETSETPRO_ALIIOT,
	NETSETPRO_IGMP,
	NETSETPRO_TCP_TLS,
	NETSETPRO_HTTPSC
};

enum ENSOCKBPRO
{
	SOCKBPRO_NONE	 = 0x00,
	SOCKBPRO_TCP,
	SOCKBPRO_UDP,
	SOCKBPRO_UDPS,
	SOCKBPRO_IGMP
};

typedef enum ENBAUDRATE
{
	BAUDRATE_50 = 0x00,
	BAUDRATE_75,
	BAUDRATE_110,
	BAUDRATE_134,
	BAUDRATE_150,
	BAUDRATE_200,
	BAUDRATE_300,
	BAUDRATE_600,
	BAUDRATE_1200,
	BAUDRATE_1800,
	BAUDRATE_2400,
	BAUDRATE_4800,
	BAUDRATE_9600,
	BAUDRATE_19200,
	BAUDRATE_38400,
	BAUDRATE_57600,
	BAUDRATE_115200,
	BAUDRATE_230400,
	BAUDRATE_380400,
	BAUDRATE_460800,
	BAUDRATE_921600,
	BAUDRATE_56000,
	BAUDRATE_1000000,
	BAUDRATE_1500000,
	BAUDRATE_2000000,
	BAUDRATE_2500000,
	BAUDRATE_3000000,
	BAUDRATE_3500000,
	BAUDRATE_4000000
}ENBAUDRATE_E;

typedef enum ENCOMBITS
{
	COMBITS_5 = 0x00,
	COMBITS_6,
	COMBITS_7,
	COMBITS_8
}ENCOMBITS_E;

typedef enum ENCOMPARITY
{
	COMPARITY_NONE = 0x00,
	COMPARITY_ODD,
	COMPARITY_EVEN,
	COMPARITY_MARK,
	COMPARITY_SPACE
}ENCOMPARITY_E;

typedef enum ENCOMSTOPBITS
{
	
	COMSTOPBITS_1 = 0x00,
	COMSTOPBITS_1P5,
	COMSTOPBITS_2
}ENCOMSTOPBITS_E;

typedef enum ENCOMUARTCTL
{
	COMUARTFC = 0x00,
	COMUARTNFC
}ENCOMUARTCTL_E;

typedef enum ENCOMUARTCTLPIN
{
	COMUARTFCPIN_DEF = 0x00,
	COMUARTFCPIN_REV
}ENCOMUARTCTLPIN_E;

enum ENCOMWANNMODE
{
	COMWANNDHCP = 0x00,
	COMWANNSTATIC
};

enum ENUARTFABLE
{
	HFUARTFDISABLE = 0x00,
	HFUARTFENABLE,
	HFUARTHFFORMAT,
};

enum ENUARTFMODE
{
	M2M_UARTTE_FAST = 0x00,
	M2M_UARTTE_NORMAL
};

enum CONFIG_WAMOD
{
	CONFIG_WAMOD_11B = 0x00,
	CONFIG_WAMOD_11BG,
	CONFIG_WAMOD_11BGN
};

enum CONFIG_WMODE
{
	CONFIG_WMODE_AP = 0x00,
	CONFIG_WMODE_STA,
	CONFIG_WMODE_APSTA
};

enum ENWORKTMODE
{
	M2M_STATE_RUN_THROUGH = 0x00,
	M2M_STATE_RUN_CMD,
	M2M_STATE_RUN_GPIO,
	M2M_STATE_RUN_PWM
};

enum CONFIG_PSLP
{
	CONFIG_PSLP_NORMAL = 0x00,
	CONFIG_PSLP_STANDBY,
	CONFIG_PSLP_DEEPSLEEP
};

enum CONFIG_PRLDEN
{
	CONFIG_PRLDEN_DISABLE = 0x00,
	CONFIG_PRLDEN_ENABLE
};

enum CONFIG_WADHCP
{
	CONFIG_WADHCP_DISABLE = 0x00,
	CONFIG_WADHCP_ENABLE
};

enum CONFIG_WEBLANGUAGE
{
	CONFIG_WEBLAN_EN = 0x00,
	CONFIG_WEBLAN_CN
};

enum CONFIG_DISPS
{	
	CONFIG_EN_PS = 0x00,
	CONFIG_DIS_PS
};

enum CONFIG_BLE
{
	CONFIG_BLE_ON	= 0x00,
	CONFIG_BLE_OFF
};

enum CONFIG_BLE_IND //ble link light
{
	CONFIG_BLE_IND_OFF	= 0x00,
	CONFIG_BLE_IND_ON
};

enum CONFIG_REG_TYPE
{
	CONFIG_REG_TYPE_LINK	= 0x00,
	CONFIG_REG_TYPE_DATA,
	CONFIG_REG_TYPE_BOTH
};

#define HF_CONFIG_OTA_FLAG_REDAY				(0x0A0A55A0)
#define HF_CONFIG_OTA_FLAG_OK					(0x0505AA50)
#define HF_BOOT_CONFIG_MAGIC_CODE			(0x48464254)
#define HF_CONFIG_OTA_FLAG_FAIL				(0x5A5A5A00)

#define HF_BOOT_RUN_MODE_NORMAL				(0)
#define HF_BOOT_RUN_MODE_AUTO_UPGRADE		(0xA5010202)
#define HF_BOOT_RUN_MODE_DEBUG				(0xA5010203)

#define HF_DEFAULT_MAC_ADDR "ACCF23FF8888"

                        
void HSF_IAPI hfconfig_init(void);

int HSF_IAPI hfconfig_is_valid(void);

void HSF_IAPI hfconfig_dump(unsigned char *data, int len);

int HSF_IAPI hfconfig_protect_check(void);

int HSF_IAPI hfconfig_fseting_save_ex(HF_CONFIG_FILE *file);

int HSF_IAPI hfconfig_fseting_save(void);

void HSF_IAPI hfconfig_file_reload(void);

void HSF_IAPI hfconfig_enable_save(int enable);

void HSF_IAPI hfconfig_file_save(void);

int HSF_IAPI hfboot_config_set_ota_ready(uint32_t ota_file_addr);

int HSF_IAPI hfboot_config_set_ota_flags(uint32_t flags);

int HSF_IAPI hfboot_config_set_ota_xmodem(uint8_t flag);

int HSF_IAPI hfboot_config_set_run_default_sw(uint8_t flag);

uint8_t HSF_IAPI hfboot_config_get_run_default_sw(void);

int HSF_IAPI hfboot_config_set_flash_test(uint8_t flag);

int HSF_IAPI hfboot_config_get_flash_test(void);

void HSF_IAPI hfboot_update_run_mode(uint32_t mode);

void HSF_IAPI hfboot_set_rf_test_mode(uint8_t mode);

uint8_t HSF_IAPI hfboot_get_rf_test_mode(void);

void HSF_IAPI hfboot_set_boot_wait_flag(uint8_t flag);

uint8_t HSF_IAPI hfboot_get_boot_wait_flag(void);

int HSF_IAPI hfboot_config_set_rf_table(int8_t table[48]);

int HSF_IAPI hfboot_config_get_rf_table(int8_t table[48]);

void HSF_IAPI hfboot_update_run_mode(uint32_t mode);

void HSF_IAPI hfboot_set_debug(uint8_t on);

int HSF_IAPI hfconfig_uart_baud_en2num(int *num,int baudrate);

int HSF_IAPI hfconfig_uart_baud_num2en(int num, int *en);


/**
 * @brief check High-flying config data is valid.
 *
 * @param[in] None
 * @return[out] 0-invalid, 1-valid
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_file_check_is_valid(void);

/**
 * @brief update valid flag in High-flying config data.
 *
 * @param[in] None
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_file_update_validflag(void);

/**
 * @brief read High-flying config data.
 *
 * @param[in] offset: the offset of config data
 *			 data: a pointer to data
 *			 len: the length, in bytes, of the data pointed to store data
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_file_data_read(int offset, unsigned char *data, int len);

 /**
 * @brief write High-flying config data.
 *
 * @param[in] offset: the offset of config data
 *			 data: a pointer to data
 *			 len: the length, in bytes, of the data pointed to write
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_file_data_write(int offset, unsigned char *data, int len);

 /**
 * @brief write UID to flash.
 *
 * @param[in] uid: a pointer to uid
 *			 uid_len: the length, in bytes, max is 128 bytes
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note UID and MAC are store in the same flash space, modify Mac will lose UID.
 */
int HSF_API hfconfig_write_user_id(unsigned char *uid, int uid_len);
 
 /**
 * @brief read UID from flash.
 *
 * @param[in] uid: a pointer to uid
 *			 max_len: the max length of the uid buffer
 * @return[out] the length of read success, <=0 is failed
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_read_user_id(unsigned char *uid, int max_len);

 /**
 * @brief get user RF table.
 *
 * @param[in] value_0x8A: a unsigned short array for register 0x8A
 *			 value_0x120: a int type number for register 0x120
 *			 value_0x11F: a int type number for register 0x11F
 *			 value_0xDA: a int type number for register 0xDA
 *			 offset: a unsigned char type number
 * @return[out] user RF table version, must >10, <=0 is not use user RF table
 * @see None.
 * @note None.
 */
int HSF_API hfconfig_get_user_rf_table(int8_t table[48]);

	
#ifdef __cplusplus
}
#endif

#endif

