/* hfupdate.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */
 
#ifndef _HF_UPDATE_H_
#define _HF_UPDATE_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef enum HFUPDATE_TYPE
{
	HFUPDATE_SW=0,
	HFUPDATE_CONFIG=1,
	HFUPDATE_WIFIFW,
	HFUPDATE_WEB,
}HFUPDATE_TYPE_E;


int HSF_IAPI hfupdate_auto_upgrade(uint32_t flags);

int HSF_IAPI hfupdate_auto_upgrade_default(void);

int HSF_IAPI http_download_enable_range(char enable);

int HSF_IAPI hfupdate_auto_upgrade_start(void);

int HSF_IAPI hfupdate_auto_upgrade_start(void);

int HSF_IAPI hfupdate_auto_upgrade_is_running(void);

int HSF_IAPI check_webpage_file_ok(char *addr, char *version);


/**
 * @brief start OTA to update application.
 *
 * @param[in] type: update type, now only support 'HFUPDATE_SW' & 'HFUPDATE_WEB'
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note this function will need time to erase flash.
 */
int HSF_API hfupdate_start(HFUPDATE_TYPE_E type);

/**
 * @brief write update file.
 *
 * @param[in] type: update type, now only support 'HFUPDATE_SW' & 'HFUPDATE_WEB'
 *			 offset: offset address, start from 0
 *			 data: a pointer to data
 *			 len: the len of data
 * @return[out] the length of write success
 * @see None.
 * @note this function will need some time to erase flash.
 */
int HSF_API hfupdate_write_file(HFUPDATE_TYPE_E type, uint32_t offset, uint8_t *data, int len);

/**
 * @brief complete update.
 *
 * @param[in] type: update type, now only support 'HFUPDATE_SW' & 'HFUPDATE_WEB'
 *			 file_total_len: the len of file
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note return -1 means file type error, return -2 means file crc error.
 */
int HSF_API hfupdate_complete(HFUPDATE_TYPE_E type, uint32_t file_total_len);

/**
 * @brief download OTA file use http.
 *
 * @param[in] purl: http url
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfupdate_fw_as_http(const char *purl);

/**
 * @brief get bootloader version.
 *
 * @param[in] version: the buffer to store bootloader version
 * @return[out] the crc32 of bootloader, 0 is failed
 * @see None.
 * @note None.
 */
unsigned int HSF_API hfupdate_read_boot_ver(char *version);

/**
 * @brief check whether or not in updating
 *
 * @param[in] None
 * @return[out] 0-not in updating, 1-in updating
 * @see None.
 * @note None.
 */
int HSF_API hfupdate_auto_upgrade_is_running(void);

/**
 * @brief download file use http
 *
 * @param[in] purl: http url
 *			 p_data: a buffer or a flash address to store update file
 *			 len: the len of p_data
 * @return[out] < 0 is fail, >0 is success, the size of file
 * @see None.
 * @note None.
 */
int HSF_API http_download_file(const char *purl,char *p_data,uint32_t len, int start_range, int *file_len);


#ifdef __cplusplus
}
#endif

#endif

