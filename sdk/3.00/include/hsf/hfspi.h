/* hfspi.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_SPI_H_
#define _HF_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif


#define HFSPI_MODE_CPOL0_CPHA0		(0)     //L1
#define HFSPI_MODE_CPOL0_CPHA1		(1)     //L2
#define HFSPI_MODE_CPOL1_CPHA0		(2)     //H1
#define HFSPI_MODE_CPOL1_CPHA1		(3)     //H2

/**
 * @brief init SPI master mode.
 *
 * @param[in] mode: SPI mode,HFSPI_MODE_CPOL0_CPHA0/HFSPI_MODE_CPOL0_CPHA1/HFSPI_MODE_CPOL1_CPHA0/HFSPI_MODE_CPOL1_CPHA1(clock polarity, phase, and shift direction)
 *			 clk: SPI frequency, 312.5K-20M, in Hz
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None
 * @note None
 */
int HSF_API hfspi_master_init(int mode, uint32_t clk);

/**
 * @brief SPI master send data.
 *
 * @param[in] buf: send data buf
 *			 length: send data length, max is 2048
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None
 * @note None
 */
int HSF_API hfspi_master_send_data(unsigned char* buf, unsigned int length);

/**
 * @brief SPI master recv data.
 *
 * @param[in] buf: recv data buf
 *			 length: recv data length, max is 2048
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfspi_master_recv_data(unsigned char* buf, unsigned int length);

/**
 * @brief SPI master send and recv data.
 *
 * @param[in] buf: recv data buf
 *			 length: recv data length, max is 2048
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfspi_master_send_and_recv_data(unsigned char* send_buf, unsigned char* recv_buf, unsigned int length);


/**
 * @brief free SPI master.
 *
 * @param[in] none
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None
 */
int HSF_API hfspi_master_free(void);


#ifdef __cplusplus
}
#endif

#endif

