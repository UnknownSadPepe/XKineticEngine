/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Internal.h"

/* ########## FUNCTIONS SECTION ########## */
XkFloat32 xkFSqrt(const XkFloat32 x) {
	XkFloat32 result = 0.0f;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 In = _mm_set_ss(x);
	__m128 Out = _mm_sqrt_ss(In);
	result = _mm_cvtss_f32(Out);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

XkFloat64 xkDSqrt(const XkFloat64 x) {
	XkFloat64 result = 0.0;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	//__m128d In = _mm_set_sd(x);
	//__m128d Out = _mm_sqrt_sd(In);
	//result = _mm_cvtsd_f64(Out);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

