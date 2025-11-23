/************************************************************
 *File : joylink_ota.c
 *Auth : jd
 *Date : 2018/07/25
 *Mail : 
 ***********************************************************/

// joylink platform layer header files
#include "joylink_stdint.h"
#include "joylink_stdio.h"
#include "joylink_string.h"
#include "joylink_memory.h"
#include "joylink_time.h"
#include "joylink_thread.h"
#include "joylink_log.h"

#include "joylink.h"

#include "joylink_extern.h"
#include "joylink_extern_ota.h"
#include <hsf.h>

void joylink_parse_url(char *url ,char *joylink_url ,char *joylink_host);
void joylink_https_ota(char *url,char *host);

static JLOtaOrder_t otaOrder;

//-----------------------------------------------------------------------

int joylink_ota_report_status(int status, int progress, char *desc)
{
	JLOtaUpload_t otaUpload;

	jl_platform_strncpy(otaUpload.feedid, otaOrder.feedid, JL_MAX_FEEDID_LEN);
	jl_platform_strncpy(otaUpload.productuuid, otaOrder.productuuid, JL_MAX_UUID_LEN);

	otaUpload.status = status;

	// log_info("status: %d\n", status);

	otaUpload.progress = progress;
	jl_platform_strncpy(otaUpload.status_desc, desc, JL_MAX_STATUS_DESC_LEN);

	joylink_server_ota_status_upload_req(&otaUpload);
    return 0;
}

void joylink_ota_task(void *data)
{
    char *filename = NULL;

	char url_data[256];
	char url_host[128];

    // 初始化CRC

    log_info("\n\nJoylink ota start!\n");

    log_info("\nserial:%d | feedid:%s | productuuid:%s | version:%d | versionname:%s | crc32:%08X | url:%s | upgradetype:%d\n\n",\
        otaOrder.serial, otaOrder.feedid, otaOrder.productuuid, otaOrder.version,\
        otaOrder.versionname, otaOrder.crc32, otaOrder.url, otaOrder.upgradetype);

    filename = strrchr(otaOrder.url, '/') + 1;
    log_info("url: %s name: %s", otaOrder.url, filename);

	memset(url_data, 0 ,256);
	memset(url_host, 0 ,128);
	joylink_parse_url(otaOrder.url,url_data,url_host);

	u_printf("\r\nurl_data %s\r\n url_host %s \r\n",url_data,url_host);
	
    joylink_https_ota(url_data,url_host);	

    return NULL;
}

//-----------------------------------------------------------------------
void joylink_set_ota_info(JLOtaOrder_t *ota_info)
{
	jl_platform_memset(&otaOrder, 0, sizeof(JLOtaOrder_t));
	jl_platform_memcpy(&otaOrder, ota_info, sizeof(JLOtaOrder_t));
}
