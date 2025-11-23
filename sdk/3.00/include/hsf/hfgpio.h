 /* hfgpio.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_GPIO_H_
#define _HF_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef void (*hfgpio_interrupt_func)(uint32_t irq, uint32_t fid);

#define HFM_PIN_NUMBER		(32+1)

#define HFM_TYPE_LPT270		0
#define HFM_TYPE_LPT170		1
#define HFM_TYPE_LPT570		2
#define HFM_TYPE_LPT271		3
#define HFM_TYPE_LPB170		4
#define HFM_TYPE_LPB175		5
#define HFM_TYPE_LPT272		6


#define HFM_MAX_FUNC_CODE	(HFM_PIN_NUMBER*3)

enum HF_GPIO_FUNC_E
{
	//////fix/////////////////////
	HFGPIO_F_JTAG_TCK=0,
	HFGPIO_F_JTAG_TDO=1,
	HFGPIO_F_JTAG_TDI,
	HFGPIO_F_JTAG_TMS,
	HFGPIO_F_USBDP,
	HFGPIO_F_USBDM,
	HFGPIO_F_UART0_TX,
	HFGPIO_F_UART0_RTS,
	HFGPIO_F_UART0_RX,
	HFGPIO_F_UART0_CTS,
	HFGPIO_F_SPI_MISO,
	HFGPIO_F_SPI_CLK,
	HFGPIO_F_SPI_CS,
	HFGPIO_F_SPI_MOSI,
	HFGPIO_F_UART1_TX,
	HFGPIO_F_UART1_RTS,
	HFGPIO_F_UART1_RX,
	HFGPIO_F_UART1_CTS,
	////////////////////////////////
	HFGPIO_F_NLINK,
	HFGPIO_F_NREADY,
	HFGPIO_F_NRELOAD,
	HFGPIO_F_SLEEP_RQ,
	HFGPIO_F_SLEEP_ON,
	HFGPIO_F_WPS,
#ifdef CONFIG_SPI_ETHERNET
	HFGPIO_F_PHY_INTR,
#else
	HFGPIO_F_RESERVE1,
#endif
	HFGPIO_F_RESERVE2,
	HFGPIO_F_RESERVE3,
	HFGPIO_F_RESERVE4,
	HFGPIO_F_RESERVE5,
	HFGPIO_F_USER_DEFINE
};

#define F_GPI			(0x00010000)
#define F_GPO			(0x00020000)
//GND
#define F_GND			(0x00040000)
//vcc
#define F_VCC			(0x00100000)
#define F_NC			(0x00200000)
//use to system reset
#define F_RST			(0x00400000)
//use to interrupt input pin
#define F_IT			(0x00800000|F_GPI)

#define F_GPIO			(F_GPI|F_GPO)

#define F_PWM			(0x01000000)
#define F_PWM0			F_PWM
#define F_PWM1			F_PWM
#define F_PWM2			F_PWM
#define F_PWM3			F_PWM
#define F_PWM4			F_PWM

#define F_ADC			(0x02000000)

#define HFM_NOPIN			(0)
#define HFM_PIN1			(F_GPIO|F_IT|F_PWM0|1)
#define HFM_PIN2			(F_GPIO|F_IT|F_PWM1|2)
#define HFM_PIN3			(F_GPIO|F_IT|F_PWM2|3)
#define HFM_PIN4			(F_GPIO|F_IT|F_PWM3|4)
#define HFM_PIN5			(F_GPIO|F_IT|F_PWM4|F_ADC|5)
#define HFM_PIN6			(F_GPIO|F_IT|F_PWM0|F_ADC|6)
#define HFM_PIN7			(F_VCC|7)
#define HFM_PIN8			(F_VCC|8)
#define HFM_PIN9			(F_NC|9)
#define HFM_PIN10			(F_NC|10)
#define HFM_PIN11			(F_NC|11)
#define HFM_PIN12			(F_NC|12)
#define HFM_PIN13			(F_NC|13)
#define HFM_PIN14			(F_NC|14)
#define HFM_PIN15			(F_NC|15)
#define HFM_PIN16			(F_GPIO|F_IT|F_PWM2|16)
#define HFM_PIN17			(F_GPIO|F_IT|F_PWM3|17)
#define HFM_PIN18			(F_NC|18)
#define HFM_PIN19			(F_NC|19)
#define HFM_PIN20			(F_GPIO|F_IT|F_PWM1|F_ADC|20)
#define HFM_PIN21			(F_GPIO|F_IT|F_PWM2|F_ADC|21)
#define HFM_PIN22			(F_GPIO|F_IT|F_PWM4|F_ADC|22)
#define HFM_PIN23			(F_VCC|23)
#define HFM_PIN24			(F_VCC|24)
#define HFM_PIN25			(F_VCC|25)
#define HFM_PIN26			(F_VCC|26)
#define HFM_PIN27			(F_GPIO|F_IT|F_PWM1|27)
#define HFM_PIN28			(F_GPIO|F_IT|F_PWM2|28)
#define HFM_PIN29			(F_GPIO|F_IT|F_PWM0|29)
#define HFM_PIN30			(F_GPIO|F_IT|F_PWM1|30)
#define HFM_PIN31			(F_GPIO|F_IT|F_PWM2|31)
#define HFM_PIN32			(F_VCC|32)


#define LPX70_GPIO0			HFM_PIN1
#define LPX70_GPIO1			HFM_PIN2
#define LPX70_GPIO3			HFM_PIN4
#define LPX70_GPIO4			HFM_PIN5
#define LPX70_GPIO5			HFM_PIN6
#define LPX70_GPIO7			HFM_PIN16
#define LPX70_GPIO11		HFM_PIN20
#define LPX70_GPIO12		HFM_PIN21
#define LPX70_GPIO14		HFM_PIN22
#define LPX70_GPIO16		HFM_PIN27
#define LPX70_GPIO17		HFM_PIN28
#define LPX70_GPIO20		HFM_PIN29
#define LPX70_GPIO21		HFM_PIN30
#define LPX70_GPIO22		HFM_PIN31


#define HF_M_PINNO(_pin)	((_pin)&0xFF)

#define HFM_VALID_PINNO(_pinno)	((_pinno)>0&&(_pinno)<=HFM_PIN_NUMBER)

#define HF_M_PIN(_no)		HFM_PIN##_no

/*  Default pin configuration (no attribute). */
#define HFPIO_DEFAULT               (0u << 0)
#define HFPIO_PULLUP			     (1u << 2)
#define HFPIO_PULLDOWN                  (1u << 3)

