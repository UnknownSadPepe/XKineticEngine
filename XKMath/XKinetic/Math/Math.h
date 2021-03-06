#pragma once

/* ########## INCLUDE SECTION ########## */
#if defined(__XKMATH_AVX__) || defined(__XKMATH_AVX2__)
	#include <immintrin.h>
#endif // __XKMATH_AVX__ || __XKMATH_AVX2__

#include "XKinetic/XKMath.h"

/* ########## MACROS SECTION ########## */
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
"C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XKMATH_API XkFloat32			xkFCos(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCos(const XkFloat64);

extern XKMATH_API XkFloat32			xkFCosA(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCosA(const XkFloat64);

extern XKMATH_API XkFloat32			xkFCosH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCosH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFCosAH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCosAH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFSin(const XkFloat32);
extern XKMATH_API XkFloat64			xkDSin(const XkFloat64);

extern XKMATH_API XkFloat32			xkFSinA(const XkFloat32);
extern XKMATH_API XkFloat64			xkDSinA(const XkFloat64);

extern XKMATH_API XkFloat32			xkFSinH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDSinH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFSinAH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDSinAH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFTan(const XkFloat32);
extern XKMATH_API XkFloat64			xkDTan(const XkFloat64);

extern XKMATH_API XkFloat32			xkFTanA(const XkFloat32);
extern XKMATH_API XkFloat64			xkDTanA(const XkFloat64);

extern XKMATH_API XkFloat32			xkFTanH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDTanH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFTanAH(const XkFloat32);
extern XKMATH_API XkFloat64			xkDTanAH(const XkFloat64);

extern XKMATH_API XkFloat32			xkFLog(const XkFloat32);
extern XKMATH_API XkFloat64			xkDLog(const XkFloat64);

extern XKMATH_API XkFloat32			xkFLog2(const XkFloat32);
extern XKMATH_API XkFloat64			xkDLog2(const XkFloat64);

extern XKMATH_API XkFloat32			xkFExp(const XkFloat32);
extern XKMATH_API XkFloat64			xkDExp(const XkFloat64);

extern XKMATH_API XkFloat32			xkFExp2(const XkFloat32);
extern XKMATH_API XkFloat64			xkDExp2(const XkFloat64);

extern XKMATH_API XkFloat32			xkFPow(const XkFloat32, const XkFloat32);
extern XKMATH_API XkFloat64			xkDPow(const XkFloat64, const XkFloat64);

extern XKMATH_API XkFloat32			xkFSqrt(const XkFloat32);
extern XKMATH_API XkFloat64			xkDSqrt(const XkFloat64);

extern XKMATH_API XkFloat32			xkFCbrt(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCbrt(const XkFloat64);

extern XKMATH_API XkFloat32			xkFRound(const XkFloat32);
extern XKMATH_API XkFloat64			xkDRound(const XkFloat64);

extern XKMATH_API XkFloat32			xkFCeil(const XkFloat32);
extern XKMATH_API XkFloat64			xkDCeil(const XkFloat64);

extern XKMATH_API XkFloat32			xkFFloor(const XkFloat32);
extern XKMATH_API XkFloat64			xkDFloor(const XkFloat64);

extern XKMATH_API XkFloat32			xkFTrunc(const XkFloat32); 
extern XKMATH_API XkFloat64			xkDTrunc(const XkFloat64);

extern XKMATH_API XkFloat32			xkFModF(const XkFloat32, XkFloat32*);
extern XKMATH_API XkFloat64			xkDModF(const XkFloat64, XkFloat64*);

extern XKMATH_API XkFloat32			xkFFRExp(const XkFloat32, const XkInt32);
extern XKMATH_API XkFloat64			xkDFRExp(const XkFloat64, const XkInt32);

extern XKMATH_API XkFloat32			xkFLDExp(const XkFloat32, const XkInt32);
extern XKMATH_API XkFloat64			xkDLDExp(const XkFloat64, const XkInt32);

extern XKMATH_API XkFloat32			xkFFMod(const XkFloat32, const XkFloat32);
extern XKMATH_API XkFloat64			xkDFMod(const XkFloat64, const XkFloat64);

XKMATH_API XK_INLINE XkFloat32	xkFMin(const XkFloat32 x, const XkFloat32 y) { return(x < y ? x : y); }
XKMATH_API XK_INLINE XkFloat64	xkDMin(const XkFloat64 x, const XkFloat64 y) { return(x < y ? x : y); }
XKMATH_API XK_INLINE XkInt32		xkIMin(const XkInt32 x, const XkInt32 y) { return(x < y ? x : y); }
XKMATH_API XK_INLINE XkUInt32		xkUMin(const XkUInt32 x, const XkUInt32 y) { return(x < y ? x : y); }
XKMATH_API XK_INLINE XkInt64		xkLIMin(const XkInt64 x, const XkInt64 y) { return(x < y ? x : y); }
XKMATH_API XK_INLINE XkUInt64		xkLUMin(const XkUInt64 x, const XkUInt64 y) { return(x < y ? x : y); }

XKMATH_API XK_INLINE XkFloat32	xkFMax(const XkFloat32 x, const XkFloat32 y) { return(x < y ? y : x); }
XKMATH_API XK_INLINE XkFloat64	xkDMax(const XkFloat64 x, const XkFloat64 y) { return(x < y ? y : x); }
XKMATH_API XK_INLINE XkInt32		xkIMax(const XkInt32 x, const XkInt32 y) { return(x < y ? y : x); }
XKMATH_API XK_INLINE XkUInt32		xkUMax(const XkUInt32 x, const XkUInt32 y) { return(x < y ? y : x); }
XKMATH_API XK_INLINE XkInt64		xkLIMax(const XkInt64 x, const XkInt64 y) { return(x < y ? y : x); }
XKMATH_API XK_INLINE XkUInt64		xkLUMax(const XkUInt64 x, const XkUInt64 y) { return(x < y ? y : x); }

XKMATH_API XK_INLINE XkFloat32	xkFClamp(const XkFloat32 x, const XkFloat32 min, const XkFloat32 max) { return(x < min ? min : (x > max ? max : x)); }
XKMATH_API XK_INLINE XkFloat64	xkDClamp(const XkFloat64 x, const XkFloat64 min, const XkFloat64 max) { return(x < min ? min : (x > max ? max : x)); }
XKMATH_API XK_INLINE XkInt32		xkIClamp(const XkInt32 x, const XkInt32 min, const XkInt32 max) { return(x < min ? min : (x > max ? max : x)); }
XKMATH_API XK_INLINE XkUInt32		xkUClamp(const XkUInt32 x, const XkUInt32 min, const XkUInt32 max) { return(x < min ? min : (x > max ? max : x)); }
XKMATH_API XK_INLINE XkInt64		xkLIClamp(const XkInt64 x, const XkInt64 min, const XkInt64 max) { return(x < min ? min : (x > max ? max : x)); }
XKMATH_API XK_INLINE XkUInt64		xkLUClamp(const XkUInt64 x, const XkUInt64 min, const XkUInt64 max) { return(x < min ? min : (x > max ? max : x)); }

extern XKMATH_API XkFloat32			xkFAbs(const XkFloat32);
extern XKMATH_API XkFloat64			xkDAbs(const XkFloat64);
extern XKMATH_API XkInt32				xkIAbs(const XkInt32);
extern XKMATH_API XkInt64				xkLIAbs(const XkInt64);

/* ########## FUNCTIONS MACROS SECTION ########## */
#define xkCos(x) _Generic((x),		\
	XkFloat32: xkFCos,							\
  XkFloat64: xkDCos)(x)

#define xkCosA(x) _Generic((x),		\
	XkFloat32: xkFCosA,							\
  XkFloat64: xkDCosA)(x)

