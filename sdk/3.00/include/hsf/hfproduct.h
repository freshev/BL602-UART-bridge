/* hfproduct.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_PRODUCT_H_
#define _HF_PRODUCT_H_

#ifdef __cplusplus
extern "C" {
#endif


#define PRODUCT_PARA_ADDR					0xD000


typedef struct _product_cmd
{
	const char * name;
	void	(*callhook)(int, char *);
} hfproduct_cmd_t,*phfproduct_cmd_t;


void HSF_IAPI hfproduct_init(void);
void HSF_IAPI hfproduct_read_mac(void);


#ifdef __cplusplus
}
#endif

#endif

