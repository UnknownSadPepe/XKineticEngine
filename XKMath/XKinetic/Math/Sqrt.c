#include "XKinetic/Math/Math.h"

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

XkInt32 xkISqrt(const XkInt32 x) {
	return(0);
}

XkUInt32 xkUSqrt(const XkUInt32 x) {
	return(0u);
}

XkInt64 xkLISqrt(const XkInt64 x) {
	return(0ll);
}

XkUInt64 xkLUSqrt(const XkUInt64 x) {
	return(0ll);
}
