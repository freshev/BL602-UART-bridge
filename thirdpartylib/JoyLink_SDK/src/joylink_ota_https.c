#include <hsf.h>
#include "joylink_extern.h"
#include "joylink_extern_ota.h"
#include "joylink_string.h"

#include <cyassl/openssl/ssl.h>
#include <cyassl/internal.h>
#include <cyassl/cyassl_config.h>

int content_data_size = 511111;
unsigned char wifi_firmware_proto_head[10] = {"HF-LPx70x1"};

#define HTTPS_DATA_SIZE 768

void joylink_parse_url(char *url ,char *joylink_url ,char *joylink_host)
{
	char *temp_url;
	
	if((memcmp(url, "HTTPS://", 8) == 0) || (memcmp(url, "https://", 8) == 0))
	{
		temp_url = strchr((url + 8), '/');
		strcpy(joylink_url, temp_url);
		memcpy(joylink_host, (url + 8), strlen(url) - strlen(temp_url) - 8);
	}

}

int user_tcp_connect_ssl_server(char *url,unsigned short port)
{
    
	int fd;	
	struct sockaddr_in addr;
	char *addrp=url;
	
	if((memcmp(url, "HTTPS://", 8)==0)||(memcmp(url, "https://", 8)==0))
		addrp= (char *)(url+8);

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

int wifi_firmware_find_head(char *data,int len)
{
	int pos=0;
	int head_len = sizeof(wifi_firmware_proto_head);
	
	if (head_len == 0) 
		return 0;
	while(pos+head_len < len)
	{
		// TODO: 包头识别
		if (memcmp(data+pos,wifi_firmware_proto_head,head_len)==0)
		{
			return pos;
		}
			
		pos++;
	}
	return -1;
}

extern char down_present;

void joylink_https_ota(char *url,char *host)
{
//	InitMemoryTracker();//for debug, it can show how many memory used in SSL
//	CyaSSL_Debugging_ON();//for debug

	CyaSSL_Init();
	CYASSL_METHOD*  method  = 0;
	CYASSL_CTX*     ctx     = 0;
  	CYASSL*         ssl     = 0;
	int sockfd=-1;
	
    int ret = -1;
	fd_set fdR;
	struct timeval timeout;
	char *str_p = NULL;
	int present = 0;

	
    int read_size = 0;
    char *content_data = NULL;
    content_data = (char*)hfmem_malloc(HTTPS_DATA_SIZE);
    if(content_data == NULL)
    {
        return ;
    }
    bzero(content_data,HTTPS_DATA_SIZE);
    
    int total_size = 0;
    char *wifi_content_data = NULL;
    wifi_content_data = (char*)hfmem_malloc(HTTPS_DATA_SIZE);
    if(wifi_content_data == NULL)
    {
        return ;
    }
    bzero(wifi_content_data,HTTPS_DATA_SIZE);
	
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
    
	sockfd = user_tcp_connect_ssl_server(host, 443);
	if(sockfd<0)
	{
		HF_Debug(DEBUG_LEVEL_LOW, "\r\n[HTTPS] create socket error\r\n\r\n");
		goto FREE_SSL;
	}
	
	HF_Debug(DEBUG_LEVEL_LOW, "user_tcp_connect_ssl_server success   next CyaSSL_set_fd----------\r\n");
	CyaSSL_set_fd(ssl, sockfd);
	if (CyaSSL_connect(ssl) != SSL_SUCCESS)
 	{
 		HF_Debug(DEBUG_LEVEL_LOW, "CyaSSL_connect(ssl) != SSL_SUCCESS-\r\n");
		int  err = CyaSSL_get_error(ssl, 0);
		char buffer[80];
		HF_Debug(DEBUG_LEVEL_LOW, "err = %d, %s\n", err,CyaSSL_ERR_error_string(err, buffer));
		HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed----------\r\n");		
	}
	else
	{
        HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect successed ----------------------------------------\n");
	}

    //TODO 数据最前面加上请求方法GET 
    char CyaSSL_write_data[500] = {0};
    strcpy(CyaSSL_write_data, "GET ");  //数据最前面加上请求方法GET 
    
    //TODO 数据后面加上url和host
    sprintf(CyaSSL_write_data+strlen("GET "), "%s HTTP/1.1\r\nHost:%s\r\n\r\n", url,host);  
    u_printf("\r\n[HTTPS] writ data is \r\n%s",CyaSSL_write_data);
	
    if(CyaSSL_write(ssl, CyaSSL_write_data, strlen(CyaSSL_write_data)) != strlen(CyaSSL_write_data))
    {
        int  err = CyaSSL_get_error(ssl, 0);
        char buffer[80];
        HF_Debug(DEBUG_LEVEL_LOW,"\r\n[HTTPS] write failed!!!\r\n\r\n");
        HF_Debug(DEBUG_LEVEL_LOW, "\r\n[HTTPS] err = %d, %s\n", err,CyaSSL_ERR_error_string(err, buffer));
    }
    else
    {
        HF_Debug(DEBUG_LEVEL_LOW,"\r\n[HTTPS] write sucessfully\r\n\r\n");
    }

//    CyaSSL_Debugging_OFF();
    	
    while(1)
    {
        if(!hfwifi_sta_is_connected())
        {
			u_printf("hfwifi_sta_is_not_connected\r\n");
            goto FREE_SSL;
        }
        FD_ZERO(&fdR);
        if(sockfd>=0)
			FD_SET(sockfd,&fdR);
		timeout.tv_sec= 5;
		timeout.tv_usec= 0;
		HF_Debug(DEBUG_LEVEL_LOW,"\r\n[HTTPS] wait data\r\n\r\n");
		
		//程序去select的时候，如果没有数据输入，程序会一直等待，直到有数据为止，也就是程序中无需循环和sleep。
        ret = select(sockfd+1, &fdR, NULL, NULL, &timeout); //使用Select就可以完成非阻塞,方式工作的程序，它能够监视我们需要监视的文件描述符的变化情况——读写或是异常。

		if(ret <= 0)
		{
            //HF_Debug(DEBUG_LEVEL_LOW,"\r\n[HTTPS] select function return is %d\r\n\r\n",ret);
            continue;
		}
		
		if(FD_ISSET(sockfd, &fdR))  //检查fdset联系的文件句柄fd是否可读写，当>0表示可读写。
		{
		    
            if(1)
            {
                hfupdate_start(HFUPDATE_SW);
                while((read_size = CyaSSL_read(ssl, wifi_content_data, HTTPS_DATA_SIZE)) > 0)
                {
                
                    int wifi_firmware_data_len = 0;
                    if(memcmp((char *)wifi_content_data, "HTTP/1.1 200 OK", strlen("HTTP/1.1 200 OK")) == 0)
                    {
                        int wifi_firmware_head = wifi_firmware_find_head(wifi_content_data, HTTPS_DATA_SIZE);
                        u_printf("[WIFI OTA] firmware_head_len : %d\r\n",wifi_firmware_head);

						str_p = jl_platform_strstr(wifi_content_data,"Content-Length");
						if(str_p == NULL){
							log_error("http parse file size error!\n");
							goto FREE_SSL;
						}
						else{
							str_p = str_p + jl_platform_strlen("Content-Length") + 2; 
							content_data_size = jl_platform_atoi(str_p);
						}

                        u_printf("[WIFI OTA] ota_file_len : %d\r\n",content_data_size);

                        if(wifi_firmware_head != -1)
                        {
                            wifi_firmware_data_len = HTTPS_DATA_SIZE - wifi_firmware_head;
                            hfupdate_write_file(HFUPDATE_SW, total_size,(uint8_t *)wifi_content_data+wifi_firmware_head, wifi_firmware_data_len);
                            total_size+=wifi_firmware_data_len;
                            u_printf("[WIFI OTA] download file:[%d] [%d]\r\n",total_size,read_size);
                        }
                    }
                    else
                    {
                        wifi_firmware_data_len = read_size;
                        hfupdate_write_file(HFUPDATE_SW, total_size,(uint8_t *)wifi_content_data, wifi_firmware_data_len);
                        total_size+=wifi_firmware_data_len;
                        u_printf("[WIFI OTA] download file:[%d] [%d]\r\n",total_size,read_size);
						
						present = total_size*100/content_data_size;
						down_present = present;
						msleep(50);
                        if(total_size >= content_data_size)
                        {
                            u_printf("\r\n[WIFI OTA] total_size:%d\r\n",total_size);
                            
                            if(hfupdate_complete(HFUPDATE_SW,total_size)!=HF_SUCCESS)
                            {
                                u_printf("update software fail\r\n");
								
								joylink_ota_report_status(OTA_STATUS_FAILURE, 100, "download failed");
								msleep(100);
	                            goto FREE_SSL;
							}
                            
                            u_printf("update software success\r\n");
                            u_printf("\r\n\r\n[WIFI OTA] DONE!!!\r\n\r\n");
							
							joylink_ota_report_status(OTA_STATUS_SUCCESS, 100, "ota is ok");
							msleep(100);
							
                            goto FREE_SSL;

                        }
                    }
                }
            }
            break;
		}
    }
FREE_SSL:
    if(content_data != NULL)
        hfmem_free(content_data);
    if(wifi_content_data != NULL)
        hfmem_free(wifi_content_data);
	CyaSSL_shutdown(ssl);
	CyaSSL_free(ssl);
FREE_CTX:
	CyaSSL_CTX_free(ctx);
	close(sockfd);
	u_printf("hfsys_softreset\r\n");
	hfsys_softreset();
}
