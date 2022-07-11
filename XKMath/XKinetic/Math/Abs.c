/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Internal.h"

/* ########## FUNCTIONS SECTION ########## */
XkFloat32 xkFAbs(const XkFloat32 x) {
	union {
		XkFloat32 f32; 
		XkUInt32 u32;
	} u = {.f32 = x};

	u.u32 &= XK_INT32_MAX;

	return(u.f32);
}

XkFloat64 xkDAbs(const XkFloat64 x) {
	union {
		XkFloat64 f64; 
		XkUInt64 u64;
	} u = {.f64 = x};

	u.u64 &= XK_UINT64_C(-1) / 2;

	return(u.f64);
}

XkInt32 xkIAbs(const XkInt32 x) {
	return(x > 0 ? x : -x);
}

XkInt64 xkLIAbs(const XkInt64 x) {
	return(x > 0 ? x : -x);
}
