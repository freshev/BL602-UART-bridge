#ifndef HF_MCU_UPDATA_H
#define HF_MCU_UPDATA_H

#ifdef __cplusplus
extern "C"{
#endif

#include "hsf.h"


extern char mcu_ota_start_flag;
extern char mcu_ota_url[256];

uint8_t BCC_CheckSum(u8_t *buf, uint32_t len);
void send_mcu_file_len(char flag,char error_type);
void mcu_ota_thread(void);

#ifdef __cplusplus
}
#endif

#endif
