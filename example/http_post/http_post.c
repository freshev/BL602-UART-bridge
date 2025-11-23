#include "hsf.h"
#include "httpclient.h"

char fin_data[512]={0};
static char mcu_file_data[1400]={0};

int hfhttp_send(int *fd,char *buf,int len);
int hfhttp_recv(int *fd,char *buf,int len);

int http_post_thread(char *http_url,const char *data,char *content_data)
{
	httpc_req_t  http_req;
	char *temp_buf=NULL;
	parsed_url_t url={0};
	http_session_t hhttp=0;
	int total_size,read_size=0;
	int rv=0;
	tls_init_config_t  *tls_cfg=NULL;
	char *test_url=http_url;

	bzero(&http_req,sizeof(http_req));
	http_req.type = HTTP_POST;
	http_req.version=HTTP_VER_1_1;

	if((temp_buf = (char*)hfmem_malloc(256))==NULL)
	{
		u_printf("no memory\n");
		rv= -HF_E_NOMEM;
		goto exit;
	}
	bzero(temp_buf, 256);

	if((rv=hfhttp_parse_URL(test_url,temp_buf , 256, &url))!=HF_SUCCESS)
	{
		goto exit;
	}

	if((rv=hfhttp_open_session(&hhttp,test_url,0,tls_cfg,3))!=HF_SUCCESS)
	{
		u_printf("http open fail\n");
		goto exit;
	}

	hfthread_disable_softwatchdog(NULL);

	http_req.resource = url.resource;
	http_req.content = data;
	http_req.content_len = strlen(data);
	hfhttp_prepare_req(hhttp,&http_req,HDR_ADD_CONN_CLOSE);
	if((rv=hfhttp_send_request(hhttp,&http_req))!=HF_SUCCESS)
	{
		u_printf("http send request fail\n");
		goto exit;
	}

	total_size=0;
		
	read_size=hfhttp_read_content(hhttp,content_data,1024);

	int i=0;
	u_printf("\r\n");
	for(i=0;i<read_size;i++)
	{
		u_printf("%c",content_data[i]);
	}
	u_printf("\r\n");
	
	exit:
	if(temp_buf!=NULL)  
		hfmem_free(temp_buf);
	if(hhttp!=0)
		hfhttp_close_session(&hhttp);

	hfthread_enable_softwatchdog(NULL,30);

	return rv;
}

