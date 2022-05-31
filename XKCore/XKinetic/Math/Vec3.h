#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Math/Math.h"

typedef struct {
	union {
		struct { XkFloat32 x, y, z; };
		struct { XkFloat32 r, g, b; };
		struct { XkFloat32 u, v, w; };
	};
} XkVec3;

typedef struct {
	union {
		struct { XkFloat64 x, y, z; };
		struct { XkFloat64 r, g, b; };
		struct { XkFloat64 u, v, w; };
	};
} XkDVec3;

XK_INLINE XkVec3 xkVec3Add(const XkVec3 a, const XkVec3 b) {
	return((XkVec3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

XK_INLINE XkDVec3 xkDVec3Add(const XkDVec3 a, const XkDVec3 b) {
	return((XkDVec3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

XK_INLINE XkVec3 xkVec3Sub(const XkVec3 a, const XkVec3 b) {
	return((XkVec3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

XK_INLINE XkDVec3 xkDVec3Sub(const XkDVec3 a, const XkDVec3 b) {
	return((XkDVec3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

XK_INLINE XkVec3 xkVec3Mul(const XkVec3 a, const XkVec3 b) {
	return((XkVec3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

XK_INLINE XkDVec3 xkDVec3Mul(const XkDVec3 a, const XkDVec3 b) {
	return((XkDVec3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

XK_INLINE XkVec3 xkVec3Div(const XkVec3 a, const XkVec3 b) {
	return((XkVec3){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z
	});
}

XK_INLINE XkDVec3 xkDVec3Div(const XkDVec3 a, const XkDVec3 b) {
	return((XkDVec3){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z
	});
}
