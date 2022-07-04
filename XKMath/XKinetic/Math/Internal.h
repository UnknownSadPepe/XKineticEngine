#pragma once

#include "XKinetic/Math/Math.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef fp_force_evalf
#define fp_force_evalf fp_force_evalf
static inline void fp_force_evalf(float x)
{
	volatile float y;
	y = x;
}
#endif

#ifndef fp_force_eval
#define fp_force_eval fp_force_eval
static inline void fp_force_eval(double x)
{
	volatile double y;
	y = x;
}
#endif

#ifndef fp_force_evall
#define fp_force_evall fp_force_evall
static inline void fp_force_evall(long double x)
{
	volatile long double y;
	y = x;
}
#endif

#define FORCE_EVAL(x) do {          				\
	if (sizeof(x) == sizeof(float)) {         \
		fp_force_evalf(x);                			\
	} else if (sizeof(x) == sizeof(double)) { \
		fp_force_eval(x);                 			\
	} else {                                  \
		fp_force_evall(x);                			\
	}                                         \
} while(0)

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus
