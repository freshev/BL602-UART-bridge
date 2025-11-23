 /* httpd.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HTTPD_H_
#define _HTTPD_H_

#ifdef __cplusplus
extern "C"{
#endif


int hfhttpd_para_nvget(char *cfg_name,int name_len, char *value, int valu_len);

int hfhttpd_para_nvset(char *cfg_name,int name_len, char *value, int value_len);


#ifdef __cplusplus
}
#endif

#endif

