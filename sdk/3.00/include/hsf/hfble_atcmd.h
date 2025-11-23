 /* hfble_atcmd.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HFBLE_ATCMD_H_
#define _HFBLE_ATCMD_H_

#ifdef __cplusplus
extern "C"{
#endif


#define HF_DMS_BLE_NAME_STRINGS "AZ"


enum CONFIG_BLE_CONENABLE
{
	CONFIG_BLE_CONENABLE_OFF	= 0x00,
	CONFIG_BLE_CONENABLE_ON
};


int HSF_IAPI hfble_config_get_name(uint8_t *name);


#ifdef __cplusplus
}
#endif

#endif

