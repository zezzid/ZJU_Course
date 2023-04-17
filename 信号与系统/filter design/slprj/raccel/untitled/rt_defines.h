#include "__cf_untitled.h"
#ifndef RTW_HEADER_rt_defines_h_
#define RTW_HEADER_rt_defines_h_
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)
#else
#define UNUSED_PARAMETER(x)         (void) (x)
#endif
#endif
#endif
