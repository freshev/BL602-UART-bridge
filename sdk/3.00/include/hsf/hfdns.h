/* hfdns.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_DNS_H_
#define _HF_DNS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief start Domain Name Serve and create a dns record.
 *
 * @param[in] name: domain name, <128 bytes
 *			 ip: the ip address of domain, if 0 mean use the ip of module in AP mode
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note this function will use a UDP pcb
 */
int HSF_API hfdns_start_server(char *name, unsigned int ip);

/**
 * @brief stop Domain Name Serve.
 *
 * @param[in] none
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfdns_stop_server(void);

/**
 * @brief add a dns record.
 *
 * @param[in] name: domain name, <128 bytes
 *			 ip: the ip address of domain, if 0 mean use the ip of module in AP mode
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfdns_addr_record(char *name, unsigned int ip);

/**
 * @brief remove a dns record.
 *
 * @param[in] name: domain name
 * @return[out] 0-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfdns_remove_record(char *name);


#ifdef __cplusplus
}
#endif

#endif

