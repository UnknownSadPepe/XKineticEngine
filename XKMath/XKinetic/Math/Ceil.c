#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Internal.h"

XkFloat32 xkFCeil(const XkFloat32 x) {
	// Musl Libc source (https://github.com/bminor/musl/blob/master/src/math/ceilf.c).

	union {XkFloat32 f; XkUInt32 i;} u = {x};
	int e = (int)(u.i >> 23 & 0xff) - 0x7f;
	XkUInt32 m;

	if(e >= 23) {
		return x;
	}

	if(e >= 0) {
		m = 0x007fffff >> e;

		if((u.i & m) == 0) {
			return x;
		}

		FORCE_EVAL(x + 0x1p120f);
		if(u.i >> 31 == 0) {
			u.i += m;
		}

		u.i &= ~m;
	} else {
		FORCE_EVAL(x + 0x1p120f);
		if(u.i >> 31) {
			u.f = -0.0;
		} else if (u.i << 1) {
			u.f = 1.0;
		}
	}
	return(u.f);
}

XkFloat64 xkDCeil(const XkFloat64 x) {
	// Musl Libc source (https://github.com/bminor/musl/blob/master/src/math/ceil.c).

	static const XkFloat64 toint = 1 / XK_FLOAT64_EPSILON;

	union {XkFloat64 f; XkUInt64 i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	XkFloat64 y;

	if(e >= 0x3ff+52 || x == 0) {
		return x;
	}

	/* y = int(x) - x, where int(x) is an integer neighbor of x */
	if(u.i >> 63) {
		y = x - toint + toint - x;
	} else {
		y = x + toint - toint - x;
	}
	/* special case because of non-nearest rounding modes */
	if(e <= 0x3ff-1) {
		FORCE_EVAL(y);
		return(u.i >> 63 ? -0.0 : 1);
	}
	if(y < 0) {
		return(x + y + 1);
	}

	return(x + y);
}
