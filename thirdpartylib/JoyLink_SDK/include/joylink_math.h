#ifndef __JOYLINK_MATH_H__
#define __JOYLINK_MATH_H__
#include "joylink_stdint.h"

 /**
 * @brief 计算x的y次方，精度是 double 类型.
 *
 * @param [in] x @n 底数.
 * @param [in] y @n 指数.
 * @return x的y次方.
 */
double jl_platform_pow(double x, double y);

 /**
 * @brief 计算x的y次方，精度是 float 类型.
 *
 * @param [in] x @n 底数.
 * @param [in] y @n 指数.
 * @return x的y次方.
 */
float jl_platform_powf(float x, float y);




#endif // end __JOYLINK_MATH_H__


