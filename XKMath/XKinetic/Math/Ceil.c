/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Internal.h"

XkFloat32 xkFCeil(const XkFloat32 x) {
	union {
		XkFloat32 f32; 
		XkUInt32	u32;
	} u = {.f32 = x};
	XkInt32 e = (XkInt32)(u.u32 >> 23 & 0xFF) - 0x7F;
	if(e >= 23) {
		return(x);
	}

	if(e >= 0) {
		XkUInt32 m = 0x007FFFFF >> e;

		if((u.u32 & m) == 0) {
			return(x);
		}

		__xkForceFEval(x + 0x1P120F);
		if(u.u32 >> 31 == 0) {
			u.u32 += m;
		}

		u.u32 &= ~m;
	} else {
		__xkForceFEval(x + 0x1P120F);
		if(u.u32 >> 31) {
			u.f32 = -0.0;
		} else if (u.u32 << 1) {
			u.f32 = 1.0;
		}
	}
	return(u.f32);
}

XkFloat64 xkDCeil(const XkFloat64 x) {
	static const XkFloat64 toint = 1 / XK_FLOAT64_EPSILON;

	union {
		XkFloat64 f64; 
		XkUInt64	u64;
	} u = {.f64 = x};
	XkInt32 e = u.u64 >> 52 & 0x7FF;
	if(e >= 0x3FF + 52 || x == 0) {
		return(x);
	}

	XkFloat64 y;

	/* y = int(x) - x, where int(x) is an integer neighbor of x */
	if(u.u64 >> 63) {
		y = x - toint + toint - x;
	} else {
		y = x + toint - toint - x;
	}
	/* special case because of non-nearest rounding modes */
	if(e <= 0x3ff - 1) {
		__xkForceDEval(y);
		return(u.u64 >> 63 ? -0.0 : 1);
	}

	if(y < 0) {
		return(x + y + 1);
	}

	return(x + y);
}
