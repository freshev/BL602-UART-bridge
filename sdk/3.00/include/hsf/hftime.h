/* hftime.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_TIME_H_
#define _HF_TIME_H_

#ifdef __cplusplus
extern "C"{
#endif


#include <time.h>


#ifdef CONFIG_NO_STRUCT_TIMEZONE
struct timezone
{ 
	int tz_minuteswest;  
	int tz_dsttime;  
};
#endif


#if !CONFIG_HAVE_SETTIMEOFDAY
int settimeofday(const struct timeval * tv, const struct timezone *tz);
#endif

#if !CONFIG_HAVE_GETTIMEOFDAY
int gettimeofday(struct timeval * tv, struct timezone * tz);
#endif


#ifdef __cplusplus
}
#endif

#endif

