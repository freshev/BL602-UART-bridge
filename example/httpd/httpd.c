 /* httpd.c
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hsf.h>

#include "httpd.h"


static int ping_cmd_type = 0;
static int ping_cmd_flag = 0;
static char ping_cmd[128];
static int ping_cmd_response_flag = 0;
static char ping_cmd_response[128];

static char *hfstrnstr(const char *s, const char *find, size_t slen)
{
	int i,flen;
	
	flen = strlen(find);
	if(flen>slen)
		return NULL;
	
	for(i=0;i<=slen-flen;i++)
	{
		if(s[i]==*find)
		{
			if(strncmp(s+i,find,slen-i)==0)
				return (char*)(s+i);
		}
	}
	
	return NULL;
}

static char html_cmd_c2h(char c)
{
	char ret;

	if ((c>= '0')&&(c<= '9'))
		ret= c-'0'+0x0;
	else if ((c>= 'a')&&(c<= 'f'))
		ret= c-'a'+0xa;
	else if ((c>= 'A')&&(c<= 'F'))
		ret= c-'A'+0xa;
	else
		ret= (char)(-1);
	return ret;
}

static void html_string_decode(char *src, int src_len, char *dst, int dst_len)
{
	int i=0, j=0;
	while((i<src_len) && (src[i] != '\0') && (j<dst_len-1))
	{
		if(src[i] == 0x25)
		{
			dst[j] = ((char)html_cmd_c2h(src[i+1]))*16 + (char)html_cmd_c2h(src[i+2]);
			i += 2;
		}
		else if(src[i] == ' ')
			dst[j] = '+';
		else if(src[i] == '+')
			dst[j] = ' ';
		else
			dst[j]=src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

static void html_string_encode(char *src, int src_len, char *dst, int dst_len)
{
	int i=0, j=0;
	for(i=0; (i<src_len) && (src[i] != '\0') && (j<dst_len-1); i++)
	{
		if(src[i] == '\b' || src[i] == '\f' || src[i] == '\n' || src[i] == '\r' || src[i] == '\t' ||src[i] == '\'' ||src[i] == '\"' || src[i] == '\\')
		{
			dst[j++] = '\\';
		}
		dst[j++] = src[i];
	}
	dst[j] = '\0';
}

int USER_FUNC hfhttpd_para_nvset(char *cfg_name,int name_len, char *value, int value_len)
{
	char tem_buf[128];
	memset(tem_buf, 0, sizeof(tem_buf));
	html_string_decode(value, value_len, tem_buf, sizeof(tem_buf)-2);
	
	if(hfstrnstr(cfg_name, "CFG_PING_CMD_TYPE", name_len) != NULL)
	{
		if(strlen(tem_buf) == 0)
			return 0;
		u_printf("set CFG_PING_CMD_TYPE %s\r\n", tem_buf);
		
		ping_cmd_type = atoi(tem_buf);
		ping_cmd_response_flag = 1;
		return 0;
	}
	else if(hfstrnstr(cfg_name, "CFG_PING_CMD", name_len) != NULL)
	{
		if(strlen(tem_buf) == 0)
			return 0;
		u_printf("set CFG_PING_CMD %s\r\n", tem_buf);
		
		if(ping_cmd_type == 1)
		{
			strcpy(ping_cmd, tem_buf);
			ping_cmd_flag = 1;
			
			if(memcmp(tem_buf, "AT+WSCAN", strlen("AT+WSCAN")) == 0 ||
				memcmp(tem_buf, "AT+H", strlen("AT+H")) == 0)
			{
				strcpy(ping_cmd_response, "unsupport");
				ping_cmd_response_flag = 1;
			}
			else
			{
				strcat(tem_buf, "\r\n");
				hfat_send_cmd(tem_buf, strlen(tem_buf), ping_cmd_response, sizeof(ping_cmd_response));
				ping_cmd_response_flag = 1;
			}
		}
		else if(ping_cmd_type == 2)
		{
			strcpy(ping_cmd, tem_buf);
			ping_cmd_flag = 1;
			
			ip_addr_t dest_addr;
			if(!hfnet_is_ipaddress(tem_buf))
			{
				if(hfnet_gethostbyname(tem_buf, &dest_addr) != HF_SUCCESS)
				{
					strcpy(ping_cmd_response, "Unknown host");
					return 0;
				}
				else
					strcpy(tem_buf, ipaddr_ntoa(&dest_addr));
			}
			if(hfnet_ping(tem_buf) ==0)
				strcpy(ping_cmd_response, "Success");
			else
				strcpy(ping_cmd_response, "Timeout");
			ping_cmd_response_flag = 1;
		}
		
		return 0;
	}

	return -1;
}

int USER_FUNC hfhttpd_para_nvget(char *cfg_name,int name_len, char *value, int value_len)
{
	char tem_buf[128];
	
	if(hfstrnstr(cfg_name, "CFG_PING_CMD_TYPE", name_len) != NULL)
	{
		snprintf(tem_buf, sizeof(tem_buf)-1, "%d", ping_cmd_type);
		html_string_encode(tem_buf, strlen(tem_buf), value, value_len);
		return 0;
	}
	else if(hfstrnstr(cfg_name, "CFG_PING_CMD", name_len) != NULL)
	{
		if(ping_cmd_flag)
		{
			snprintf(tem_buf, sizeof(tem_buf)-1, "%s", ping_cmd);
			html_string_encode(tem_buf, strlen(tem_buf), value, value_len);
			ping_cmd_flag = 0;
		}
		return 0;
	}
	else if(hfstrnstr(cfg_name, "CFG_PING_RESULT", name_len) != NULL)
	{
		if(ping_cmd_response_flag)
		{
			snprintf(tem_buf, sizeof(tem_buf)-1, "%s", ping_cmd_response);
			html_string_encode(tem_buf, strlen(tem_buf), value, value_len);
			ping_cmd_response_flag = 0;
		}
		return 0;
	}
	else if(hfstrnstr(cfg_name,"CFG_FIRMWARE_VERSION",name_len) != NULL)
	{
		snprintf(tem_buf, sizeof(tem_buf)-1, "%s.%s", GLOBAL_VER, GLOBAL_LVER);
		html_string_encode(tem_buf, strlen(tem_buf), value, value_len);
		return 0;
	}
	else if(hfstrnstr(cfg_name,"CFG_WEBPAGE_INFO",name_len) != NULL)
	{
		snprintf(tem_buf, sizeof(tem_buf)-1, "%s", "1.0");
		html_string_encode(tem_buf, strlen(tem_buf), value, value_len);
		return 0;
	}

	return -1;
}

