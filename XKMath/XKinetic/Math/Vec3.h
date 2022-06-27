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

	struct { XkFloat32 x, y, z; };
	struct { XkFloat32 r, g, b; };
	struct { XkFloat32 u, v, w; };

	XkFloat32 handle[3];
} XkVec3;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m256d avx;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	struct { XkFloat64 x, y, z; };
	struct { XkFloat64 r, g, b; };
	struct { XkFloat64 u, v, w; };

	XkFloat64 handle[3];
} XkDVec3;

XK_INLINE XKMATH_API XkVec3 xkVec3Add(const XkVec3 a, const XkVec3 b) {
	XkVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_add_ps(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec3 xkDVec3Add(const XkDVec3 a, const XkDVec3 b) {
	XkDVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_add_pd(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec3 xkVec3Sub(const XkVec3 a, const XkVec3 b) {
	XkVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_sub_ps(a.avx, b.avx);
#else
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec3 xkDVec3Sub(const XkDVec3 a, const XkDVec3 b) {
	XkDVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_sub_pd(a.avx, b.avx);
#else
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec3 xkVec3Mul(const XkVec3 a, const XkVec3 b) {
	XkVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_mul_ps(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec3 xkDVec3Mul(const XkDVec3 a, const XkDVec3 b) {
	XkDVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_mul_pd(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec3 xkVec3Div(const XkVec3 a, const XkVec3 b) {
	XkVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_div_ps(a.avx, b.avx);
#else
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec3 xkDVec3Div(const XkDVec3 a, const XkDVec3 b) {
	XkDVec3 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm256_div_pd(a.avx, b.avx);
#else
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkBool xkVec3Compare(const XkVec3 a, const XkVec3 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT32_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT32_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkBool xkDVec3Compare(const XkDVec3 a, const XkDVec3 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT64_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT64_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkFloat32 xkVec3Length(const XkVec3 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

XK_INLINE XKMATH_API XkFloat64 xkDVec3Length(const XkDVec3 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

XK_INLINE XKMATH_API XkVec3 xkVec3Normalize(const XkVec3 a) {
	XkVec3 vec = {0};

	const XkFloat32 length = xkVec3Length(a);

	const XkFloat32 Multiplier = 1.0f / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m128 avxMultiplier = _mm_set1_ps(Multiplier);
  vec.avx = _mm_mul_ps(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
	vec.z = a.z * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec3 xkDVec3Normalize(const XkDVec3 a) {
	XkDVec3 vec = {0};

	const XkFloat64 length = xkDVec3Length(a);

	const XkFloat64 Multiplier = 1.0 / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m256d avxMultiplier = _mm256_set1_pd(Multiplier);
  vec.avx = _mm256_mul_pd(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
	vec.z = a.z * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkFloat32 xkVec3Dot(const XkVec3 a, const XkVec3 b) {
	XkFloat32 result = 0.0f;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
  result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

XK_INLINE XKMATH_API XkFloat64 xkDVec3Dot(const XkDVec3 a, const XkDVec3 b) {
	XkFloat64 result = 0.0;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
  result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

#ifdef __cplusplus
}
#endif // __cplusplus
