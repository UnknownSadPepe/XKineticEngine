#include "XKinetic/Math/Math.h"

XkFloat32 xkFAbs(const XkFloat32 x) {
	// Musl Libc source (https://github.com/bminor/musl/blob/master/src/math/fabsf.c).

	union {XkFloat32 f; XkUInt32 i;} u = {x};
	u.i &= 0x7fffffff;
	return u.f;
}

XkFloat64 xkDAbs(const XkFloat64 x) {
	// Musl Libc source (https://github.com/bminor/musl/blob/master/src/math/fabs.c).

	union {XkFloat64 f; XkUInt64 i;} u = {x};
	u.i &= -1ULL/2;
	return u.f;
}
