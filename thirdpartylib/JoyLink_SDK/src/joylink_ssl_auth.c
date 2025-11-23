#include <hsf.h>
#include "joylink_extern.h"
#include "joylink_ble_sdk.h"

#include <cyassl/openssl/ssl.h>
#include <cyassl/internal.h>
#include <cyassl/cyassl_config.h>

static USER_FUNC int tcp_connect_ssl_server(char *url)
{
	int fd;	
	struct sockaddr_in addr;
	unsigned short port = 443;
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
char ssl_recvbuf[1024];

int https_auth_start(char *url, const char *sendbuf, int sendnum)//a SSL test
{
	//InitMemoryTracker();//for debug, it can show how many memory used in SSL
	//CyaSSL_Debugging_ON();//for debug

	CyaSSL_Init();
	CYASSL_METHOD*  method  = 0;
	CYASSL_CTX*     ctx     = 0;
	CYASSL*         ssl     = 0;
	int sockfd=-1;
	int recvlen=0,ret=0;
	
	method=CyaTLSv1_2_client_method();
	if (method == NULL)
		HF_Debug(DEBUG_LEVEL_LOW, "unable to get method");

	ctx = CyaSSL_CTX_new(method);
	if (ctx == NULL)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "unable to get ctx");
		return 0;
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
		if(has_softap_flag>0){
			u_printf("E_JL_NET_CONF_ST_WIFI_CONNECT_WAN_ERROR\r\n");
			jl_send_net_config_state(E_JL_NET_CONF_ST_WIFI_CONNECT_WAN_ERROR,NULL,0);
		}
		msleep(100);
		scan_suc = 0;
		hfwifi_scan_ex(hf_atcmd_wscan_callback, NULL, 0, 5);

		if(scan_suc == 0){
			char data[50];
			u_printf("can not scan this ssid\n");
			sprintf(data,"%d_%ddBm",0xFF,0);
			u_printf("E_JL_NET_CONF_ST_CONFIG_FAILED_INFO\r\n");
			jl_send_net_config_state(E_JL_NET_CONF_ST_CONFIG_FAILED_INFO,(uint8_t *)data,strlen(data));
		}
		
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

//	sendlen = strlen(sendbuf);
	
	ret = CyaSSL_write(ssl, sendbuf, 1024);
	
//	u_printf("[%s:%d]:\r\n%s\r\n",__FUNCTION__,__LINE__,sendbuf);
	
	if ( ret<=0 )
		u_printf("SSL_write fail %d \r\n",ret);
	else
		u_printf("SSL_write success %d \r\n",ret);

	memset(ssl_recvbuf,0,1024);
	recvlen = CyaSSL_read(ssl, ssl_recvbuf, sizeof(ssl_recvbuf)-1);

	u_printf("[%s:%d]:recvlen %d\r\n",__FUNCTION__,__LINE__,recvlen);
	
	if (recvlen > 0)
	{
		HF_Debug(DEBUG_LEVEL_LOW,"Server response: recv start ----------------------------------------\n");

		u_printf("[%s:%d]:%s\r\n",__FUNCTION__,__LINE__,ssl_recvbuf);

		memcpy(https_post_data_t.revbuf,ssl_recvbuf,recvlen);
		
		HF_Debug(DEBUG_LEVEL_LOW,"\n---------------------------------------- recv End!\n");	
	}
	else if (recvlen < 0) 
	{
		int readErr = CyaSSL_get_error(ssl, 0);
		if (readErr != SSL_ERROR_WANT_READ)
			HF_Debug(DEBUG_LEVEL_LOW, "CyaSSL_read failed");
	}
	else
		HF_Debug(DEBUG_LEVEL_LOW,"\n---------------------------------------- recv NULL!\n"); 

FREE_SSL:
	CyaSSL_shutdown(ssl);
	CyaSSL_free(ssl);
FREE_CTX:
	CyaSSL_CTX_free(ctx);
	close(sockfd);
	
	//CyaSSL_Debugging_OFF();//close debug
	//ShowMemoryTracker();//peek into how memory was used

	return recvlen;
}
	
