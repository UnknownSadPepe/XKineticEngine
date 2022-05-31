#pragma once

#include "XKinetic/XKCore.h"

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
// The multiplier to convert seconds to milliseconds.
#define XK_SEC_TO_MS_MULTIPLIER 1000.0f
// The multiplier to convert milliseconds to seconds.
#define XK_MS_TO_SEC_MULTIPLIER 0.001f
// huge number that should be larger than any valid number used.
#define XK_INFINITY 1e30f
// least significant digit representable.
#define XK_FLOAT32_EPSILON (XkFloat32)1E-5
#define XK_FLOAT64_EPSILON (XkFloat64)1E-9

XKCORE_API XkFloat32 xkFCos(const XkFloat32);
XKCORE_API XkFloat64 xkDCos(const XkFloat64);
#define xkCos(x) _Generic((x), \
	XkFloat32: xkFCos, \
  XkFloat64: xkDCos)(x)

XKCORE_API XkFloat32 xkFCosA(const XkFloat32);
XKCORE_API XkFloat64 xkDCosA(const XkFloat64);
#define xkCosA(x) _Generic((x), \
	XkFloat32: xkFCosA, \
  XkFloat64: xkDCosA)(x)

XKCORE_API XkFloat32 xkFCosH(const XkFloat32);
XKCORE_API XkFloat64 xkDCosH(const XkFloat64);
#define xkCosH(x) _Generic((x), \
	XkFloat32: xkFCosH, \
  XkFloat64: xkDCosH)(x)

XKCORE_API XkFloat32 xkFCosAH(const XkFloat32);
XKCORE_API XkFloat64 xkDCosAH(const XkFloat64);
#define xkCosAH(x) _Generic((x), \
	XkFloat32: xkFCosAH, \
  XkFloat64: xkDCosAH)(x)

XKCORE_API XkFloat32 xkFSin(const XkFloat32);
XKCORE_API XkFloat64 xkDSin(const XkFloat64);
#define xkSin(x) _Generic((x), \
	XkFloat32: xkFSin, \
  XkFloat64: xkDSin)(x)

XKCORE_API XkFloat32 xkFSinA(const XkFloat32);
XKCORE_API XkFloat64 xkDSinA(const XkFloat64);
#define xkSinA(x) _Generic((x), \
	XkFloat32: xkFSinA, \
  XkFloat64: xkDSinA)(x)

XKCORE_API XkFloat32 xkFSinH(const XkFloat32);
XKCORE_API XkFloat64 xkDSinH(const XkFloat64);
#define xkSinH(x) _Generic((x), \
	XkFloat32: xkFSinH, \
  XkFloat64: xkDSinH)(x)

XKCORE_API XkFloat32 xkFSinAH(const XkFloat32);
XKCORE_API XkFloat64 xkDSinAH(const XkFloat64);
#define xkSinAH(x) _Generic((x), \
	XkFloat32: xkFSinAH, \
  XkFloat64: xkDSinAH)(x)

XKCORE_API XkFloat32 xkFTan(const XkFloat32);
XKCORE_API XkFloat64 xkDTan(const XkFloat64);
#define xkTan(x) _Generic((x), \
	XkFloat32: xkFTan, \
  XkFloat64: xkDTan)(x)

XKCORE_API XkFloat32 xkFTanA(const XkFloat32);
XKCORE_API XkFloat64 xkDTanA(const XkFloat64);
#define xkTanA(x) _Generic((x), \
	XkFloat32: xkFTanA, \
  XkFloat64: xkDTanA)(x)

XKCORE_API XkFloat32 xkFTanH(const XkFloat32);
XKCORE_API XkFloat64 xkDTanH(const XkFloat64);
#define xkTanH(x) _Generic((x), \
	XkFloat32: xkFTanH, \
  XkFloat64: xkDTanH)(x)

XKCORE_API XkFloat32 xkFTanAH(const XkFloat32);
XKCORE_API XkFloat64 xkDTanAH(const XkFloat64);
#define xkTanAH(x) _Generic((x), \
	XkFloat32: xkFTanAH, \
  XkFloat64: xkDTanAH)(x)

