/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Internal.h"

/* ########## FUNCTIONS SECTION ########## */
XkFloat32 xkFFMod(const XkFloat32 x, const XkFloat32 y) {
	union {
		XkFloat32 f32;
		XkUInt32	u32;
	} ux = {.f32 = x}, uy = {.f32 = y};

	XkInt32 ex = ux.u32	>> 23 & 0xFF;
	XkInt32 ey = uy.u32	>> 23 & 0xFF;

	XkUInt32 sx = ux.u32 & 0x80000000;

	/// NOTE: float load/store to inner loops ruining performance and code size.
	XkUInt32 uxi = ux.u32;

	XkUInt32 i;

	return(0.0f);
}

XkFloat64 xkDFMod(const XkFloat64 x, const XkFloat64 y) {
	union {
		XkFloat64 f64; 
		XkUInt64	u64;
	} ux = {.f64 = x}, uy = {.f64 = y};

	XkInt32 ex = ux.u64 >> 52 & 0x7FF;
	XkInt32 ey = uy.u64 >> 52 & 0x7FF;
	XkInt32 sx = ux.u64 >> 63;

	/// NOTE: float load/store to inner loops ruining performance and code size.
	XkUInt64 uxi = ux.u64;

	XkUInt64 i;

	return(0.0);
}
