#pragma once

#include "XKinetic/XKMath.h"
#include "XKinetic/Math/Math.h"

typedef struct {
	union {
		struct { XkFloat32 x, y; };
		struct { XkFloat32 u, v; };
	};
} XkVec2;

typedef struct {
	union {
		struct { XkFloat64 x, y; };
		struct { XkFloat64 u, v; };
	};
} XkDVec2;

XK_INLINE XkVec2 xkVec2Add(const XkVec2 a, const XkVec2 b) {
	return((XkVec2){
		.x = a.x + b.x,
		.y = a.y + b.y
	});
}

XK_INLINE XkDVec2 xkDVec2Add(const XkDVec2 a, const XkDVec2 b) {
	return((XkDVec2){
		.x = a.x + b.x,
		.y = a.y + b.y
	});
}

XK_INLINE XkVec2 xkVec2Sub(const XkVec2 a, const XkVec2 b) {
	return((XkVec2){
		.x = a.x - b.x,
		.y = a.y - b.y
	});
}

XK_INLINE XkDVec2 xkDVec2Sub(const XkDVec2 a, const XkDVec2 b) {
	return((XkDVec2){
		.x = a.x - b.x,
		.y = a.y - b.y
	});
}

XK_INLINE XkVec2 xkVec2Mul(const XkVec2 a, const XkVec2 b) {
	return((XkVec2){
		.x = a.x * b.x,
		.y = a.y * b.y
	});
}

XK_INLINE XkDVec2 xkDVec2Mul(const XkDVec2 a, const XkDVec2 b) {
	return((XkDVec2){
		.x = a.x * b.x,
		.y = a.y * b.y
	});
}

XK_INLINE XkVec2 xkVec2Div(const XkVec2 a, const XkVec2 b) {
	return((XkVec2){
		.x = a.x / b.x,
		.y = a.y / b.y
	});
}

XK_INLINE XkDVec2 xkDVec2Div(const XkDVec2 a, const XkDVec2 b) {
	return((XkDVec2){
		.x = a.x / b.x,
		.y = a.y / b.y
	});
}