XKCORE_API XkFloat32 xkFLog(const XkFloat32);
XKCORE_API XkFloat64 xkDLog(const XkFloat64);
XKCORE_API XkInt32 xkILog(const XkInt32);
XKCORE_API XkUInt32 xkULog(const XkUInt32);
XKCORE_API XkInt64 xkLILog(const XkInt64);
XKCORE_API XkUInt64 xkLULog(const XkUInt64);
#define xkLog(x) _Generic((x), \
	XkFloat32: xkFLog, \
  XkFloat64: xkDLog, \
  XkInt32: xkILog, \
  XkUInt32: xkULog, \
  XkInt64: xkLILog, \
  XkUInt64: xkLULog)(x)

XKCORE_API XkFloat32 xkFExp(const XkFloat32);
XKCORE_API XkFloat64 xkDExp(const XkFloat64);
XKCORE_API XkInt32 xkIExp(const XkInt32);
XKCORE_API XkUInt32 xkUExp(const XkUInt32);
XKCORE_API XkInt64 xkLIExp(const XkInt64);
XKCORE_API XkUInt64 xkLUExp(const XkUInt64);
#define xkExp(x) _Generic((x), \
	XkFloat32: xkFExp, \
  XkFloat64: xkDExp, \
  XkInt32: xkIExp, \
  XkUInt32: xkUExp, \
  XkInt64: xkLIExp, \
  XkUInt64: xkLUExp)(x)

XKCORE_API XkFloat32 xkFPow(const XkFloat32, const XkFloat32);
XKCORE_API XkFloat64 xkDPow(const XkFloat64, const XkFloat64);
XKCORE_API XkInt32 xkIPow(const XkInt32, const XkInt32);
XKCORE_API XkUInt32 xkUPow(const XkUInt32, const XkUInt32);
XKCORE_API XkInt64 xkLIPow(const XkInt64, const XkInt64);
XKCORE_API XkUInt64 xkLUPow(const XkUInt64, const XkUInt64);
#define xkPow(x) _Generic((x), \
	XkFloat32: xkFPow, \
  XkFloat64: xkDPow, \
  XkInt32: xkIPow, \
  XkUInt32: xkUPow, \
  XkInt64: xkLIPow, \
  XkUInt64: xkLUPow)(x)

XKCORE_API XkFloat32 xkFSqrt(const XkFloat32);
XKCORE_API XkFloat64 xkDSqrt(const XkFloat64);
XKCORE_API XkInt32 xkISqrt(const XkInt32);
XKCORE_API XkUInt32 xkUSqrt(const XkUInt32);
XKCORE_API XkInt64 xkLISqrt(const XkInt64);
XKCORE_API XkUInt64 xkLUSqrt(const XkUInt64);
#define xkSqrt(x) _Generic((x), \
	XkFloat32: xkFSqrt, \
  XkFloat64: xkDSqrt, \
  XkInt32: xkISqrt, \
  XkUInt32: xkUSqrt, \
  XkInt64: xkLISqrt, \
  XkUInt64: xkLUSqrt)(x)


XKCORE_API XkFloat32 xkFCbrt(const XkFloat32);
XKCORE_API XkFloat64 xkDCbrt(const XkFloat64);
XKCORE_API XkInt32 xkICbrt(const XkInt32);
XKCORE_API XkUInt32 xkUCbrt(const XkUInt32);
XKCORE_API XkInt64 xkLICbrt(const XkInt64);
XKCORE_API XkUInt64 xkLUCbrt(const XkUInt64);
#define xkCbrt(x) _Generic((x), \
	XkFloat32: xkFCbrt, \
  XkFloat64: xkDCbrt, \
  XkInt32: xkICbrt, \
  XkUInt32: xkUCbrt, \
  XkInt64: xkLICbrt, \
  XkUInt64: xkLUCbrt)(x)

XKCORE_API XkFloat32 xkFCeil(const XkFloat32);
XKCORE_API XkFloat64 xkDCeil(const XkFloat64);
#define xkCeil(x) _Generic((x), \
	XkFloat32: xkFCeil, \
  XkFloat64: xkDCeil)(x)

XKCORE_API XkFloat32 xkFFloor(const XkFloat32);
XKCORE_API XkFloat64 xkDFloor(const XkFloat64);
#define xkFloor(x) _Generic((x), \
	XkFloat32: xkFFloor, \
  XkFloat64: xkDFloor)(x)

XKCORE_API XkFloat32 xkFModF(const XkFloat32, XkFloat32*);
XKCORE_API XkFloat64 xkDModF(const XkFloat64, XkFloat64*);
#define xkModF(x) _Generic((x), \
	XkFloat32: xkFModF, \
  XkFloat64: xkDModF)(x)

