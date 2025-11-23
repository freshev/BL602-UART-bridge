#include <stddef.h>
#include <stdint.h>

#include <time.h>
#include <sys/time.h>
#include <hsf.h>

#include "joylink_stdio.h"
#include "joylink_time.h"

extern unsigned int jd_sys_time;

/**
 * 初始化系统时间
 *
 * @return: 0 - success or -1 - fail
 *
 */
int32_t jl_set_UTCtime(jl_time_stamp_t ts)
{	
	u_printf("[%s:%d]:jl_set_UTCtime %d\r\n",__FUNCTION__,__LINE__,ts.second);
	
	jd_sys_time = ts.second;

	
    return 0;
}

/**
* @brief 获取系统UTC时间，精确到毫秒
* @param none
* @return time ms
*/
int jl_get_time_msec(jl_time_stamp_t *ts)
{
//	u_printf("[%s:%d]:jl_get_time_msec %d\r\n",__FUNCTION__,__LINE__,jd_sys_time);
	if(ts)
	{
        ts->second = (uint32_t) (jd_sys_time);
        ts->ms = (uint32_t) (jd_sys_time*1000);
	}

    return 0;
}

/**
 * 获取系统UTC时间，精确到秒
 *
 * @return: UTC Second
 *
 */
uint32_t jl_get_time_second(uint32_t *jl_time)
{
    return hfsys_get_time();
}

/**
 * get time string
 *
 * @out param: 
 * @return: success or fail
 *
 */
int jl_get_time(jl_time_t *jl_time)
{
//	u_printf("*********************jl_get_time*********************\r\n");
    return 0;
}

/**
 * 获取时间字符串
 *
 * @out param: "year-month-day hour:minute:second.millisecond"
 * @return: success or fail
 *
 */
char *jl_get_time_str(void)
{
    static char time_buffer[30];
    time_t timep;
    jl_time_stamp_t ts;
    struct tm *p;

    time(&timep);
    p = localtime(&timep);
    jl_get_time_msec(&ts);

    jl_platform_sprintf(time_buffer, "%02d-%02d-%02d %02d:%02d:%02d", 
        1900 + p->tm_year,
        1 + p->tm_mon,
        p->tm_mday,
        p->tm_hour,
        p->tm_min,
        p->tm_sec
        );
	
//	u_printf("*********************time_buffer %s*********************\r\n",time_buffer);
    return time_buffer;
}

/**
 * get os time
 *
 * @out param: none
 * @return: sys time ticks ms since sys start
*/
uint32_t jl_get_os_time(void)
{
    return hfsys_get_time();
}