/*  Low level interrupt is active */
#define HFPIO_IT_LOW_LEVEL          	(1u<<4)
/*  High level interrupt is active */
#define HFPIO_IT_HIGH_LEVEL	    		(1u<<5)
/*  Falling edge interrupt is active */
#define HFPIO_IT_FALL_EDGE            	(1u<<6)
/*  Rising edge interrupt is active */
#define HFPIO_IT_RISE_EDGE             	(1u<<7)
/*Interrupt Edge detection is active.*/
#define HFPIO_IT_EDGE			    	(1u<<8)

#define HFPIO_TYPE_Pos                	27
/* PIO Type Mask */
#define HFPIO_TYPE_Msk                	(0x7u << HFPIO_TYPE_Pos)

/*   The pin is an input. */
#define HFM_IO_TYPE_INPUT       (0x01 << HFPIO_TYPE_Pos)
/*   The pin is an output and has a default level of 0.*/
#define HFM_IO_OUTPUT_0          (0x02 << HFPIO_TYPE_Pos)
/*   The pin is an output and has a default level of 1.*/
#define HFM_IO_OUTPUT_1          (0x04 << HFPIO_TYPE_Pos)
#define HFPIO_DS				  (0x8u << HFPIO_TYPE_Pos)


void HSF_IAPI hfgpio_init(void);

int HSF_IAPI hfgpio_get_pid(int gpio);

int HSF_IAPI hfgpio_get_chip_pin(int fid);

int HSF_IAPI hfgpio_configure_pin(int pid,int flags);

int HSF_IAPI hfgpio_pin_is_high(int pid);

int HSF_IAPI hfgpio_fpin_add_feature(int fid,int flags);

int HSF_IAPI hfgpio_fpin_clear_feature(int fid,int flags);

void HSF_IAPI hfgpio_gpio_test_enable(int enable);

void HSF_IAPI hfgpio_set_nlink_pin(int val);

void HSF_IAPI hfgpio_set_nready_pin(int val);

int HSF_IAPI hfgpio_reload_pin_is_low(void);

#define  hfgpio_set_out_high(pid)	hfgpio_configure_pin(pid,HFPIO_DEFAULT|HFM_IO_OUTPUT_1)

#define  hfgpio_set_out_low(pid)	hfgpio_configure_pin(pid,HFPIO_DEFAULT|HFM_IO_OUTPUT_0)


/**
 * @brief check the validity of hf_gpio_fid_to_pid_map_table.
 *
 * @param[in] type: the module type, as follows
 * ==========================================
 * | HFM_TYPE_LPT270                        |
 * |----------------------------------------|
 * | HFM_TYPE_LPT170                        |
 * |----------------------------------------|
 * | HFM_TYPE_LPT271                        |
 * |----------------------------------------|
 * | HFM_TYPE_LPB170                        |
 * |----------------------------------------|
 * | HFM_TYPE_LPB175                        |
 * ==========================================
 * @return[out] HF_SUCCESS-successfully, other value is have multiple functions in the same pin
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_fmap_check(int type);

/**
 * @brief set the configure parameters of pin by the function id.
 *
 * @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 *			 flags: the flag of pin, as follows, can be used together, such as: HFPIO_DEFAULT|HFM_IO_TYPE_INPUT
 * ==========================================
 * | HFPIO_DEFAULT                          |
 * |----------------------------------------|
 * | HFM_IO_TYPE_INPUT                      |
 * |----------------------------------------|
 * | HFM_IO_OUTPUT_0                        |
 * |----------------------------------------|
 * | HFM_IO_OUTPUT_1                        |
 * ==========================================
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal, HF_E_ACCES-not allowed
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_configure_fpin(int fid, int flags);

/**
 * @brief get the configure parameters of pin by the function id.
 *
 * @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] the configure parameters of pin
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_fconfigure_get(int fid);

/**
 * @brief set the pin to high level by the function id.
 *
 * @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal
 * @see None.
 * @note None.
 */
