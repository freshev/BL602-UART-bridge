 /* ssltest.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <hsf.h>
#include <stdlib.h>
#include <string.h>

#define USE_MBEDTLS_LIB_AND_MBEDTLS_API 0
// #define USE_MBEDTLS_LIB_AND_CYASSL_API 1
// #define USE_CYASSL_LIB_AND_CYASSL_API 2
// #define	MBEDTLS_TEST_CLIENT
#define	MBEDTLS_TEST_SERVER	

#if defined(USE_MBEDTLS_LIB_AND_MBEDTLS_API) || defined(USE_MBEDTLS_LIB_AND_CYASSL_API)
#include "mbedtls_compatible_alios.h"
// #include "mbedtls_compatible_cyassl.h"
#elif defined USE_CYASSL_LIB_AND_CYASSL_API
//#include <cyassl/openssl/ssl.h>
//#include <cyassl/internal.h>
//#include <cyassl/cyassl_config.h>
#endif

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

#ifdef	MBEDTLS_TEST_CLIENT
static const char root_ca[] = 
{
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDVzCCAj+gAwIBAgIJAIU7KuY1rC5WMA0GCSqGSIb3DQEBCwUAMEIxCzAJBgNV\r\n"
"BAYTAlhYMRUwEwYDVQQHDAxEZWZhdWx0IENpdHkxHDAaBgNVBAoME0RlZmF1bHQg\r\n"
"Q29tcGFueSBMdGQwHhcNMjEwMTEzMDg0OTE1WhcNMzEwMTExMDg0OTE1WjBCMQsw\r\n"
"CQYDVQQGEwJYWDEVMBMGA1UEBwwMRGVmYXVsdCBDaXR5MRwwGgYDVQQKDBNEZWZh\r\n"
"dWx0IENvbXBhbnkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA\r\n"
"xTwUG4pO8QvHOdxa3OP8p/EcY54YbiFpVOTw3wZb60V7COfp4et/mmB267oL5PAv\r\n"
"Lps6Xpf7bL+FQfdP1lOirpa1YC+8JCuvRhnlmJlUk9ILTldZQNsW5zkrLfviiCFy\r\n"
"8quFObC/86B4JzI1SfwzraThtWdVw7twDmLhvuUgjc2Mu7ASTsrAwVRubhMzV4Rl\r\n"
"J7o10r60JmlaeYDRpyHRTTHT05OyRz8POxS0wU1MLh5NjGP4eXp/MRSYayNFLrZH\r\n"
"cdQPJGmAhcGfpX1XsI70gWHtSisXxrsiU+IVJd3vebbL+jbDzwcM03olnrQ2lLRW\r\n"
"WgxwVLB5QskU7L9amnFNdQIDAQABo1AwTjAdBgNVHQ4EFgQUwCe4RUPPVHbLogzT\r\n"
"C1K1kkQAjyowHwYDVR0jBBgwFoAUwCe4RUPPVHbLogzTC1K1kkQAjyowDAYDVR0T\r\n"
"BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAHgzSL2trnwiDgJI3ABAhlwTFsQdn\r\n"
"ZpnuEqm5tnmWrdf4cmaNsUg9cVYSXeBz3iclJ38Vcy9K4aYbo4wY/LZlNbM0YQlX\r\n"
"i1a7kRCrk6+PzeE2v+cfYVzJwJ/QZ2hf1c6XJmVn2DaOeTP1uPe3jf6E0fq5ikDK\r\n"
"4PwyIqNTdqQiiOkL0yPs/unonfcQbACAq6+NNQ4hrjbJLYAevYXd+pblxQRklIT9\r\n"
"/XmgYA1ERLtyvAb7fM3hbzcJCNaj9kPHyQa7q4QuyXnNL1Y8xfaVSSKeOPw5N38G\r\n"
"kikJfeiVOqy9FEpEP9I+b4EEP6KiQxfHdloZznIa2tXBKRSyngU02JlmMQ==\r\n"
"-----END CERTIFICATE-----\r\n"
};

static const char device_cert[] = 
{
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDDzCCAfcCCQDOyUqSvYSh8zANBgkqhkiG9w0BAQsFADBCMQswCQYDVQQGEwJY\r\n"
"WDEVMBMGA1UEBwwMRGVmYXVsdCBDaXR5MRwwGgYDVQQKDBNEZWZhdWx0IENvbXBh\r\n"
"bnkgTHRkMB4XDTIxMDExMzA5NTAwMloXDTMxMDExMTA5NTAwMlowUTELMAkGA1UE\r\n"
"BhMCQ04xEDAOBgNVBAgMB0JlaWppbmcxEDAOBgNVBAcMB0JlaWppbmcxDTALBgNV\r\n"
"BAoMBEVNUVgxDzANBgNVBAMMBmNsaWVudDCCASIwDQYJKoZIhvcNAQEBBQADggEP\r\n"
"ADCCAQoCggEBALW8vVLPiXW5K6OavSUQbdTznXtHUElDdB4ZjIpwUOdVcj+gnUtF\r\n"
"5uMTtgqrILrUgDkr+1rTRheVo73SowkRIK8LB98P9yXCEXjVH+9H6a7PSkoj26q9\r\n"
"V3DX9LA6YkDlhrm7DVZANZLZ3/V22TYVHSnsgoC8nADp3U3aszKmytECrVDqOrax\r\n"
"hjhuT9tNrpi5x1YKWiPbP7hlPsXNe9DGHGDON43gAdoYvIBKw3lsIf5yfD+gqweP\r\n"
"NasOpgUcNiQyfIofLKgyQk7Ov/fuireOyieMGLiinktmRQv+t6LC+qk2y4ADDWb8\r\n"
"R7X8FNDheo1C2wXDC3lu4lS5aksfowtxzHkCAwEAATANBgkqhkiG9w0BAQsFAAOC\r\n"
"AQEAP5LUpVXw7O2pm80diQMp1oxz8vshTjj3M8LWI1SBCAQTpE3CUHCo+eODMi0A\r\n"
"3kYpxvLbJpRKZDoVmhM9rMd+8h5/9ZRm8j3dDWq9EBZulGaHm9NuGTq6hZPJi8ci\r\n"
"GcKMyZQqYntCUXJRwj43q5sOl5Y52JJLtgQR/D9vhpCoH5A3vkEQjPdi+BeGjznJ\r\n"
"H3Ba/x4X7bRvW67GOgONiHF/xKMZiRMzhlWk86bW2FcoFOF1YI9WR40zM1g4dVkt\r\n"
"AvujQpDUpyTUPsijPN3ZMU6cwXXoKwtpzr6ENYI6JqblrjubkLA1dJ7Pjyflpnlu\r\n"
"4cbOHUDO29CCeDEbWEbZpeciWg==\r\n"
"-----END CERTIFICATE-----\r\n"
};

static const char private_key[] = 
{
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEowIBAAKCAQEAtby9Us+Jdbkro5q9JRBt1POde0dQSUN0HhmMinBQ51VyP6Cd\r\n"
"S0Xm4xO2CqsgutSAOSv7WtNGF5WjvdKjCREgrwsH3w/3JcIReNUf70fprs9KSiPb\r\n"
"qr1XcNf0sDpiQOWGubsNVkA1ktnf9XbZNhUdKeyCgLycAOndTdqzMqbK0QKtUOo6\r\n"
"trGGOG5P202umLnHVgpaI9s/uGU+xc170MYcYM43jeAB2hi8gErDeWwh/nJ8P6Cr\r\n"
"B481qw6mBRw2JDJ8ih8sqDJCTs6/9+6Kt47KJ4wYuKKeS2ZFC/63osL6qTbLgAMN\r\n"
"ZvxHtfwU0OF6jULbBcMLeW7iVLlqSx+jC3HMeQIDAQABAoIBAGOUhZCIk2NkERtW\r\n"
"QGm8tNHIovPXwZBDW67ahP2eSVZYpX9jvIxwQvEN7eOunQKCSbgJ93Ju7asinVP3\r\n"
"xMnFDsmbG7cIAn439mblMNhl6Q+WGbjCKS1HDlCQpEyj0Q6KNeYzLj2idTiAFY1k\r\n"
"j+RocVB1fZSYxEpj2pU8TpBkgCFBjvt2dk2TsyLVgs2LVvTk4taXzEIpg/2g7hDb\r\n"
"c/VC0y4WG5Ed8LCf6JenX7u3KeM1bCYswg02JXGTLpIPRpk4MMyhiX63hwyw9AAH\r\n"
"y7SqsBOC8mHSyH9D5I4Xh5eOAwUHxacaIpttshZB7FVysWIBwn5UR6Vm5SZy9HFv\r\n"
"us0/A7kCgYEA61SlEvo/w/a08jmSMfoaEnPwfgHs+ECHw1wTaqRsDcjgDquojxvn\r\n"
"1RGP/Rxr1htppnOlI/ytZHbSnOiEJlxdpAE4fJvV5rl0iOvatCvGVZ2W33z9EKX7\r\n"
"6NlxxEheIUaaEMsSdhmY8U6QnFVyRxiRZTV/4eAEjA1WJVDl8K4zAW8CgYEAxbMP\r\n"
"WQLSOPMdqH4Hl3rSzwWG+8kI2tCrvRJt6PYCbM2PKXlIPs/POp21odOtYCFf9I3M\r\n"
"KUhyN1lxbiX6DSAGZEx89vcRBVYE2Sbw1j5J6U81TJb1xAohWM3gDDYKCWX1CaV4\r\n"
"toQQlpuEmmCqQEwUIqWRnAVbms6NNbCyQnKBTJcCgYBxoYyXzkhN+mlC8PObuDUw\r\n"
"pdUBMzLWaGpltacWflBCk7VEwDSC7amS44kQYdHcL55jJkIeT1r2QL3P0CJHV6BL\r\n"
"md9JpAG0B+ayWphfGSgKnS6FuZeEm3E47Q4XBg6VqL6pzzSZ3CBSnGoNYuDsXXuP\r\n"
"UDbwvTfU3He1SwvMnIC6dwKBgQC3A70YfHkZyU3SVeE3RLd0eDxuR7uPvQ7O+AmR\r\n"
"WHQEPwLhtOnBY+UF8UtcZLWiQSMwJDg0m2FIhd9wxW1Gyze/j+M7SJqUIv5X/CmF\r\n"
"W6JWfkHsBe+7rFkUeXmINFp0OtNtO6aU54rnsU4/D29sGEGnlThHg9o6ZC3q3wkW\r\n"
"ZCP4PwKBgAkHGTZHCBOJXdQV+hsmFQ7ltmsk0vaisjoEYHSCAQNX6M29Nw5NPSlv\r\n"
"fEBeQkZzh8ATWZQVyR4nhdYuJ0s6QKCdxFicAe8YYG54SWV442NrmlcTRsiaLp00\r\n"
"U93I4ChZZWQjAcjfSkDFsLpbLc3Nk7RJG45r4rIHWTyzsh4HA9+3\r\n"
"-----END RSA PRIVATE KEY-----\r\n"
};
#else

#define HttpRspDataFormat      "HTTP/1.1 200 OK\r\n"\
"Content-type: text/html\r\n"\
"\r\n"\
"<html><body>Hello (TLS) World, System RunTime!</body></html>"

static const char* root_ca =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDtDCCApygAwIBAgIBATANBgkqhkiG9w0BAQsFADByMQswCQYDVQQGEwJKUDEO\r\n"
"MAwGA1UECAwFQWljaGkxGzAZBgNVBAoMElJpbm5haSBDb3Jwb3JhdGlvbjEZMBcG\r\n"
"A1UECwwQUiZEIEhlYWRxdWFydGVyczEbMBkGA1UEAwwSUmlubmFpIENvcnBvcmF0\r\n"
"aW9uMCAXDTIxMTEyNTA0NTEyMFoYDzIwNTExMTE4MDQ1MTIwWjByMQswCQYDVQQG\r\n"
"EwJKUDEOMAwGA1UECAwFQWljaGkxGzAZBgNVBAoMElJpbm5haSBDb3Jwb3JhdGlv\r\n"
"bjEZMBcGA1UECwwQUiZEIEhlYWRxdWFydGVyczEbMBkGA1UEAwwSUmlubmFpIENv\r\n"
"cnBvcmF0aW9uMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA19dtCxTt\r\n"
"OiFeZ3uLWQlbWJ5OtggxA46qGdLMw4ZeFyNomq/Cg1klTMiINkdSt9xklgLk9QIQ\r\n"
"sU3Rhc5/bpfWUGeT+M51DCDSasad5HFpqaX5FgD7MCgeW9Vc/5DTBwbBEfvJCB8V\r\n"
"UoVVsC4zh6UOofQ9J6vM5bQpTqxmwtdViTUIbwhxYBAR6+I1s+sNAXhXRjlARacP\r\n"
"dKplALyKtzL8fDwwW0oM5duoUiXt9wSBcbMZ9RJm4nZbARCe6K5zvzrKPnxX5upw\r\n"
"+z+GD42is4aGfwfXaBLKPdUBArGUr15EBNCIQVcnJ1wg6ubP6W5rJOcakZ/U6L9G\r\n"
"bbl0x5lZZQgXZQIDAQABo1MwUTAdBgNVHQ4EFgQUdNOgxYAN3Pgq8RNAl2OpY/2M\r\n"
"0DAwHwYDVR0jBBgwFoAUdNOgxYAN3Pgq8RNAl2OpY/2M0DAwDwYDVR0TAQH/BAUw\r\n"
"AwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAAnpPQYpG3BwNAeb720N5uZUC7e1Gyjjd\r\n"
"gSQzjcWFsWLatdU2uWMNzwztMN+smF96HkCEWtARBn9dlhBBCnQEbe3YdNsvB+5t\r\n"
"uKaC/gKDQ+kEtbx9fACDJKIXSVKRIdKZ8cEMumeE3CDJzq7oktL53wcMdIGwbTE2\r\n"
"8MB34A7h3ApJGABL63G1oBQSOBnPDiQVTQnGS5obI69kM97R2giEVMWT/B3GhFTJ\r\n"
"jp/OEYpnVPU/T4xTo6laVk7WZvGP5udp3KvaWpzGHiq2UuF3baTRW1f36qYnbldO\r\n"
"0MsCIYT4IZOZ2vlO7gK/tt9Gfi1iHt8KP9B52fQR7NxB4YBvgJGeiA==\r\n"
"-----END CERTIFICATE-----\r\n";

static const char *server_crt = 
"-----BEGIN CERTIFICATE-----\r\n"
"MIID1TCCAr2gAwIBAgIBAjANBgkqhkiG9w0BAQsFADByMQswCQYDVQQGEwJKUDEO\r\n"
"MAwGA1UECAwFQWljaGkxGzAZBgNVBAoMElJpbm5haSBDb3Jwb3JhdGlvbjEZMBcG\r\n"
"A1UECwwQUiZEIEhlYWRxdWFydGVyczEbMBkGA1UEAwwSUmlubmFpIENvcnBvcmF0\r\n"
"aW9uMCAXDTIxMTEyNTA0NTczNFoYDzIwNTExMTE4MDQ1NzM0WjBrMQswCQYDVQQG\r\n"
"EwJKUDEOMAwGA1UECAwFQWljaGkxGzAZBgNVBAoMElJpbm5haSBDb3Jwb3JhdGlv\r\n"
"bjEZMBcGA1UECwwQUiZEIEhlYWRxdWFydGVyczEUMBIGA1UEAwwLcmlubmFpX2F1\r\n"
"dGgwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCaMQDVvNaV0lvT5Zv4\r\n"
"URgsVB0DUh7E+DZkiFRDPMaMKqtlCMjceNsB30uK6+EInKgqOJd4bknP1PM0FGfh\r\n"
"ySwV1uetaTTpyE1uDWChsUCC6UPKOSecezgJtD9cGUWxtVDPO+w8jQU8t7Zy3n5e\r\n"
"Z2aeH/xzb60sbRSslfk9RMql3N4Eg/gL9lFCVCfUGlg7RxA6fpRbwCP2A8Fm7Hjc\r\n"
"5nON7nNJi6rjbWv6e+3wZ5hS5SxHDg5I61FW5DuWnnasugILqP9FaI3G84MDWJ1l\r\n"
"aQ9W9MVOYUc7zrSjk6m0btlqW2wom37whL0yT6U0fOQHYcWc9uYxx1G0vsvklCUF\r\n"
"F0rnAgMBAAGjezB5MAkGA1UdEwQCMAAwLAYJYIZIAYb4QgENBB8WHU9wZW5TU0wg\r\n"
"R2VuZXJhdGVkIENlcnRpZmljYXRlMB0GA1UdDgQWBBTMRavv6U9ci1rMq3+7v9uk\r\n"
"TWa8BDAfBgNVHSMEGDAWgBR006DFgA3c+CrxE0CXY6lj/YzQMDANBgkqhkiG9w0B\r\n"
"AQsFAAOCAQEAyY93VocKvS74WlQ8FLLkgoK6lcOFjWaFTocpBpMZ/tsZVFspYQN/\r\n"
"1+58D8C/ritDwo/cBbPY5jirrgOj3/LuHxoCa60Pg8jFjZwbzA5P1GeJKBUXgSfg\r\n"
"34TrTiiP95ZUakTmytWJmHDH8tEqiH1se3OInuHgbjAFZJ+u1VpsKq2Q60GQ2deB\r\n"
"dWE8yFRlJBNUk9Rg4VCURUNOoZ/HZ9B2NDPlMhyKZ27swK54agIPKRj3gPf5VNZv\r\n"
"LtSkfm5ayIScBSSFae8l+If3xM5Ctv6FeztMPMjHU2suwcRqmI4opua3bQYayksM\r\n"
"NL27374bBJ2lF0GeaUHzVls2prHuJIYUTw==\r\n"
"-----END CERTIFICATE-----\r\n";

static const char *server_key = 
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEpAIBAAKCAQEAmjEA1bzWldJb0+Wb+FEYLFQdA1IexPg2ZIhUQzzGjCqrZQjI\r\n"
"3HjbAd9LiuvhCJyoKjiXeG5Jz9TzNBRn4cksFdbnrWk06chNbg1gobFAgulDyjkn\r\n"
"nHs4CbQ/XBlFsbVQzzvsPI0FPLe2ct5+Xmdmnh/8c2+tLG0UrJX5PUTKpdzeBIP4\r\n"
"C/ZRQlQn1BpYO0cQOn6UW8Aj9gPBZux43OZzje5zSYuq421r+nvt8GeYUuUsRw4O\r\n"
"SOtRVuQ7lp52rLoCC6j/RWiNxvODA1idZWkPVvTFTmFHO860o5OptG7ZaltsKJt+\r\n"
"8IS9Mk+lNHzkB2HFnPbmMcdRtL7L5JQlBRdK5wIDAQABAoIBAQCAK43DHcbOIV9d\r\n"
"o3ZkEpzidETttryHBMDKDpzki0eLyghQ4t18jyWVx9SWtP6JVxdeiU43uI24qg5D\r\n"
"01aK09vGh65rcpGeZ3cdrRcPMTUr3NUR6zKnG7H4NxGX8BYD43E54li7+IlK8HdD\r\n"
"wvkOZith87q5BjLQRBg0YjIdIOrGtaiMW2T/hQ5uYmLS/3Jf/o48jcxPMXjfpYBB\r\n"
"T2DKl0BstGihGPNnv83z8x8gmAC3Wz97sWvWXhpOk+I75gBJW6TZdVR7oba2HQPN\r\n"
"8xnvew9DQDkUUN6oIL7z+P7ij2iu+2sdrjQQVcMimKxGcdkOmaIwj++lS/E5Uwg3\r\n"
"L+TxRZopAoGBAM0F5RJRWVgNjM5andmx3tmb68m9/g2xpSs2jxHghZW8XhekD6vR\r\n"
"Ka6qDWJ3X+59XIEqQ8RZau8H49IknGCfNa2EQ1s4/BBI17EL9pBxBA6IlOpj73uI\r\n"
"01iA1GLiXyvNt6iQlCBOCRc5SFYVFSuNVJYXJviKN445tZgbH3nawGMVAoGBAMCH\r\n"
"lH3aVS3IpnfPnM8j/RV63SEWOomP6GkvbnIn9EMyAJaRVNI7keJpO+fRlhmwLz4o\r\n"
"B/y6aiFHBq+uWsTnoJmLx9OqgBMyYvUgS4JJepVOGhkj9p1pZ3S3/reIn/6/OIqN\r\n"
"26/TUqs4WgG5zXFIA/sXq8pPfsczfmAFD22CvSULAoGBAJgYKWm/Y5JI6w4idzuK\r\n"
"EpJIc1EEWzX5dVhrbxOKBk+goATVtrJ1xoBGsws7F7Wq1jcUDZXZ59RPfBjnBANB\r\n"
"2OZSWk2QJp5GC4zSHSXmUWYeuKpxXLW+OVtMp0J8QLIUOI0aRGj6uw+5dQo3Na9L\r\n"
"d1ao8kYq8y/Va/vdEyqot1RJAoGAOqAOQ1RcY5iZuBnr8ddPlV7YPt757DF5362l\r\n"
"v/USl/N94ltWrL2e6oaIy0oynpfbit29sONCtedezdgVo6e0a4z4yCc+4JmTMHkp\r\n"
"BP9C6Hvjzov46G3UJuJwGYrszTGFEguoPZ3nqmN6ZNQjDr+TFr5afTw/qoCvlqVz\r\n"
"0TDiT4kCgYAB1rwLto62Ts08qjFviZgnd4JUOU0F5P7R0q/QTUBp46ZUxzf47lNB\r\n"
"i2RegYzFwdCJPBHdPpObgysS1ZWmDTwAZA3LwoN8YRDiTEcAao5E+FfQeY+L/plE\r\n"
"mzTLzhFoKUH2qPoNHMlHQLwgYXymc9kgSz2pvVFvUmfrkGh6fcHlJQ==\r\n"
"-----END RSA PRIVATE KEY-----\r\n";
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


static USER_FUNC int tcp_connect_ssl_server(char *url)
{
	int fd;	
	struct sockaddr_in addr;
	unsigned short port = 2001;
	char *addrp=url;
	char *portp = NULL;
	
	if((memcmp(url, "HTTPS://", 8)==0)||(memcmp(url, "https://", 8)==0))
		addrp= (char *)(url+8);
	portp= strstr(addrp, ":");
	if(portp)
	{
		port = atoi(portp+1);
		*portp = '\0';
	}
	
	ip_addr_t dest_addr;
	if(hfnet_is_ipaddress((const char *)(addrp)) !=1 )
	{
		if(hfnet_gethostbyname((const char *)(addrp), &dest_addr) !=HF_SUCCESS)
			return -1;
	}
	else
		inet_aton((char *)(addrp), (ip_addr_t *) &dest_addr);
	
	memset((char*)&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr=dest_addr.addr;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0)
		return -1;
	
	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr))< 0)
	{
		close(fd);
		return -1;
	}
	
	return fd;
}

char ssl_url[101];
char ssl_recvbuf[1000];
#if defined(USE_MBEDTLS_LIB_AND_CYASSL_API) || defined(USE_CYASSL_LIB_AND_CYASSL_API)
static USER_FUNC void my_ssl_test(char *url, char *sendbuf, int sendnum)//a SSL test
{
	InitMemoryTracker();//for debug, it can show how many memory used in SSL
	CyaSSL_Debugging_ON();//for debug

	CyaSSL_Init();
	CYASSL_METHOD*  method  = 0;
	CYASSL_CTX*     ctx     = 0;
	CYASSL*         ssl     = 0;
	int sockfd=-1;
	
	method=CyaTLSv1_2_client_method();
	if (method == NULL)
		HF_Debug(DEBUG_LEVEL_LOW, "unable to get method");

	ctx = CyaSSL_CTX_new(method);
	if (ctx == NULL)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "unable to get ctx");
		return;
	}

	CyaSSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, 0);//disable verify certificates
	
	ssl = CyaSSL_new(ctx);
	if (ssl == NULL)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "unable to get SSL object");
		goto FREE_CTX;
	}

	sockfd=tcp_connect_ssl_server(url);
	if(sockfd<0)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "create socket error");
		goto FREE_SSL;
	}
	
	CyaSSL_set_fd(ssl, sockfd);
	if (CyaSSL_connect(ssl) != SSL_SUCCESS)
 	{
		int  err = CyaSSL_get_error(ssl, 0);
		char buffer[80];
		HF_Debug(DEBUG_LEVEL_LOW, "err = %d, %s\n", err,CyaSSL_ERR_error_string(err, buffer));
		HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed");
	}
	else
		HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect successed ----------------------------------------\n");

	if (CyaSSL_write(ssl, sendbuf, sendnum) != sendnum)
       	HF_Debug(DEBUG_LEVEL_LOW,"SSL_write failed");

	int recvlen;
	recvlen = CyaSSL_read(ssl, ssl_recvbuf, sizeof(ssl_recvbuf)-1);
	if (recvlen > 0)
	{
		HF_Debug(DEBUG_LEVEL_LOW,"Server response: recv start ----------------------------------------\n");
		CyaSSL_Debugging_OFF();
		hfuart_send(HFUART0, ssl_recvbuf, recvlen,1000);
		
		while (1) 
		{
			recvlen = CyaSSL_read(ssl, ssl_recvbuf, sizeof(ssl_recvbuf)-1);
			if (recvlen > 0) 
				hfuart_send(HFUART0, ssl_recvbuf, recvlen,1000);
			else
				break;
		}
		
		CyaSSL_Debugging_ON();
		HF_Debug(DEBUG_LEVEL_LOW,"\n---------------------------------------- recv End!\n");	
	}
	else if (recvlen < 0) 
	{
		int readErr = CyaSSL_get_error(ssl, 0);
		if (readErr != SSL_ERROR_WANT_READ)
			HF_Debug(DEBUG_LEVEL_LOW, "CyaSSL_read failed");
	}

FREE_SSL:
	CyaSSL_shutdown(ssl);
	CyaSSL_free(ssl);
FREE_CTX:
	CyaSSL_CTX_free(ctx);
	close(sockfd);
	
	CyaSSL_Debugging_OFF();//close debug
	ShowMemoryTracker();//peek into how memory was used
}

#elif defined(USE_MBEDTLS_LIB_AND_MBEDTLS_API)
static USER_FUNC void my_ssl_test(char *url, char *sendbuf, int sendnum)//a SSL test
{
#ifdef	MBEDTLS_TEST_CLIENT
	void *ssl = NULL;
	int sockfd=-1;
	
	sockfd=tcp_connect_ssl_server(url);
	if(sockfd<0)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "create socket error");
		goto FREE_SSL;
	}
	else
		u_printf("scoket create succes...\n");

	ssl = app_mbedtls_ssl_connect((void *)sockfd, root_ca,sizeof(root_ca),device_cert,sizeof(device_cert),private_key,sizeof(private_key));
	if (ssl == NULL)
 	{
		HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed");
		goto FREE_SSL;
	}
	else
		HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect successed ----------------------------------------\n");

FREE_SSL:
	app_mbedtls_ssl_close(ssl);
	close(sockfd);
#endif
}
#endif

static USER_FUNC int set_ssl_addr(pat_session_t s,int argc,char *argv[],char *rsp,int len)
{
	if( 0 == argc )
	{
		hffile_userbin_read(0, ssl_url, 100);	
		sprintf(rsp, "=%s", ssl_url);
		return 0;
	}
	else if( 1 == argc )
	{
		if((strlen(argv[0]) > 1)&&(strlen(argv[0]) < 100))
		{
			hffile_userbin_write(0, argv[0], strlen(argv[0])+1);
			return 0;
		}
		else
			return -1;
	}
	else
		return -1;
}

const hfat_cmd_t user_define_at_cmds_table[]=
{
	{"SSLADDR", set_ssl_addr, "   AT+SSLADDR: Get/Set address for SSL.\r\n", NULL},//add a AT cmd for SSL
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
	
	//HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart recv %d bytes data %d\n",event,len,buf_len);
	if((memcmp(data, "POST", 4)==0)||(memcmp(data, "GET", 3)==0))
	{
		hffile_userbin_read(0, ssl_url, 100);	
		my_ssl_test(ssl_url, data, len);//do SSL Get/Post
		return 0;
	}
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

void app_init(void)
{
	u_printf("app_init\n");
}

static void app_user_ssl_test(void *arg)
{
	#ifdef	MBEDTLS_TEST_SERVER
	int ret = 0;
	uint32_t ip = 0;
	void *ssl = NULL;
	char *server = NULL;
	char buff[1024] = {0};

	hfnet_get_wan_ip(&ip, NULL,NULL);
    server = inet_ntoa(ip);
	#else
	my_ssl_test("a3mfhuwviolcif-ats.iot.us-east-1.amazonaws.com",NULL,0);
	#endif

	while(1)
	{
		#ifdef	MBEDTLS_TEST_SERVER
		ssl = app_mbedtls_ssl_server(server,"443",root_ca,strlen(root_ca)+1,server_crt,strlen(server_crt)+1,server_key,strlen(server_key)+1);
		if(ssl == NULL)
			continue;
		
		memset(buff,0,sizeof(buff));
		ret = app_mbedtls_ssl_recv(ssl,buff,sizeof(buff)-1);
		if(ret > 0)
		{
			u_printf("%s\n",buff);
			app_mbedtls_ssl_send(ssl,HttpRspDataFormat,strlen(HttpRspDataFormat));
		}

		app_mbedtls_ssl_close(ssl);
		#endif
		msleep(100);
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
	
	//this is a new function, can define the stack size for UART thread
	if(hfnet_start_uart_ex(0, HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback, 2048)!=HF_SUCCESS)
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

	hfthread_create(app_user_ssl_test,"app user ssl test",1024*4,NULL,HFTHREAD_PRIORITIES_LOW,NULL,NULL);
	
	return 1;
}

