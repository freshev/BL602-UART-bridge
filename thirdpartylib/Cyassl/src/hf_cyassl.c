/*
 * Copyright (C) 2014-2022, High-flying International Ltd.
 * All Rights Reserved.
 */

/** hf_cyassl.c
 */
#include "hsf.h"
#include <string.h>
#include <cyassl/openssl/ssl.h>
#include <cyassl/cyassl_config.h>
#include <cyassl/ctaocrypt/memory.h>

 typedef struct memoryStats {
        size_t totalAllocs;     /* number of allocations */
        size_t totalBytes;      /* total number of bytes allocated */
        size_t peakBytes;       /* concurrent max bytes */
        size_t currentBytes;    /* total current bytes in use */
    } memoryStats;
	
static memoryStats ourMemStats;

typedef struct memHint {
    size_t thisSize;      /* size of this memory */
    void*  thisMemory;    /* actual memory for user */
} memHint;
	
static void *cyassl_mem_malloc(size_t size)
{
	memHint* mt;
	if (size == 0)
		return NULL;

	mt = (memHint*)hfmem_malloc(sizeof(memHint) + size);
	if (mt == NULL)
	{
		HF_Debug(DEBUG_SSL,"failed to allocate mem[%d] for CyaSSL, have malloced [%d]", size, ourMemStats.currentBytes);
		return NULL;
	}
	mt->thisSize   = size;
	mt->thisMemory = (char *)mt + sizeof(memHint);

	ourMemStats.totalAllocs++;
	ourMemStats.totalBytes   += size;
	ourMemStats.currentBytes += size;
	if (ourMemStats.currentBytes > ourMemStats.peakBytes)
		ourMemStats.peakBytes = ourMemStats.currentBytes;

	//if(size>500)
		//HF_Debug(DEBUG_SSL,"###   cyassl_mem_malloc big******[%d],current[%d] peek[%d]\n",size,(unsigned long)ourMemStats.currentBytes,(unsigned long)ourMemStats.peakBytes);
	
	return mt->thisMemory;
}

static void cyassl_mem_free(void *buffer)
{
	if (buffer == NULL)
		return;

	memHint* mt;
	mt = (memHint*)((char *)buffer - sizeof(memHint));
	ourMemStats.currentBytes -= mt->thisSize; 

	//if(mt->thisSize>500)
		//HF_Debug(DEBUG_SSL,"###   cyassl_mem_free big------[%d], current[%d]\n",mt->thisSize, (unsigned long)ourMemStats.currentBytes);
	
	hfmem_free(mt);
}

static void *cyassl_mem_realloc(void *buffer, size_t size)
{
	 void* ret = cyassl_mem_malloc(size);
	 memHint* mt;
	
        if (buffer) {
            /* if realloc is bigger, don't overread old ptr */
            mt = (memHint*)((char*)buffer - sizeof(memHint));

            if (mt->thisSize < size)
                size = mt->thisSize;
        }

        if (ret && buffer)
            memcpy(ret, buffer, size);

	//if((size - mt->thisSize)>100 )
		//HF_Debug(DEBUG_SSL,"###   cyassl_mem_realloc big******[%d],current[%d] peek[%d]\n",size - mt->thisSize,(unsigned long)ourMemStats.currentBytes,(unsigned long)ourMemStats.peakBytes);
	
	if (ret)
		cyassl_mem_free(buffer);

    return ret;
}

void InitMemoryTracker(void) 
{
	ourMemStats.totalAllocs  = 0;
	ourMemStats.totalBytes   = 0;
	ourMemStats.peakBytes    = 0;
	ourMemStats.currentBytes = 0;
}

void ShowMemoryTracker(void) 
{
	HF_Debug(DEBUG_SSL,"total     	Allocs 	= %9lu\n",(unsigned long)ourMemStats.totalAllocs);
	HF_Debug(DEBUG_SSL,"total     	Bytes  	= %9lu\n",(unsigned long)ourMemStats.totalBytes);
	HF_Debug(DEBUG_SSL,"peak    	Bytes  	= %9lu\n",(unsigned long)ourMemStats.peakBytes);
	HF_Debug(DEBUG_SSL,"current 	ytes  	= %9lu\n",(unsigned long)ourMemStats.currentBytes);
}

void hf_set_cyassl_mem_fun(void)
{
	char set_cyassl_func=0;
	if(set_cyassl_func==0)
	{
		CyaSSL_SetAllocators(cyassl_mem_malloc, cyassl_mem_free,cyassl_mem_realloc);
		set_cyassl_func=1;
	}
}