int http_post_file_thread(char *http_url,int file_size)
{
   int ret,total_size=0;
	int i=0;
	httpc_req_t  http_req;
	char *temp_buf=NULL;
	parsed_url_t url={0};
	http_session_t hhttp=0;
	int read_size=0;
	int rv=-1;
	tls_init_config_t  *tls_cfg=NULL;
	char *test_url=http_url;
	char *http_write_data = NULL;
	char *fir_data = NULL;

	bzero(&http_req,sizeof(http_req));
	http_req.type = HTTP_POST;
	http_req.version=HTTP_VER_1_1;

	if((temp_buf = (char*)hfmem_malloc(256))==NULL)
	{
		u_printf("no memory\n");
		rv= -HF_E_NOMEM;
		goto exit;
	}
	bzero(temp_buf, 256);

//	u_printf("test url : %s.\r\n",test_url);

	if((rv=hfhttp_parse_URL(test_url,temp_buf , 256, &url))!=HF_SUCCESS)
	{
		goto exit;
	}

//	u_printf("url scheme: %s. hostname : %s. portno = %d. resource : %s.\r\n",url.scheme,url.hostname,url.portno,url.resource);

	if((rv=hfhttp_open_session(&hhttp,test_url,0,tls_cfg,3))!=HF_SUCCESS)
	{
		u_printf("http open fail\n");
		goto exit;
	}

	hfthread_disable_softwatchdog(NULL);

	
	if((http_write_data = (char*)hfmem_malloc(1024))==NULL)
	{
		u_printf("no memory\n");
		rv= -HF_E_NOMEM;
		goto exit;
	}
	
   if((fir_data = (char*)hfmem_malloc(512))==NULL)
   {
	   u_printf("no memory\n");
	   rv= -HF_E_NOMEM;
	   goto exit;
   }
	
   bzero(http_write_data,1024);
	
   sprintf(fir_data, "%s\r\n", "----------------------------487108334870865500588872");/*boundary 值由浏览器默认指定,并非固定*/
   sprintf(fir_data+strlen(fir_data), "%s\r\n", "Content-Disposition: form-data; name=\"part\"; filename=\"1111.bin\"");/*提交的表单*/
   sprintf(fir_data+strlen(fir_data), "%s\r\n\r\n", "Content-Type: application/octet-stream");/*数据类型*/
   
   int fir_len = strlen(fir_data);

   u_printf("fir_len %d\n",fir_len);

	memset(fin_data,0,512);
   sprintf(fin_data,"%s","----------------------------487108334870865500588872\r\nContent-Disposition: form-data; name=\"fileName\"\r\n\r\n1111\r\n\r\n----------------------------487108334870865500588872--\r\n");/*提交的表单*/
   int fin_len = strlen(fin_data);
   u_printf("fin_len %d\n",fin_len);

	
	sprintf(http_write_data,"POST %s HTTP/1.1\r\n",url.resource);
	sprintf(http_write_data+strlen(http_write_data), "%s\r\n", "connection: keep-alive");
	sprintf(http_write_data+strlen(http_write_data), "%s\r\n", "Host: 120.195.219.223:30080");
	sprintf(http_write_data+strlen(http_write_data), "%s\r\n", "Content-Type: multipart/form-data; boundary=--------------------------487108334870865500588872");
	sprintf(http_write_data+strlen(http_write_data), "Content-Length: %d\r\n\r\n", fin_len+file_size+2+fir_len-1);/* firt body + data len + \r\n + final body -1 */
	
	sprintf(http_write_data+strlen(http_write_data),"%s",fir_data);

	ret = hfhttp_send(hhttp,http_write_data,strlen(http_write_data));
	if(ret <= 0)
	{
	   u_printf("hfhttp_send error\r\n");
		rv = -1;
		goto exit;
	}
	u_printf("http_write_data %d\r\n",strlen(http_write_data));
	
	u_printf("\r\n");
	for(i=0;i<strlen(http_write_data);i++)
	{
		u_printf("%c",http_write_data[i]);
	}
	u_printf("\r\n");

	uint32_t p_data = hfpartition_addr(PARTITION_NAME_UPGRADE);
	memset(mcu_file_data,0,1400);

	while(1)
	{
		if(total_size+1024>file_size)
		{
			int remain = file_size-total_size;
			u_printf("remian %d\n",remain);
			hfflash_read(p_data+total_size, (unsigned char *)mcu_file_data, remain, 0);
			
			mcu_file_data[remain]='\r';
			mcu_file_data[remain+1]='\n';
			
			memcpy(mcu_file_data+remain+2,fin_data,fin_len);

			u_printf("mcu_file_data %d\r\n",remain+fin_len+2);

			u_printf("\r\n");
			for(i=0;i<remain+fin_len+2;i++)
			{
				u_printf("%02x",mcu_file_data[i]);
			}
			u_printf("\r\n");

			ret = hfhttp_send(hhttp,mcu_file_data,remain+fin_len+2);
			
			if(ret <= 0)
			{
			   u_printf("hfhttp_send error\r\n");
				rv = -1;
				goto exit;
			}
			else
				break;
		}
		else
		{
			hfflash_read(p_data+total_size, (unsigned char *)mcu_file_data, 1024, 0);

			ret = hfhttp_send(hhttp,mcu_file_data,1024);
			if(ret <= 0)
			{
				u_printf("hfhttp_send error\r\n");
				rv = -1;
				goto exit;
			}
		}
		total_size+=1024;
		u_printf("total_size %d\r\n",total_size);
		msleep(10);
	}

	memset(mcu_file_data,0,1400);
	ret = hfhttp_recv(hhttp,mcu_file_data,1400);
	if(ret > 0)
	{
		u_printf("hfhttp_recv %s\r\n",mcu_file_data);

	   rv = 0;
	   goto exit;
	}
	else
	{
		u_printf("hfhttp_recv error\r\n");
		rv = -1;
		goto exit;
	}

	exit:
	if(temp_buf!=NULL)	
		hfmem_free(temp_buf);
	if(fir_data!=NULL)	
		hfmem_free(fir_data);
	if(http_write_data!=NULL)	
		hfmem_free(http_write_data);
	if(hhttp!=0)
		hfhttp_close_session(&hhttp);

	hfthread_enable_softwatchdog(NULL,30);

	return rv;
}