XKCORE_API XkFloat32 xkFFMod(const XkFloat32, const XkFloat32);
XKCORE_API XkFloat64 xkDFMod(const XkFloat64, const XkFloat64);
#define xkFMod(x) _Generic((x), \
	XkFloat32: xkFMod, \
  XkFloat64: xkDMod)(x)

XKCORE_API XK_INLINE XkFloat32 xkFMin(const XkFloat32 x, const XkFloat32 y) { return(x < y ? x : y); }
XKCORE_API XK_INLINE XkFloat64 xkDMin(const XkFloat64 x, const XkFloat64 y) { return(x < y ? x : y); }
XKCORE_API XK_INLINE XkInt32 xkIMin(const XkInt32 x, const XkInt32 y) { return(x < y ? x : y); }
XKCORE_API XK_INLINE XkUInt32 xkUMin(const XkUInt32 x, const XkUInt32 y) { return(x < y ? x : y); }
XKCORE_API XK_INLINE XkInt64 xkLIMin(const XkInt64 x, const XkInt64 y) { return(x < y ? x : y); }
XKCORE_API XK_INLINE XkUInt64 xkLUMin(const XkUInt64 x, const XkUInt64 y) { return(x < y ? x : y); }
#define xkMin(x) _Generic((x), \
	XkFloat32: xkFMin, \
  XkFloat64: xkDMin, \
  XkInt32: xkIMin, \
  XkUInt32: xkUMin, \
  XkInt64: xkLIMin, \
  XkUInt64: xkLUMin)(x)

XKCORE_API XK_INLINE XkFloat32 xkFMax(const XkFloat32 x, const XkFloat32 y) { return(x < y ? y : x); }
XKCORE_API XK_INLINE XkFloat64 xkDMax(const XkFloat64 x, const XkFloat64 y) { return(x < y ? y : x); }
XKCORE_API XK_INLINE XkInt32 xkIMax(const XkInt32 x, const XkInt32 y) { return(x < y ? y : x); }
XKCORE_API XK_INLINE XkUInt32 xkUMax(const XkUInt32 x, const XkUInt32 y) { return(x < y ? y : x); }
XKCORE_API XK_INLINE XkInt64 xkLIMax(const XkInt64 x, const XkInt64 y) { return(x < y ? y : x); }
XKCORE_API XK_INLINE XkUInt64 xkLUMax(const XkUInt64 x, const XkUInt64 y) { return(x < y ? y : x); }
#define xkMax(x) _Generic((x), \
	XkFloat32: xkFMax, \
  XkFloat64: xkDMax, \
  XkInt32: xkIMax, \
  XkUInt32: xkUMax, \
  XkInt64: xkLIMax, \
  XkUInt64: xkLUMax)(x)

XKCORE_API XK_INLINE XkFloat32 xkFClamp(const XkFloat32 x, const XkFloat32 min, const XkFloat32 max) { return(x < min ? min : (x > max ? max : x)); }
XKCORE_API XK_INLINE XkFloat64 xkDClamp(const XkFloat64 x, const XkFloat64 min, const XkFloat64 max) { return(x < min ? min : (x > max ? max : x)); }
XKCORE_API XK_INLINE XkInt32 xkIClamp(const XkInt32 x, const XkInt32 min, const XkInt32 max) { return(x < min ? min : (x > max ? max : x)); }
XKCORE_API XK_INLINE XkUInt32 xkUClamp(const XkUInt32 x, const XkUInt32 min, const XkUInt32 max) { return(x < min ? min : (x > max ? max : x)); }
XKCORE_API XK_INLINE XkInt64 xkLIClamp(const XkInt64 x, const XkInt64 min, const XkInt64 max) { return(x < min ? min : (x > max ? max : x)); }
XKCORE_API XK_INLINE XkUInt64 xkLUClamp(const XkUInt64 x, const XkUInt64 min, const XkUInt64 max) { return(x < min ? min : (x > max ? max : x)); }
#define xkClamp(x) _Generic((x), \
	XkFloat32: xkFClamp, \
  XkFloat64: xkDClamp, \
  XkInt32: xkIClamp, \
  XkUInt32: xkUClamp, \
  XkInt64: xkLIClamp, \
  XkUInt64: xkLUClamp)(x)

XKCORE_API XkFloat32 xkFAbs(const XkFloat32);
XKCORE_API XkFloat64 xkDAbs(const XkFloat64);
#define xkAbs(x) _Generic((x), \
	XkFloat32: xkFAbs, \
  XkFloat64: xkDAbs)(x)
