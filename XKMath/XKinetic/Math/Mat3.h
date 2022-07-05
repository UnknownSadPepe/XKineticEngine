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

	XkFloat32 handle[3][2];
} XkMat3x2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[3][3];
} XkMat3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat32 handle[3][4];
} XkMat3x4;


typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx[2];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[3][2];
} XkDMat3x2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx[3];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[3][3];
} XkDMat3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256 avx[4];
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	XkFloat64 handle[3][4];
} XkDMat3x4;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

