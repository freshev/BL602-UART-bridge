/* mqtt_ssl.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include "hsf.h"
#include "mqtt_ssl.h"
#include "MQTT/mqtt_api.h"

#ifdef	MBEDTLS_SSL_ENABLE
#include "mbedtls_compatible_alios.h"
#else
#include <cyassl/openssl/ssl.h>
#include <cyassl/internal.h>
#include <cyassl/cyassl_config.h>
#endif


//if you want use certificate, please define macro 'SSL_CONNECT_NEED_CERT'
#define SSL_CONNECT_NEED_CERT


#define MQTT_RCV_BUF_NUM 1500
static char g_mqtt_recv_buf[MQTT_RCV_BUF_NUM];


#ifdef SSL_CONNECT_NEED_CERT
static const char* root_ca =
"-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n";



static const char *device_cert = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVAKZzSmopqHUJydty2sT3Bq93i87QMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzEwMTAwOTE4\n"
"NTVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCwmb9pg1VE9Pf2+bCO\n"
"QddCvOeA3IhzpIbda0m15U3GAfbkWt0HxlyPpXBx88cSnmJ4gU7BlXcU9MoKecMw\n"
"XsRedFiZ3rwy75Mv7WI4gQsWRe90/ZTe28lz67Uv+Rn4gym3lShB70XRytzJ3JuG\n"
"HHtWZbUSjiLkcGLz71BIuxD4ioSWpoaDdM58B58vMhzleczfEMnCGbkOfAyS9FmI\n"
"sIMCpqjh7kJS8cJFrYBUe6tmp8uoZIYafNqJSwFzHP/SOKDZSqh0CPSPbzuWKR9w\n"
"klkfC4VTGUm9bfp6BXBYpTeU3Kab2Xo8cvSq1WW7p57oUP9nQwnixofRiIsOq0eV\n"
"3QM1AgMBAAGjYDBeMB8GA1UdIwQYMBaAFGo/kpssax2qzueEvwXvAqccJKX9MB0G\n"
"A1UdDgQWBBQVRNhce7mT1C5Dlg8YIJGvtEG9vjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAq56q2kEzcFdtymMxn7DfREUr\n"
"FjEwD7dl1bFIOCIBMMnfxcdSD+Xy9gKgC8j5dY/WbOzzeesv9d3ffqqpru2P3JRN\n"
"HSNK//qSfPHTS882HxRYbHsp4OUBo3gfqZ930m6jBn1yhQ5VIgQ/lhv1BkRwbl2B\n"
"8Sx4w8TUVqJ4Si03A62xTRHqvJnZH7dTTcqHS0KcMaScKiK60euSgj2V5VIhdbCO\n"
"sa0NoQcvMO9S/Q6KOBYXN2iQeM/Sdeiylf1hKpnL2xRoDYVcNKjhG825qMC1yika\n"
"uovlHjIOJjW+K5tzzhIGxCgl08c+yrhsnII0j2lJo8QQP1yOrB/vRR6h7FTogQ==\n"
"-----END CERTIFICATE-----\n";



static const char *private_key =
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEpAIBAAKCAQEAsJm/aYNVRPT39vmwjkHXQrzngNyIc6SG3WtJteVNxgH25Frd\n"
"B8Zcj6VwcfPHEp5ieIFOwZV3FPTKCnnDMF7EXnRYmd68Mu+TL+1iOIELFkXvdP2U\n"
"3tvJc+u1L/kZ+IMpt5UoQe9F0crcydybhhx7VmW1Eo4i5HBi8+9QSLsQ+IqElqaG\n"
"g3TOfAefLzIc5XnM3xDJwhm5DnwMkvRZiLCDAqao4e5CUvHCRa2AVHurZqfLqGSG\n"
"GnzaiUsBcxz/0jig2UqodAj0j287likfcJJZHwuFUxlJvW36egVwWKU3lNymm9l6\n"
"PHL0qtVlu6ee6FD/Z0MJ4saH0YiLDqtHld0DNQIDAQABAoIBAGzeCwrvpJRC883z\n"
"9SxtWFdS/uAIk7G+nklHR4RznHNRaLMzdIjDdvIyydPltTY8H3YsOLHMA0IO+bJl\n"
"h7d85E9aJ/iLP7eiyzjDfUZZ/sy3Rjv3y1trYJAuoV62kJULvp7mu4+SApenGF70\n"
"uYd+bWZAgtSyfL4Yrle0kuiTMY4VR8fbXXegxX9N9pb24ca6IJrp59qXpkbJjmAT\n"
"W+9nEvqeQkl6rEZvVjJBvin29FPQVDN7scNy3jzTQniwOwWEKrUhsQ2kv3RSOywB\n"
"e+O+lE0hmuZLQjTbKdrBQaiOgf8rlwZ0q6dkod8dmpHL+bn+BxLqpSd9y2K94oVo\n"
"A1YUJk0CgYEA4GtXmpHc+IDc2h/HU7xs/ba0e2Erp4eWTPMwWCp9MUiuS4O93OJI\n"
"llli3vNVivTvwhxH8hXsxgCHBby8fYh8sJZJvIA6ihyCsqV66sWiB8uZkO0gt4WB\n"
"5JUMQ5JFBsWobWVPxUDVqIaicTF23UT7nJCS7wTTQmDlUB0hRWwG1pMCgYEAyXO+\n"
"969tFTZcCVrwSMkqxbWvpR2R7JucyhAGO/ACUrxjorJtKiSEkW37B2YL2PbBYi1C\n"
"9oe2EcLEOn6a7t8aSygXDcfblrcRhI9mFAot6g5O9Uecpqv/bsBZCW5kiLLH+4iS\n"
"ZmDjd0ThLB1QS8rcrp+MtxxoxPINVtdXOST61BcCgYBatAfcOUgOSEb7Ag0WEvoa\n"
"MVYQ5901AOAGiePoPoQK/00yyDRcqjicS9RiOAdC+mxNEBEkDyh7fosUDoxAUIHU\n"
"/Wkf/tOqLovEmI1thiNO80NGCBFJG3S8ZmFmjh/H9Ot2C5SKLQIt8vyEs3FPTSpE\n"
"xUodwN2B3pfQIXXpERhScQKBgQCvx3htpTvYk4sxepFJ4YaZ55PwzmGDBLGFuv/F\n"
"kwJj8RA7addJO34Va9LrvMY/teg942KXvQlIbBtPMyO7pR7LT5r2IlrgIrN9aKbY\n"
"e51eqseIzMjKwi/rEpleWl4MzXskZyHfhVFVw9t648UprURsdrmRGY/tsYukJ9hq\n"
"+3KGVwKBgQCZ/aiD2Eg+a39CqwJIRLmIhzztwBafieBJj3+WXZXdzkACqeAj+7wf\n"
"xZlNshNBgwDp78y+8OqY1QuhwaYDD2iDbAe3PbEOFWkL2INPPJ9LEeSAxHv9G8bS\n"
"RcYVfse0G80GWzrkUvbGSGL1aQb0r6HSF/hjL8pl+rON2ERNdkOZpA==\n"
"-----END RSA PRIVATE KEY-----\n";

#endif



static int tcp_connect_ssl_server(char *addrp, unsigned short port)
{
	int fd;	
	struct sockaddr_in addr;

	ip_addr_t dest_addr;
	if(hfnet_is_ipaddress((const char *)(addrp)) !=1 )
	{
		if(hfnet_gethostbyname((const char *)(addrp), &dest_addr) !=HF_SUCCESS)
		{
			u_printf("gethostbyname [%s] fail\r\n", addrp);
			return -1;
		}
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

	int tmp=1;
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp) )<0)
	{
		u_printf("set SOL_SOCKET fail\r\n");
	}	
	
	if(setsockopt(fd, SOL_SOCKET,SO_KEEPALIVE,&tmp,sizeof(tmp))<0)
	{
		u_printf("set SO_KEEPALIVE fail\r\n");
	}
	tmp = 60;//60s
	if(setsockopt(fd, IPPROTO_TCP,TCP_KEEPIDLE,&tmp,sizeof(tmp))<0)
	{
		u_printf("set TCP_KEEPIDLE fail\r\n");
	}
	tmp = 5;
	if(setsockopt(fd, IPPROTO_TCP,TCP_KEEPINTVL,&tmp,sizeof(tmp))<0)
	{
		u_printf("set TCP_KEEPINTVL fail\r\n");
	}
	tmp = 3;
	if(setsockopt(fd, IPPROTO_TCP,TCP_KEEPCNT,&tmp,sizeof(tmp))<0)
	{
		u_printf("set TCP_KEEPCNT fail\r\n");
	}
	
	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr))< 0)
	{
		close(fd);
		return -1;
	}
	
	return fd;
}

static int mqtt_callback(hfmqtt_event_id_t event, char *topic, unsigned char *data, int data_len)
{
	switch(event)
	{
		case HFMQTT_CONNECTED:
			u_printf("MQTT >>> connected to server\r\n");
			break;

		case HFMQTT_DISCONNECTED:
			u_printf("MQTT >>> disconected\r\n");
			break;

		case HFMQTT_TOPIC_SUB_SUCCESSED:
			u_printf("MQTT >>> sub topic <%s> successed\r\n",topic);
			break;

		case HFMQTT_TOPIC_SUB_DATA:
			u_printf("MQTT >>> recv topic <%s> data_len [%d]\r\n", topic,data_len);
			break;

		case HFMQTT_TOPIC_UNSUB_SUCCESSED:
			u_printf("MQTT >>> unsub topic <%s> successed\r\n",topic);
			break;

		case HFMQTT_PING_RESPONSE:
			u_printf("MQTT >>> ping response\r\n");
			break;
			
		default :
			break;
	}
	
	return 0;
}






static void mqtt_thread(void *arg)
{
#ifdef	MBEDTLS_SSL_ENABLE
	void *ssl = NULL;
#else
	CYASSL_CTX*     ctx = NULL;
	CYASSL*         ssl = NULL;
#endif
	int sockfd;
	fd_set fdR;
	int rc, beat;
	struct timeval interval;

#ifndef	MBEDTLS_SSL_ENABLE
	CyaSSL_Init();
#endif
	
	hfmqtt_init(mqtt_callback);
	hfmqtt_set_clientid(MQTT_CLIENT_ID); //default is station MAC address
	//hfmqtt_set_auth(char *username, char *password); //default is demo & demo
	hfmqtt_set_alive_time(60);//default is 300 seconds
	
	hfmqtt_sub("yosemite_lawn_mower");
	hfmqtt_sub("1111");
	// hfmqtt_sub("mqtt_test_topic_2");
	
	while(1)
	{
#ifndef	MBEDTLS_SSL_ENABLE
		ctx = NULL;
#endif
		ssl = NULL;
		sockfd = -1;
		msleep(1000);
		
		if(!hfwifi_sta_is_connected())
			continue;

		sockfd=tcp_connect_ssl_server(MQTT_SERVER_ADDR, MQTT_SERVER_PORT);
		if(sockfd<0)
		{
			HF_Debug(DEBUG_LEVEL_LOW, "create socket error\r\n");
			continue;
		}
#ifdef	MBEDTLS_SSL_ENABLE
		ssl = app_mbedtls_ssl_connect((void *)sockfd, root_ca,strlen(root_ca)+1,device_cert,strlen(device_cert)+1,private_key,strlen(private_key)+1);
		if (ssl == NULL)
		{
			HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed");
			goto EXIT_SLL;
		}
#else
		InitMemoryTracker();//for debug, it can show how many memory used in SSL
		CyaSSL_Debugging_ON();//for debug

		ctx = CyaSSL_CTX_new(CyaTLSv1_2_client_method());
		if (ctx == NULL)
		{
			HF_Debug(DEBUG_LEVEL_LOW, "unable to get ctx\r\n");
			goto EXIT_SLL;
		}

#ifdef SSL_CONNECT_NEED_CERT
		if(SSL_SUCCESS != CyaSSL_CTX_load_verify_buffer(ctx, (const unsigned char*)root_ca, (long)strlen(root_ca),  SSL_FILETYPE_PEM))
		{
			HF_Debug(DEBUG_LEVEL_LOW, "unable to load verify buffer\r\n");
			goto EXIT_SLL;
		}

		if(SSL_SUCCESS != CyaSSL_CTX_use_PrivateKey_buffer(ctx, (const unsigned char*)private_key, (long)strlen(private_key), SSL_FILETYPE_PEM))
		{
			HF_Debug(DEBUG_LEVEL_LOW, "unable to load privatekey buffer\r\n");
			goto EXIT_SLL;
		}

		if(SSL_SUCCESS != CyaSSL_CTX_use_certificate_buffer(ctx, (const unsigned char*)device_cert, (long)strlen(device_cert), SSL_FILETYPE_PEM)) 
		{
			HF_Debug(DEBUG_LEVEL_LOW, "unable to load certificate buffer\r\n");
			goto EXIT_SLL;
		}
#else
		CyaSSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, 0);//disable verify certificates
#endif

		ssl = CyaSSL_new(ctx);
		if (ssl == NULL)
		{
			HF_Debug(DEBUG_LEVEL_LOW, "unable to get SSL object\r\n");
			goto EXIT_SLL;
		}
		
		CyaSSL_set_fd(ssl, sockfd);
		if (CyaSSL_connect(ssl) != SSL_SUCCESS)
	 	{
			int  err = CyaSSL_get_error(ssl, 0);
			char buffer[80];
			HF_Debug(DEBUG_LEVEL_LOW, "err = %d, %s\r\n", err,CyaSSL_ERR_error_string(err, buffer));
			HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed\r\n");

			goto EXIT_SLL;
	    }
#endif

		HF_Debug(DEBUG_LEVEL_LOW,"SSL connect success----------------------------------------\r\n");
		
		hfmqtt_login((void *)ssl);

		beat = hfsys_get_time();
		while(1)
		{
			if(hfsys_get_time() - beat > 60*1000)//send MQTT ping each 60s
			{
				hfmqtt_ping();
				beat = hfsys_get_time();
			}
			
			interval.tv_sec = 0;
			interval.tv_usec = 100000;

			FD_ZERO(&fdR);
			FD_SET(sockfd,&fdR);
			rc= select(sockfd+1,&fdR,NULL,NULL,&interval);
			if(rc <= 0)
				continue;

			if(!FD_ISSET(sockfd, &fdR))
				continue;
			#ifdef	MBEDTLS_SSL_ENABLE
			int rc = app_mbedtls_ssl_recv(ssl, g_mqtt_recv_buf, MQTT_RCV_BUF_NUM);
			#else
			int rc = CyaSSL_recv(ssl, g_mqtt_recv_buf, MQTT_RCV_BUF_NUM, 0);
			#endif
			if(rc <= 0)
			{
				u_printf("app mbedtls recv < 0 ....\n");
				break;//socket closed
			}
				
			hfmqtt_data_parse(g_mqtt_recv_buf);
		}
		
	EXIT_SLL:
		#ifdef	MBEDTLS_SSL_ENABLE
		app_mbedtls_ssl_close(ssl);
		#else
		CyaSSL_shutdown(ssl);
		CyaSSL_free(ssl);
		CyaSSL_CTX_free(ctx);
		#endif
		close(sockfd);

		hfmqtt_close();
		#ifndef	MBEDTLS_SSL_ENABLE
		CyaSSL_Debugging_OFF();//close debug
		ShowMemoryTracker();//peek into how memory was used
		#endif
		HF_Debug(DEBUG_LEVEL_LOW,"SSL closed.\r\n");
		msleep(3000);
	}
}

void start_mqtt_ssl_test(void)
{
	if(hfthread_create(mqtt_thread, "MQTT", 2048, NULL, HFTHREAD_PRIORITIES_LOW, NULL, NULL)!= HF_SUCCESS)
	{
		HF_Debug(DEBUG_ERROR,"create MQTT thread fail\n");
	}

	return;
}

