 /* hfble.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_BLE_H_
#define _HF_BLE_H_

#define HSF_API
#define HSF_IAPI HSF_API

#include <stdint.h>

typedef int (*hfble_callback_t)( uint32_t event,uint8_t *data,uint8_t len,uint8_t buf_len);

#define BLE_VER "1.02"
#define BLE_SEND_MTU_MAX_SIZE (247)
#define BLE_CONKEYLEN           16

enum BLE_RUN_MODE
{
	HF_BLE_RUN_THROUGHT_MODE,
	HF_BLE_RUN_DMS_MODE,
};

enum BLE_SEND_STATE
{
	HF_BLE_READY_SEND,
	HF_BLE_READY_SENDING,
};

enum BLE_NTF_STATE
{
	HF_BLE_READY_NTF,
	HF_BLE_NTFING,
};

enum BLE_IND_STATE
{
	HF_BLE_READY_IND,
	HF_BLE_INDING,
};

enum BLE_STATE
{
	HF_BLE_ADV = 1,
	HF_BLE_CONNECT,
	HF_BLE_CLOSE,
};

#define GAP_MAX_ADV_DATA_LEN              31u

typedef enum
{
	HFNET_BT_NTF_DATA_READY=20,
	HFNET_BT_NTF_DATA_ENABLE,
	HFNET_BT_NTF_DATA_DISENABLE,
	HFNET_BT_IND_DATA_READY,
	HFNET_BT_IND_DATA_ENABLE,
	HFNET_BT_IND_DATA_DISENABLE,
	HFNET_BT_CONNECTED,
	HFNET_BT_DISCONNECTED,
}hfble_event_id_t;

typedef struct
{
	/*GAP Advertisement Parameters which includes Flags, Service UUIDs and short name*/
	uint8_t      advData[GAP_MAX_ADV_DATA_LEN]; 
	/*length of the advertising data. This should be made zero if there is no data */
	uint8_t      advDataLen;
	/*GAP Advertisement Parameters which includes Flags, Service UUIDs and short name*/
	uint8_t      advrspData[GAP_MAX_ADV_DATA_LEN]; 
	/*length of the advertising data. This should be made zero if there is no data */
	uint8_t      advrspDataLen;	
	
} GAPP_DISC_DATA_T;

typedef struct
{
	uint8_t addr_type;
	uint8_t addr[6];
	int8_t rssi;
	uint8_t evtype;
	uint16_t len;
	uint8_t *data;

}BLE_SCAN_RESULT_ITEM,*PBLE_SCAN_RESULT_ITEM;

typedef int (*hfble_scan_callback_t)(PBLE_SCAN_RESULT_ITEM);


void HSF_IAPI hfble_stack_init();

void HSF_IAPI hfble_set_recv_callback(hfble_callback_t p_callback);


/**
 * @brief start ble operation.
 *
 * @param[in] NULL.
 * @return[out] the number of 0:success 1: fail.
 * @see None.
 * @note None.
 */
extern int32_t HSF_IAPI hf_start_ble();
/**
 * @brief start ble operation.
 *
 * @param[in] NULL.
 * @return[out] the number of 0:success 1: fail.
 * @see None.
 * @note None.
 */
extern int32_t HSF_IAPI hf_close_ble();

/**
 * @brief start ble scan until stop scan.
 *
 * @param[in] p_callback: pass ble scan result to this callback one by one
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfble_start_scan(hfble_scan_callback_t p_callback);

/**
 * @brief stop ble scan.
 *
 * @param[in] None
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfble_stop_scan(void);

void HSF_IAPI hf_ble_init_common_data(void);
uint32_t HSF_IAPI hf_ble_tp_notify_write(uint8_t *data, uint32_t len);
uint32_t HSF_IAPI hf_ble_tp_indicate_write(uint8_t *data, uint16_t len);
extern int32_t HSF_IAPI hf_get_ble_run_mode();
extern void HSF_IAPI hf_set_ble_run_mode(enum BLE_RUN_MODE mode);
extern int32_t HSF_IAPI hf_get_ble_ntf_state();
extern void HSF_IAPI hf_set_ble_ntf_state(enum BLE_NTF_STATE mode);
extern int32_t HSF_IAPI hf_get_ble_send_state();
extern void HSF_IAPI hf_set_ble_send_state(enum BLE_SEND_STATE mode);
extern int32_t HSF_IAPI hf_get_ble_conn_state();
extern void HSF_IAPI hf_set_ble_conn_state(enum BLE_STATE mode);
extern void HSF_IAPI hf_set_ble_fast_send_add();
extern void HSF_IAPI hf_set_ble_fast_send_cut();
extern int32_t HSF_IAPI hf_get_ble_fast_send_count();
extern void HSF_IAPI hfble_ind_set_recv_callback(hfble_callback_t p_callback);
extern void HSF_IAPI hf_ble_ind_init_common_data();
extern int32_t HSF_IAPI hf_get_ble_ind_state();
extern int32_t HSF_IAPI hf_get_ble_ind_state();
extern void HSF_IAPI hf_set_ble_ind_state(enum BLE_NTF_STATE mode);
extern int32_t HSF_IAPI hf_get_ble_ind_send_state();
extern void HSF_IAPI hf_set_ble_ind_send_state(enum BLE_SEND_STATE mode);
extern void HSF_IAPI hfble_ind_set_recv_callback(hfble_callback_t p_callback);
extern int HSF_API hf_read_bt_mac_address(uint8_t *mac);
extern void HSF_IAPI hfbleconkey_check(char *data,int len);
extern void HSF_IAPI hfble_connect_enable_timer();
extern int HSF_IAPI hf_ble_start_switch();
extern int HSF_IAPI hf_ble_get_mtu(void);


#endif