#define hfgpio_fset_out_high(fid)	hfgpio_configure_fpin(fid,HFPIO_DEFAULT|HFM_IO_OUTPUT_1)

/**
 * @brief set the pin to low level by the function id.
 *
 * @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal
 * @see None.
 * @note None.
 */
#define hfgpio_fset_out_low(fid)	hfgpio_configure_fpin(fid,HFPIO_DEFAULT|HFM_IO_OUTPUT_0)

/**
 * @brief configure the interrupt of pin by the function id.
 *
* @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 *			 flags: the interrupt type, as follows
 * ==========================================
 * | HFPIO_IT_LOW_LEVEL                     |
 * |----------------------------------------|
 * | HFPIO_IT_HIGH_LEVEL                    |
 * |----------------------------------------|
 * | HFPIO_IT_FALL_EDGE                     |
 * |----------------------------------------|
 * | HFPIO_IT_RISE_EDGE                     |
 * ==========================================
 *			 handle: a function pointer, called back when trigger
 *			 enable: enable or disable to trigger
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal, HF_E_ACCES-not allowed
 * @see None.
 * @note None.	Timers cannot be used during interrupts
 */
int HSF_API hfgpio_configure_fpin_interrupt(int fid, uint32_t flags, hfgpio_interrupt_func handle, int enable);

/**
 * @brief enable interrupt of pin by the function id.
 *
* @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal
 * @see None.
 * @note None.	Timers cannot be used during interrupts
 */
int HSF_API hfgpio_fenable_interrupt(int fid);

/**
 * @brief disable interrupt of pin by the function id.
 *
* @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed, HF_E_INVAL-illegal
 * @see None.
 * @note None.	Timers cannot be used during interrupts
 */
int HSF_API hfgpio_fdisable_interrupt(int fid);

/**
 * @brief disable interrupt of all pins by the function id.
 *
* @param[in] fid:None
 * @return[out] HF_SUCCESS-successfully, HF_FAIL-failed
 * @see None.
 * @note None.	Timers cannot be used during interrupts
 */
int HSF_API hfgpio_disabel_all_interrupt(void);

/**
 * @brief check the level of the pin to be high by the function id.
 *
* @param[in] fid: the function id define by table 'hf_gpio_fid_to_pid_map_table'
 * @return[out] >=1 high level, <=0 low level or illegal
 * @see None.
 * @note effective in output mode and input mode.
 */
int HSF_API hfgpio_fpin_is_high(int fid);

/**
 * @brief check whether or not in GPIO test mode .
 *
 * @param[in] None
 * @return[out] 0-not in test mode, 1-in test mode
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_gpio_test_is_running(void);

/**
 * @brief stop PWM.
 *
 * @param[in] fid: the function id of gpio
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_pwm_disable(int fid);

/**
 * @brief start PWM.
 *
 * @param[in] fid: the function id of gpio
 *			 freq: the frequency of PWM, the range is [100-800000]
 *			 hrate: the duty cycle of PWM, the range is [0-100], 0 means low, 100 means high
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note the same PWM channel cannot be used at the same time.
 */
int HSF_API hfgpio_pwm_enable(int fid, int freq, int hrate);

/**
 * @brief start PWM.
 *
 * @param[in] fid: the function id of gpio
 *			 freq: the frequency of PWM, max is 20000000
 *			 percent: high level ratio, accurate 0.0001
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note the same PWM channel cannot be used at the same time.
 */
int HSF_API hfgpio_pwm_enable_ex(int fid, int freq, float percent);

/**
 * @brief start ADC.
 *
 * @param[in] fid: the function id of gpio
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_adc_enable(int fid);

/**
 * @brief get ADC value.
 *
 * @param[in] fid: the function id of gpio
 * @return[out] 
 			<0-failed
 			>=0-the value of ADC, [0-3200] indicate [0V-3.2V]
 * @see None.
 * @note None.
 */
int HSF_API hfgpio_adc_get_value(int fid);

/**
 * @brief init infrared function.
 *
 * @param[in] fid: the function id of gpio
 * @see None.
 * @note None.
 */
void HSF_API hf_ir_init(int fid);
/**
 * @brief infrared enable.
 *
 * @param[in] fid: the function id of gpio
 * @see None.
 * @note None.
 */
void HSF_API hf_ir_enable(void);
/**
 * @brief infrared disable.
 *
 * @param[in] fid: the function id of gpio
 * @see None.
 * @note None.
 */
void HSF_API hf_ir_disable(void);

#ifdef __cplusplus
}
#endif

#endif

