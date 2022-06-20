#pragma once

#include "XKinetic/XKMath.h"
#include "XKinetic/Math/Math.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	union {
		struct { XkFloat32 x, y, z, w; };
		struct { XkFloat32 r, g, b, a; };
	};
} XkVec4;

typedef struct {
	union {
		struct { XkFloat64 x, y, z, w; };
		struct { XkFloat64 r, g, b, a; };
	};
} XkDVec4;

XK_INLINE XKMATH_API XkVec4 xkVec4Add(const XkVec4 a, const XkVec4 b) {
	return((XkVec4){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
		.w = a.w + b.w
	});
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Add(const XkDVec4 a, const XkDVec4 b) {
	return((XkDVec4){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
		.w = a.w + b.w
	});
}

XK_INLINE XKMATH_API XkVec4 xkVec4Sub(const XkVec4 a, const XkVec4 b) {
	return((XkVec4){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
		.w = a.w - b.w
	});
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Sub(const XkDVec4 a, const XkDVec4 b) {
	return((XkDVec4){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
		.w = a.w - b.w
	});
}

XK_INLINE XKMATH_API XkVec4 xkVec4Mul(const XkVec4 a, const XkVec4 b) {
	return((XkVec4){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z,
		.w = a.w * b.w
	});
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Mul(const XkDVec4 a, const XkDVec4 b) {
	return((XkDVec4){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z,
		.w = a.w * b.w
	});
}

XK_INLINE XKMATH_API XkVec4 xkVec4Div(const XkVec4 a, const XkVec4 b) {
	return((XkVec4){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z,
		.w = a.w / b.w
	});
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Div(const XkDVec4 a, const XkDVec4 b) {
	return((XkDVec4){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z,
		.w = a.w / b.w
	});
}

XK_INLINE XKMATH_API XkBool xkVec4Compare(const XkVec4 a, const XkVec4 b) {
	if(xkAbs(a.x - b.x) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT32_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT32_EPSILON) return(XK_FALSE);
  if(xkAbs(a.w - b.w) > XK_FLOAT32_EPSILON) return(XK_FALSE);

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkBool xkDVec4Compare(const XkDVec4 a, const XkDVec4 b) {
	if(xkAbs(a.x - b.x) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.y - b.y) > XK_FLOAT64_EPSILON) return(XK_FALSE);
	if(xkAbs(a.z - b.z) > XK_FLOAT64_EPSILON) return(XK_FALSE);
  if(xkAbs(a.w - b.w) > XK_FLOAT64_EPSILON) return(XK_FALSE);

	return(XK_TRUE);
}

XK_INLINE XKMATH_API XkFloat32 xkVec4Length(const XkVec4 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

XK_INLINE XKMATH_API XkFloat64 xkDVec4Length(const XkDVec4 a) {
	return(xkSqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

XK_INLINE XKMATH_API XkVec4 xkVec4Normalize(const XkVec4 a) {
	const XkFloat32 length = xkVec4Length(a);
	return((XkVec4){
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length,
		.w = a.w / length
	});
}

XK_INLINE XKMATH_API XkDVec4 xkDVec4Normalize(const XkDVec4 a) {
	const XkFloat64 length = xkDVec4Length(a);
	return((XkDVec4){
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length,
		.w = a.w / length
	});
}

#ifdef __cplusplus
}
#endif // __cplusplus
