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

	struct { XkFloat32 x, y; };
	struct { XkFloat32 u, v; };

	XkFloat32 handle[2];
} XkVec2;

typedef union {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	__m128d avx;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	struct { XkFloat64 x, y; };
	struct { XkFloat64 u, v; };

	XkFloat64 handle[2];
} XkDVec2;

XK_INLINE XKMATH_API XkVec2 xkVec2Add(const XkVec2 a, const XkVec2 b) {
	XkVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_add_ps(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec2 xkDVec2Add(const XkDVec2 a, const XkDVec2 b) {
	XkDVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_add_pd(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec2 xkVec2Sub(const XkVec2 a, const XkVec2 b) {
	XkVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_sub_ps(a.avx, b.avx);
#else
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec2 xkDVec2Sub(const XkDVec2 a, const XkDVec2 b) {
	XkDVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_sub_pd(a.avx, b.avx);
#else
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec2 xkVec2Mul(const XkVec2 a, const XkVec2 b) {
	XkVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_mul_ps(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec2 xkDVec2Mul(const XkDVec2 a, const XkDVec2 b) {
	XkDVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_mul_pd(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkVec2 xkVec2Div(const XkVec2 a, const XkVec2 b) {
	XkVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_div_ps(a.avx, b.avx);
#else
	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec2 xkDVec2Div(const XkDVec2 a, const XkDVec2 b) {
	XkDVec2 vec = {0};
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	vec.avx = _mm_mul_pd(a.avx, b.avx);
#else
	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkBool xkVec2Compare(const XkVec2 a, const XkVec2 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT32_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkBool xkDVec2Compare(const XkDVec2 a, const XkDVec2 b) {
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
	if(xkAbs(a.x - b.x) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT64_EPSILON) return(XK_FALSE);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkFloat32 xkVec2Length(const XkVec2 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y));
}

XK_INLINE XKMATH_API XkFloat64 xkDVec2Length(const XkDVec2 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y));
}

XK_INLINE XKMATH_API XkVec2 xkVec2Normalize(const XkVec2 a) {
	XkVec2 vec = {0};

	const XkFloat32 length = xkVec2Length(a);

	const XkFloat32 Multiplier = 1.0f / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m128 avxMultiplier = _mm_set1_ps(Multiplier);
  vec.avx = _mm_mul_ps(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkDVec2 xkDVec2Normalize(const XkDVec2 a) {
	XkDVec2 vec = {0};

	const XkFloat64 length = xkDVec2Length(a);

	const XkFloat64 Multiplier = 1.0 / length;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
  __m128d avxMultiplier = _mm_set1_pd(Multiplier);
  vec.avx = _mm_mul_pd(a.avx, avxMultiplier);
#else
	vec.x = a.x * Multiplier;
	vec.y = a.y * Multiplier;
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(vec);
}

XK_INLINE XKMATH_API XkFloat32 xkVec2Dot(const XkVec2 a, const XkVec2 b) {
	XkFloat32 result = 0.0f;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
  result = (a.x * b.x) + (a.y * b.y);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

XK_INLINE XKMATH_API XkFloat64 xkDVec2Dot(const XkDVec2 a, const XkDVec2 b) {
	XkFloat64 result = 0.0;

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	/// TODO: Implementation.
#else
  result = (a.x * b.x) + (a.y * b.y);
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

	return(result);
}

#ifdef __cplusplus
}
#endif // __cplusplus
