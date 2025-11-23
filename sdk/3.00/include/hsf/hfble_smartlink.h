 /* hfble_smartlink.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_BLE_SMARTLINK_H_
#define _HF_BLE_SMARTLINK_H_

#include "hsf.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BLE_DEBUG
#ifdef BLE_DEBUG
#define ble_debug(fmt, ...)   u_printf(fmt, ##__VA_ARGS__)
#else
#define ble_debug(ftm, ...)
#endif

#define AOS_WAIT_FOREVER 0xffffffffu

#define BLE_CONFIG_CMD_READY 	 "ready"
#define BLE_CONFIG_CMD_SUCCESS	 "config_success"
#define BLE_CONFIG_CMD_FAIL 	 "config_fail"
#define BLE_CONFIG_CMD_ACK		 "config_ack"

#define BLE_CONFIG_FAIL_PW		"password"
#define BLE_CONFIG_FAIL_NAP		"apNotExist"
#define BLE_CONFIG_FAIL_OTHER	"error"

#define SMKFIND_BU		1
#define SMKFIND_U		2
#define SMKFIND_B		3

#define BLE_CONFIG_CMD_SEND_TO_APP_COUNT_MAX 	120
#define BLE_CONFIG_CMD_SEND_FIND_COUNT_MAX 	40

#define BLE_LIST_MSG_MAX_NUM	20

typedef enum
{
	CONFIG_STATUS_NONE,
	CONFIG_STATUS_START,
	CONFIG_STATUS_EXCHANGE,
	CONFIG_STATUS_SUCCESSS,
	CONFIG_STATUS_FIND_START,
	CONFIG_STATUS_FIND_END,
	CONFIG_STATUS_FAIL
}BLE_CONFIG_STATUS;

typedef struct
{
	unsigned char pkt_no;
	unsigned char dataLen;
	char *data;

} BLE_MSG_NODE_BODY;

typedef struct ble_msg_node
{
	BLE_MSG_NODE_BODY nodeBody;
	struct ble_msg_node* pNodeNext;
} BLE_MSG_NODE;

typedef struct
{
	unsigned char noteCount;
	unsigned char noteRecvNum;
	BLE_MSG_NODE* firstNodePtr;
} BLE_LIST_HEADER;


void HSF_IAPI hfble_btlink_start(void);

int HSF_IAPI hfble_btlink_response(void);

void HSF_IAPI hfble_btlink_handle(void);

void HSF_IAPI hfble_set_send_ack_callback(hfble_callback_t p_callback);


/**
 * @brief check whether or not in ble link.
 *
 * @param[in] None
 * @return[out] 0-not in ble link, 1-in ble link
 * @see None.
 * @note None.
 */
int HSF_API hfble_btlink_is_start(void);
int hf_aec256ccm_decrypt_func(unsigned char* data,int data_len,unsigned char *deviceKey,unsigned char *confirm);
int HSF_API hfble_in_btlink(void);


#ifdef __cplusplus
}
#endif

#endif