#define xkCosH(x) _Generic((x),		\
	XkFloat32: xkFCosH,							\
  XkFloat64: xkDCosH)(x)

#define xkCosAH(x) _Generic((x),	\
	XkFloat32: xkFCosAH,						\
  XkFloat64: xkDCosAH)(x)

#define xkSin(x) _Generic((x),		\
	XkFloat32: xkFSin,							\
  XkFloat64: xkDSin)(x)

#define xkSinA(x) _Generic((x),		\
	XkFloat32: xkFSinA,							\
  XkFloat64: xkDSinA)(x)

#define xkSinH(x) _Generic((x),		\
	XkFloat32: xkFSinH,							\
  XkFloat64: xkDSinH)(x)

#define xkSinAH(x) _Generic((x),	\
	XkFloat32: xkFSinAH,						\
  XkFloat64: xkDSinAH)(x)

#define xkTan(x) _Generic((x),		\
	XkFloat32: xkFTan,							\
  XkFloat64: xkDTan)(x)

#define xkTanA(x) _Generic((x),		\
	XkFloat32: xkFTanA,							\
  XkFloat64: xkDTanA)(x)

#define xkTanH(x) _Generic((x),		\
	XkFloat32: xkFTanH,							\
  XkFloat64: xkDTanH)(x)

