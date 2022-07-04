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

	XkFloat32 handle[4][2];
} XkMat4x2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[4][3];
} XkMat4x3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[4][4];
} XkMat4;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx[2];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[4][2];
} XkDMat4x2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[4][3];
} XkDMat4x3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[4][4];
} XkDMat4;

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus
