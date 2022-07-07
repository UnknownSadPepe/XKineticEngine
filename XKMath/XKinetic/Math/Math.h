#pragma once

#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	#include <immintrin.h>
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

#include "XKinetic/XKMath.h"

// An approximate representation of PI.
#define XK_PI 3.14159265358979323846f
// An approximate representation of PI multiplied by 2.
#define XK_PI_2 2.0f * XK_PI
// An approximate representation of PI divided by 2.
#define XK_HALF_PI 0.5f * XK_PI
// An approximate representation of PI divided by 4.
#define XK_QUARTER_PI 0.25f * XK_PI
// One divided by an approximate representation of PI.
#define XK_ONE_OVER_PI 1.0f / XK_PI
// One divided by half of an approximate representation of PI.
#define XK_ONE_OVER_TWO_PI 1.0f / XK_PI_2
// An approximation of the square root of 2.
#define XK_SQRT_TWO 1.41421356237309504880f
// An approximation of the square root of 3.
#define XK_SQRT_THREE 1.73205080756887729352f
// One divided by an approximation of the square root of 2.
#define XK_SQRT_ONE_OVER_TWO 0.70710678118654752440f
// One divided by an approximation of the square root of 3.
#define XK_SQRT_ONE_OVER_THREE 0.57735026918962576450f
// A multiplier used to convert degrees to radians.
#define XK_DEG2RAD_MULTIPLIER XK_PI / 180.0f
// A multiplier used to convert radians to degrees.
#define XK_RAD2DEG_MULTIPLIER 180.0f / XK_PI
// huge number that should be larger than any valid number used.
#define XK_INFINITY 1e30f
// least significant digit representable.
#define XK_FLOAT32_EPSILON 1E-5
#define XK_FLOAT64_EPSILON 1E-9

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern XKMATH_API XkFloat32 XK_FASTCALL xkFCos(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCos(const XkFloat64);
#define xkCos(x) _Generic((x), \
	XkFloat32: xkFCos, \
  XkFloat64: xkDCos)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFCosA(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCosA(const XkFloat64);
#define xkCosA(x) _Generic((x), \
	XkFloat32: xkFCosA, \
  XkFloat64: xkDCosA)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFCosH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCosH(const XkFloat64);
#define xkCosH(x) _Generic((x), \
	XkFloat32: xkFCosH, \
  XkFloat64: xkDCosH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFCosAH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCosAH(const XkFloat64);
#define xkCosAH(x) _Generic((x), \
	XkFloat32: xkFCosAH, \
  XkFloat64: xkDCosAH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFSin(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDSin(const XkFloat64);
#define xkSin(x) _Generic((x), \
	XkFloat32: xkFSin, \
  XkFloat64: xkDSin)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFSinA(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDSinA(const XkFloat64);
#define xkSinA(x) _Generic((x), \
	XkFloat32: xkFSinA, \
  XkFloat64: xkDSinA)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFSinH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDSinH(const XkFloat64);
#define xkSinH(x) _Generic((x), \
	XkFloat32: xkFSinH, \
  XkFloat64: xkDSinH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFSinAH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDSinAH(const XkFloat64);
#define xkSinAH(x) _Generic((x), \
	XkFloat32: xkFSinAH, \
  XkFloat64: xkDSinAH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFTan(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDTan(const XkFloat64);
#define xkTan(x) _Generic((x), \
	XkFloat32: xkFTan, \
  XkFloat64: xkDTan)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFTanA(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDTanA(const XkFloat64);
#define xkTanA(x) _Generic((x), \
	XkFloat32: xkFTanA, \
  XkFloat64: xkDTanA)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFTanH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDTanH(const XkFloat64);
#define xkTanH(x) _Generic((x), \
	XkFloat32: xkFTanH, \
  XkFloat64: xkDTanH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFTanAH(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDTanAH(const XkFloat64);
#define xkTanAH(x) _Generic((x), \
	XkFloat32: xkFTanAH, \
  XkFloat64: xkDTanAH)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFLog(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDLog(const XkFloat64);
extern XKMATH_API XkInt32 XK_FASTCALL xkILog(const XkInt32);
extern XKMATH_API XkUInt32 XK_FASTCALL xkULog(const XkUInt32);
extern XKMATH_API XkInt64 XK_FASTCALL xkLILog(const XkInt64);
extern XKMATH_API XkUInt64 XK_FASTCALL xkLULog(const XkUInt64);
#define xkLog(x) _Generic((x), \
	XkFloat32: xkFLog, \
  XkFloat64: xkDLog)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFExp(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDExp(const XkFloat64);
extern XKMATH_API XkInt32 XK_FASTCALL xkIExp(const XkInt32);
extern XKMATH_API XkUInt32 XK_FASTCALL xkUExp(const XkUInt32);
extern XKMATH_API XkInt64 XK_FASTCALL xkLIExp(const XkInt64);
extern XKMATH_API XkUInt64 XK_FASTCALL xkLUExp(const XkUInt64);
#define xkExp(x) _Generic((x), \
	XkFloat32: xkFExp, \
  XkFloat64: xkDExp)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFPow(const XkFloat32, const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDPow(const XkFloat64, const XkFloat64);
extern XKMATH_API XkInt32 XK_FASTCALL xkIPow(const XkInt32, const XkInt32);
extern XKMATH_API XkUInt32 XK_FASTCALL xkUPow(const XkUInt32, const XkUInt32);
extern XKMATH_API XkInt64 XK_FASTCALL xkLIPow(const XkInt64, const XkInt64);
extern XKMATH_API XkUInt64 XK_FASTCALL xkLUPow(const XkUInt64, const XkUInt64);
#define xkPow(x) _Generic((x), \
	XkFloat32: xkFPow, \
  XkFloat64: xkDPow)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFSqrt(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDSqrt(const XkFloat64);
#define xkSqrt(x) _Generic((x), \
	XkFloat32: xkFSqrt, \
  XkFloat64: xkDSqrt)(x)


extern XKMATH_API XkFloat32 XK_FASTCALL xkFCbrt(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCbrt(const XkFloat64);
#define xkCbrt(x) _Generic((x), \
	XkFloat32: xkFCbrt, \
  XkFloat64: xkDCbrt)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFCeil(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDCeil(const XkFloat64);
#define xkCeil(x) _Generic((x), \
	XkFloat32: xkFCeil, \
  XkFloat64: xkDCeil)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFFloor(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDFloor(const XkFloat64);
#define xkFloor(x) _Generic((x), \
	XkFloat32: xkFFloor, \
  XkFloat64: xkDFloor)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFModF(const XkFloat32, XkFloat32*);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDModF(const XkFloat64, XkFloat64*);
#define xkModF(x) _Generic((x), \
	XkFloat32: xkFModF, \
  XkFloat64: xkDModF)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFFMod(const XkFloat32, const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDFMod(const XkFloat64, const XkFloat64);
#define xkFMod(x) _Generic((x), \
	XkFloat32: xkFMod, \
  XkFloat64: xkDMod)(x)

extern XKMATH_API XK_INLINE XkFloat32 XK_FASTCALL xkFMin(const XkFloat32 x, const XkFloat32 y) { return(x < y ? x : y); }
extern XKMATH_API XK_INLINE XkFloat64 XK_FASTCALL xkDMin(const XkFloat64 x, const XkFloat64 y) { return(x < y ? x : y); }
extern XKMATH_API XK_INLINE XkInt32 XK_FASTCALL xkIMin(const XkInt32 x, const XkInt32 y) { return(x < y ? x : y); }
extern XKMATH_API XK_INLINE XkUInt32 XK_FASTCALL xkUMin(const XkUInt32 x, const XkUInt32 y) { return(x < y ? x : y); }
extern XKMATH_API XK_INLINE XkInt64 XK_FASTCALL xkLIMin(const XkInt64 x, const XkInt64 y) { return(x < y ? x : y); }
extern XKMATH_API XK_INLINE XkUInt64 XK_FASTCALL xkLUMin(const XkUInt64 x, const XkUInt64 y) { return(x < y ? x : y); }
#define xkMin(x) _Generic((x), \
	XkFloat32: xkFMin, \
  XkFloat64: xkDMin, \
  XkInt32: xkIMin, \
  XkUInt32: xkUMin, \
  XkInt64: xkLIMin, \
  XkUInt64: xkLUMin)(x)

