/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "MQTTHF.h"
#include "MQTTmbedtls.h"

void *mqtt_ssl = NULL;

const char hf_mqtt_version[]="MQTT-HF3.0(2020-07-23)";
const char *MQTT_version(void)
{
	return hf_mqtt_version;
}

void gettimeofday_hf(struct timeval *a, void *__tz)
{
	unsigned int tick = hfsys_get_time();
	a->tv_sec = tick/1000;
	a->tv_usec = (tick%1000)*1000;
}

void timersub_hf(struct timeval *a, struct timeval *b, int *ret_sec,int *ret_usec)
{
	if(NULL == a || NULL == b || NULL == ret_sec || NULL == ret_usec)
		return ;

	*ret_sec = (int)(a->tv_sec - b->tv_sec);
	if (a->tv_usec < b->tv_usec)
	{
		a->tv_usec += 1000000;
		*ret_usec = a->tv_usec - b->tv_usec;	
		*ret_sec -= 1;
	}
	else
		*ret_usec = a->tv_usec - b->tv_usec;
}


void timeradd_hf(struct timeval *a, struct timeval *b, struct timeval *ret)
{
	if(NULL == a || NULL == b || NULL == ret)
		return ;

	ret->tv_sec = a->tv_sec + b->tv_sec;
	ret->tv_usec = a->tv_usec + b->tv_usec;
	if (ret->tv_usec >= 1000000)
	{
		ret->tv_usec -= 1000000;
		ret->tv_sec += 1;
	}
}

char expired(Timer_mqtt* timer)
{
	struct timeval now;
	gettimeofday_hf(&now, NULL);
    int ret_sec = 0,ret_usec =0;
	timersub_hf(&timer->end_time, &now, &ret_sec, &ret_usec);
	return ret_sec < 0 || (ret_sec == 0 && ret_usec <= 0);
}


void countdown_ms(Timer_mqtt* timer, unsigned int timeout)
{
	struct timeval now;
	gettimeofday_hf(&now, NULL);
	struct timeval interval = {timeout / 1000, (timeout % 1000) * 1000};
	timeradd_hf(&now, &interval, &timer->end_time);
}


void countdown(Timer_mqtt* timer, unsigned int timeout)
{
	struct timeval now;
	gettimeofday_hf(&now, NULL);
	struct timeval interval = {timeout, 0};
	timeradd_hf(&now, &interval, &timer->end_time);
}


int left_ms(Timer_mqtt* timer)
{
	struct timeval now;
	gettimeofday_hf(&now, NULL);
    int ret_sec = 0,ret_usec =0;	
	timersub_hf(&timer->end_time, &now, &ret_sec, &ret_usec);
	return (ret_sec < 0 || (ret_sec == 0 && ret_usec <= 0)) ? 0 : ret_sec * 1000 + ret_usec / 1000;	
}


void InitTimer(Timer_mqtt* timer)
{
	timer->end_time = (struct timeval){0, 0};
}


int hf_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	struct timeval interval = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
	if (timeout_ms <= 0)
	{
		interval.tv_sec = 0;
		interval.tv_usec = 100;
	}	

    /*Rui:useless for LPB100*/
	//setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));
	#if 1
	fd_set fdR;
	int select_ret = 0;

	FD_ZERO(&fdR);
	FD_SET(n->my_socket,&fdR);
	select_ret= select(n->my_socket+1,&fdR,NULL,NULL,&interval);
	if(select_ret<=0)
        return 0;

	if(!FD_ISSET(n->my_socket, &fdR))
		return 0;
     #endif
	 
	int bytes = 0;
	while (bytes < len)
	{   
		int rc = recv(n->my_socket, &buffer[bytes], (size_t)(len - bytes), 0);	
		//u_printf("%s: len %d|recv_len %d\n",__FUNCTION__, len, rc);

		//Rui:
        if(rc == 0)
			return -1;
		
		if (rc == -1)
		{
			if (errno != ENOTCONN && errno != ECONNRESET)
			{
				bytes = -1;
				break;
			}
		}
		else
			bytes += rc;
	}
	return bytes;
}


int hf_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
//	struct timeval tv;
//	tv.tv_sec = 0;  /* 30 Secs Timeout */
//	tv.tv_usec = timeout_ms * 1000;  // Not init'ing this can cause strange errors

//	setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	int	rc = send(n->my_socket, buffer, len, 0);
	return rc;
}


void hf_disconnect(Network* n)
{
	close(n->my_socket);
}


void NewNetwork(Network* n)
{	
	n->my_socket = -1;
#ifdef _NOT_SUPPORT_JD_
	if(g_hf_config_file.mqtt_tls)
	{
		n->mqttread = mqtt_mbedtls_ssl_recv;
		n->mqttwrite = mqtt_mbedtls_ssl_send;
		n->disconnect = mqtt_mbedtls_ssl_close;
	}
	else
#endif
	{
		n->mqttread = hf_read;
		n->mqttwrite = hf_write;
		n->disconnect = hf_disconnect;
	}
}

int ConnectNetwork(Network* n, char* addr, int port)
{
	int type = SOCK_STREAM;
	struct sockaddr_in address;
	int rc = -1;
	u8_t family = AF_INET;	
	struct addrinfo *result = NULL;
	struct addrinfo hints = {0, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, 0, NULL, NULL, NULL};

	if ((rc = getaddrinfo(addr, NULL, &hints, &result)) == 0)
	{
		struct addrinfo* res = result;

		/* prefer ip4 addresses */
		while (res)
		{
			if (res->ai_family == AF_INET)
			{
				result = res;
				break;
			}
			res = res->ai_next;
		}

		if (result->ai_family == AF_INET)
		{
			address.sin_port = htons(port);
			address.sin_family = family = AF_INET;
			address.sin_addr = ((struct sockaddr_in*)(result->ai_addr))->sin_addr;
		}
		else
			rc = -1;

		freeaddrinfo(result);
	}

	if (rc == 0)
	{
		n->my_socket = socket(family, type, 0);
		if (n->my_socket >= 0)
		{
			rc = connect(n->my_socket, (struct sockaddr*)&address, sizeof(address));
			
#ifdef _NOT_SUPPORT_JD_
			if(g_hf_config_file.mqtt_tls)
			{
				if(rc >= 0)
				{
					mqtt_ssl = mqtt_mbedtls_ssl_connect((void *)n->my_socket,NULL,0,NULL,0,NULL,0);
					if (mqtt_ssl == NULL){
						HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect failed\n");
					}
					else{
						HF_Debug(DEBUG_LEVEL_LOW, "SSL_connect successed ----------------------------------------\n");
						return rc;
					}
				}
				else
					HF_Debug(DEBUG_LEVEL_LOW, "connect failed %d\r\n",rc);
			}
			else
#endif
			{
				if(rc >= 0)
				{
					HF_Debug(DEBUG_LEVEL_LOW, "connect successed ----------------------------------------\n");
					return rc;
				}
				else
					HF_Debug(DEBUG_LEVEL_LOW, "connect failed %d\r\n",rc);
			}
		}
	}
	u_printf("close socket\r\n");
	close(n->my_socket);

	return -1;
}
