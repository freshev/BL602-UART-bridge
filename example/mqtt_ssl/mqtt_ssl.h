/* mqtt_ssl.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _MQTT_SSL_H_
#define _MQTT_SSL_H_

#ifdef __cplusplus
extern "C"{
#endif

#define MBEDTLS_SSL_ENABLE

#define MQTT_SERVER_ADDR "a17q8xcqcnhjj-ats.iot.ap-southeast-2.amazonaws.com"
#define MQTT_SERVER_PORT 8883

#define MQTT_CLIENT_ID  "8899"

/*
*name:	void start_mqtt_ssl_test(void)
*Para:	none
*return:	none
*/
void start_mqtt_ssl_test(void);


#ifdef __cplusplus
}
#endif

#endif