extern XKMATH_API XK_INLINE XkFloat32 XK_FASTCALL xkFMax(const XkFloat32 x, const XkFloat32 y) { return(x < y ? y : x); }
extern XKMATH_API XK_INLINE XkFloat64 XK_FASTCALL xkDMax(const XkFloat64 x, const XkFloat64 y) { return(x < y ? y : x); }
extern XKMATH_API XK_INLINE XkInt32 XK_FASTCALL xkIMax(const XkInt32 x, const XkInt32 y) { return(x < y ? y : x); }
extern XKMATH_API XK_INLINE XkUInt32 XK_FASTCALL xkUMax(const XkUInt32 x, const XkUInt32 y) { return(x < y ? y : x); }
extern XKMATH_API XK_INLINE XkInt64 XK_FASTCALL xkLIMax(const XkInt64 x, const XkInt64 y) { return(x < y ? y : x); }
extern XKMATH_API XK_INLINE XkUInt64 XK_FASTCALL xkLUMax(const XkUInt64 x, const XkUInt64 y) { return(x < y ? y : x); }
#define xkMax(x) _Generic((x), \
	XkFloat32: xkFMax, \
  XkFloat64: xkDMax, \
  XkInt32: xkIMax, \
  XkUInt32: xkUMax, \
  XkInt64: xkLIMax, \
  XkUInt64: xkLUMax)(x)

extern XKMATH_API XK_INLINE XkFloat32 XK_FASTCALL xkFClamp(const XkFloat32 x, const XkFloat32 min, const XkFloat32 max) { return(x < min ? min : (x > max ? max : x)); }
extern XKMATH_API XK_INLINE XkFloat64 XK_FASTCALL xkDClamp(const XkFloat64 x, const XkFloat64 min, const XkFloat64 max) { return(x < min ? min : (x > max ? max : x)); }
extern XKMATH_API XK_INLINE XkInt32 XK_FASTCALL xkIClamp(const XkInt32 x, const XkInt32 min, const XkInt32 max) { return(x < min ? min : (x > max ? max : x)); }
extern XKMATH_API XK_INLINE XkUInt32 XK_FASTCALL xkUClamp(const XkUInt32 x, const XkUInt32 min, const XkUInt32 max) { return(x < min ? min : (x > max ? max : x)); }
extern XKMATH_API XK_INLINE XkInt64 XK_FASTCALL xkLIClamp(const XkInt64 x, const XkInt64 min, const XkInt64 max) { return(x < min ? min : (x > max ? max : x)); }
extern XKMATH_API XK_INLINE XkUInt64 XK_FASTCALL xkLUClamp(const XkUInt64 x, const XkUInt64 min, const XkUInt64 max) { return(x < min ? min : (x > max ? max : x)); }
#define xkClamp(x) _Generic((x), \
	XkFloat32: xkFClamp, \
  XkFloat64: xkDClamp, \
  XkInt32: xkIClamp, \
  XkUInt32: xkUClamp, \
  XkInt64: xkLIClamp, \
  XkUInt64: xkLUClamp)(x)

extern XKMATH_API XkFloat32 XK_FASTCALL xkFAbs(const XkFloat32);
extern XKMATH_API XkFloat64 XK_FASTCALL xkDAbs(const XkFloat64);
extern XKMATH_API XkInt32 XK_FASTCALL xkIAbs(const XkInt32);
extern XKMATH_API XkInt64 XK_FASTCALL xkLIAbs(const XkInt64);
#define xkAbs(x) _Generic((x), \
	XkFloat32: xkFAbs,    \
  XkFloat64: xkDAbs,    \
  XkInt32: xkIAbs,      \
  XkInt64: xkLIAbs)(x)

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
