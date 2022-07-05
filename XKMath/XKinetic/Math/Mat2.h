#pragma once

#include "XKinetic/XKMath.h"
#include "XKinetic/Math/Math.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[2];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[2][2];
} XkMat2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[2][3];
} XkMat2x3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[2][4];
} XkMat2x4;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128d avx[2];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[2][2];
} XkDMat2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128d avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[2][3];
} XkDMat2x3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128d avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[2][4];
} XkDMat2x4;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

