/* hfflashlayout.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _HF_FLASH_LAYOUT_H_
#define _HF_FLASH_LAYOUT_H_


#define CONFIG_FLASH_SIZE_2MB
#define CONFIG_FLASH_SIZE					(1024*1024*2)

#define BOOT_ADDRESS						0x00000000
#define BOOT_SIZE							(68*1024)
#define SOFTWARE_CODE_ADDRESS			0x00011000
#define MAX_SOFTWARE_CODE_SIZE			(916*1024)
#define UPGRADE_ADDRESS					0x000F6000
#define MAX_UPGRADE_FILE_SIZE				(560*1024)
#define WEB_ADDRESS						0x00182000
#define WEB_ADDRESS_END					0x001B4000
#define UFLASH_ADDRESS						0x001B4000
#define HFUFLASH_SIZE						(200*1024)
#define UFLASH1_ADDRESS					0x0
#define HFUFLASH1_SIZE						(0*1024)
#define BOOT_CONFIG						0x001E6000 
#define SECU_FLASH_ADDR					0x001E7000
#define USERPAGE							0x001E8000
#define USERPAGE_BACKUP					0x001E9000
#define F_SETTING_ADDRESS					0x001EA000
#define TEMP_FLASH_ADDRESS				0x001EB000
#define USER_BIN_FILE_OFFSET				0x001EC000
#define USER_BIN_FILE_SIZE					(4*1024)
#define USER_BIN_FILE_BAK_OFFSET			0x001ED000


//#define NOT_SUPPORT_HTTPC_THREAD
//#define NOT_SUPPORT_MQTT_THREAD

#endif

