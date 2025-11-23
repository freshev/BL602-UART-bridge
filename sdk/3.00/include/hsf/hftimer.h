/* hftimer.h
 *
 * Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.
 *
 * This file is part of HSF.
 *
 */

#ifndef _HF_TIMER_H_
#define _HF_TIMER_H_

#ifdef __cplusplus
extern "C"{
#endif


#define HFTIMER_FLAG_HARDWARE_TIMER				(0x00000001)


typedef void * hftimer_handle_t;
/* Define the prototype to which timer callback functions must conform. */
typedef void (*hf_timer_callback)( hftimer_handle_t htimer );


int HSF_IAPI hftimer_init(void);
 
/**
 * @brief create a timer.
 *
 * @param[in] name: no use
 *			 period: the period of timer, software timer is in milliseconds, hardware timer is in microsecond range is [1000-1000000]
 *			 auto_reload: when timer expired whether or not restart
 *			 timer_id: timer id, use to distinguish different timers
 *			 p_callback: timer callback function pointer
 *			 flags: 0 is software timer, HFTIMER_FLAG_HARDWARE_TIMER is hardware timer
 * @return[out] the handle of timer, if NULL mean create failed
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
hftimer_handle_t HSF_API hftimer_create( const char *name, int32_t period, bool auto_reload,uint32_t  timer_id, hf_timer_callback p_callback,uint32_t flags );

/**
 * @brief get timer id.
 *
 * @param[in] htimer: the handle of timer
 * @return[out] timer id
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
uint32_t HSF_API hftimer_get_timer_id( hftimer_handle_t htimer );

/**
 * @brief delete timer.
 *
 * @param[in] htimer: the handle of timer
 * @return[out] None
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
void HSF_API hftimer_delete(hftimer_handle_t htimer);

/**
 * @brief start timer.
 *
 * @param[in] htimer: the handle of timer
 * @return[out] HF_SUCCESS-successfully, other value is failed
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
int HSF_API hftimer_start(hftimer_handle_t htimer);

/**
 * @brief stop timer.
 *
 * @param[in] htimer: the handle of timer
 * @return[out] None
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
void HSF_API hftimer_stop(hftimer_handle_t htimer);

/**
 * @brief change the period of timer.
 *
 * @param[in] htimer: the handle of timer
 *			 new_period: the new period of timer, software timer is in milliseconds, hardware timer is in microsecond
 * @return[out] None
 * @see None.
 * @note None.  Cannot be used in interrupts
 */
void HSF_API hftimer_change_period(hftimer_handle_t htimer, int32_t new_period);


#ifdef __cplusplus
}
#endif

#endif

