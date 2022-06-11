#pragma once

#include "XKinetic/XKCore.h"

XK_INLINE XkBool32 xkAlbet(const XkInt32 chr) {
	return((XkUInt32)chr | 32) - 'a' < 26;
}

XK_INLINE XkBool32 xkDigit(const XkInt32 chr) {
	return(XkUInt32)chr - '0' < 10;
}

XK_INLINE XkBool32 xkAlnum(const XkInt32 chr) {
	return(xkAlbet(chr) || xkDigit(chr));
}

XK_INLINE XkBool32 xkDelim(const XkChar8 chr, XkString delim) {
	while(*delim) {
		if(chr == *delim) {
			return(XK_TRUE);
		}
		++delim;
	}
	return(XK_FALSE);
}

XK_INLINE XkBool32 xkLower(const XkInt32 chr) {
	return((XkUInt32)chr - 'a' < 26);
}

XK_INLINE XkBool32 xkUpper(const XkInt32 chr) {
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
