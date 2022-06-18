#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XK_INLINE XkBool xkAlbet(const XkInt32 chr) {
	return((XkUInt32)chr | 32) - 'a' < 26;
}

XK_INLINE XkBool xkDigit(const XkInt32 chr) {
	return(XkUInt32)chr - '0' < 10;
}

XK_INLINE XkBool xkAlnum(const XkInt32 chr) {
	return(xkAlbet(chr) || xkDigit(chr));
}

XK_INLINE XkBool xkDelim(const XkChar chr, XkString delim) {
	while(*delim) {
		if(chr == *delim) {
			return(XK_TRUE);
		}
		++delim;
	}
	return(XK_FALSE);
}

XK_INLINE XkBool xkWDelim(const XkWChar chr, XkWString delim) {
	while(*delim) {
		if(chr == *delim) {
			return(XK_TRUE);
		}
		++delim;
	}
	return(XK_FALSE);
}

XK_INLINE XkBool xkLower(const XkInt32 chr) {
	return((XkUInt32)chr - 'a' < 26);
}

XK_INLINE XkBool xkUpper(const XkInt32 chr) {
	return((XkUInt32)chr - 'A' < 26);
}

XK_INLINE XkInt32 xkToLower(const XkInt32 chr) {
	if(xkUpper(chr)) {
		return(chr | 32);
	}
	return(chr);
}

XK_INLINE XkInt32 xkToUpper(const XkInt32 chr) {
	if(xkLower(chr)) {
		return(chr & 0x5f);
	}
	return(chr);
}

#ifdef __cplusplus
}
#endif // __cplusplus
