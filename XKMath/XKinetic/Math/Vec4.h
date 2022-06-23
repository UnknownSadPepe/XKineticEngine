#pragma once

#include "XKinetic/XKMath.h"
#include "XKinetic/Math/Math.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128 avx;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	struct { XkFloat32 x, y, z, w; };
	struct { XkFloat32 r, g, b, a; };

	XkFloat32 handle[4];
} XkVec4;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	struct { XkFloat64 x, y, z, w; };
	struct { XkFloat64 r, g, b, a; };

	XkFloat64 handle[4];
} XkDVec4;

XK_INLINE XKMATH_API XkVec4 xkVec4Add(const XkVec4 a, const XkVec4 b) {
	XkVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_add_ps(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	vec.w = a.w + b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Add(const XkDVec4 a, const XkDVec4 b) {
	XkDVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_add_pd(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	vec.w = a.w + b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec4 xkVec4Sub(const XkVec4 a, const XkVec4 b) {
	XkVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_sub_ps(a.avx, b.avx);
#else
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	vec.w = a.w - b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Sub(const XkDVec4 a, const XkDVec4 b) {
	XkDVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_sub_pd(a.avx, b.avx);
#else
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	vec.w = a.w - b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec4 xkVec4Mul(const XkVec4 a, const XkVec4 b) {
	XkVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_mul_ps(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	vec.w = a.w * b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Mul(const XkDVec4 a, const XkDVec4 b) {
	XkDVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_mul_pd(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	vec.w = a.w * b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec4 xkVec4Div(const XkVec4 a, const XkVec4 b) {
	XkVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_div_ps(a.avx, b.avx);
#else
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
	vec.w = a.w / b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Div(const XkDVec4 a, const XkDVec4 b) {
	XkDVec4 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_div_pd(a.avx, b.avx);
#else
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
	vec.w = a.w / b.w;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkBool xkVec4Compare(const XkVec4 a, const XkVec4 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT32_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.w - b.w) > XK_FLOAT32_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkBool xkDVec4Compare(const XkDVec4 a, const XkDVec4 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT64_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.w - b.w) > XK_FLOAT64_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkFloat32 xkVec4Length(const XkVec4 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

XK_INLINE XKMATH_API XkFloat64 xkDVec4Length(const XkDVec4 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

XK_INLINE XKMATH_API XkVec4 xkVec4Normalize(const XkVec4 a) {
	XkVec4 vec = {0};

	const XkFloat32 length = xkVec4Length(a);

	const XkFloat32 Multiplier = 1.0f / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m128 avxMultiplier = _mm_set1_ps(Multiplier);
  vec.avx = _mm_mul_ps(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
	vec.z = a.z * Multiplier;
	vec.w = a.w * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Normalize(const XkDVec4 a) {
	XkDVec4 vec = {0};

	const XkFloat64 length = xkDVec4Length(a);

	const XkFloat64 Multiplier = 1.0 / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m256d avxMultiplier = _mm256_set1_pd(Multiplier);
  vec.avx = _mm256_mul_pd(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
	vec.z = a.z * Multiplier;
	vec.w = a.w * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkFloat32 xkVec4Dot(const XkVec4 a, const XkVec4 b) {
	XkFloat32 result = 0.0f;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: implementation.
#else
  result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

XK_INLINE XKMATH_API XkFloat64 xkDVec4Dot(const XkDVec4 a, const XkDVec4 b) {
	XkFloat64 result = 0.0;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: implementation.
#else
  result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

#ifdef __cplusplus
}
#endif // __cplusplus