#define xkTanAH(x) _Generic((x),	\
	XkFloat32: xkFTanAH,						\
  XkFloat64: xkDTanAH)(x)

#define xkLog(x) _Generic((x),		\
	XkFloat32: xkFLog,							\
  XkFloat64: xkDLog)(x)

#define xkLog2(x) _Generic((x),		\
	XkFloat32: xkFLog2,							\
  XkFloat64: xkDLog2)(x)

#define xkExp(x) _Generic((x),		\
	XkFloat32: xkFExp,							\
  XkFloat64: xkDExp)(x)

#define xkExp2(x) _Generic((x),		\
	XkFloat32: xkFExp2,							\
  XkFloat64: xkDExp2)(x)

#define xkPow(x) _Generic((x),		\
	XkFloat32: xkFPow,							\
  XkFloat64: xkDPow)(x)

#define xkSqrt(x) _Generic((x),		\
	XkFloat32: xkFSqrt,							\
  XkFloat64: xkDSqrt)(x)


#define xkCbrt(x) _Generic((x),		\
	XkFloat32: xkFCbrt,							\
  XkFloat64: xkDCbrt)(x)

#define xkRound(x) _Generic((x),	\
	XkFloat32: xkFRound,						\
	XkFloat64: xkDRound)(x)

#define xkCeil(x) _Generic((x),		\
	XkFloat32: xkFCeil,							\
  XkFloat64: xkDCeil)(x)

#define xkFloor(x) _Generic((x),	\
	XkFloat32: xkFFloor,						\
  XkFloat64: xkDFloor)(x)

#define xkModF(x) _Generic((x),		\
	XkFloat32: xkFModF,							\
  XkFloat64: xkDModF)(x)

#define xkFMod(x) _Generic((x),		\
	XkFloat32: xkFMod,							\
  XkFloat64: xkDMod)(x)

#define xkMin(x) _Generic((x),		\
	XkFloat32: xkFMin,							\
  XkFloat64: xkDMin,							\
  XkInt32: xkIMin,								\
  XkUInt32: xkUMin,								\
  XkInt64: xkLIMin,								\
  XkUInt64: xkLUMin)(x)

#define xkMax(x) _Generic((x),		\
	XkFloat32: xkFMax,							\
  XkFloat64: xkDMax,							\
  XkInt32: xkIMax,								\
  XkUInt32: xkUMax,								\
  XkInt64: xkLIMax,								\
  XkUInt64: xkLUMax)(x)

#define xkClamp(x) _Generic((x),	\
	XkFloat32: xkFClamp,						\
  XkFloat64: xkDClamp,						\
  XkInt32: xkIClamp,							\
  XkUInt32: xkUClamp,							\
  XkInt64: xkLIClamp,							\
  XkUInt64: xkLUClamp)(x)

#define xkAbs(x) _Generic((x),		\
	XkFloat32: xkFAbs,							\
  XkFloat64: xkDAbs,							\
  XkInt32: xkIAbs,								\
  XkInt64: xkLIAbs)(x)

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
