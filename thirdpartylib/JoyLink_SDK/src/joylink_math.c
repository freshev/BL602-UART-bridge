#include <math.h>
#include "joylink_math.h"

 /**
 * @brief 计算x的y次方，精度是 double 类型.
 *
 * @param [in] x @n 底数.
 * @param [in] y @n 指数.
 * @return x的y次方.
 */
double jl_platform_pow(double x, double y)
{
    return pow(x, y);
}

 /**
 * @brief 计算x的y次方，精度是 float 类型.
 *
 * @param [in] x @n 底数.
 * @param [in] y @n 指数.
 * @return x的y次方.
 */
float jl_platform_powf(float x, float y)
{
    return powf(x, y);
}



