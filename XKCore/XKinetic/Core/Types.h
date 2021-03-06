#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
XK_INLINE XKCORE_API XkBool8 xkAlbet(const XkUInt32 chr) {
	return((chr | 32) - 'a' < 26);
}

XK_INLINE XKCORE_API XkBool8 xkDigit(const XkUInt32 chr) {
	return((chr - '0') < 10);
}

XK_INLINE XKCORE_API XkBool8 xkAlnum(const XkUInt32 chr) {
	return(xkAlbet(chr) || xkDigit(chr));
}

XK_INLINE XKCORE_API XkBool8 xkDelim(const XkChar chr, XkString delim) {
	while(*delim) {
		if(chr == *delim) {
			return(XK_TRUE);
		}
		++delim;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool8 xkDelim8(const XkChar8 chr, XkString8 delim8) {
	while(*delim8) {
		if(chr == *delim8) {
			return(XK_TRUE);
		}
		++delim8;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool8 xkDelim16(const XkChar16 chr, XkString16 delim16) {
	while(*delim16) {
		if(chr == *delim16) {
			return(XK_TRUE);
		}
		++delim16;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool8 xkDelim32(const XkChar32 chr, XkString32 delim32) {
	while(*delim32) {
		if(chr == *delim32) {
			return(XK_TRUE);
		}
		++delim32;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool8 xkWDelim(const XkWChar chr, XkWString wdelim) {
	while(*wdelim) {
		if(chr == *wdelim) {
			return(XK_TRUE);
		}
		++wdelim;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool8 xkLower(const XkUInt32 chr) {
	return((chr - 'a') < 26);
}

XK_INLINE XKCORE_API XkBool8 xkUpper(const XkUInt32 chr) {
	return((chr - 'A') < 26);
}

XK_INLINE XKCORE_API XkUInt32 xkToLower(const XkUInt32 chr) {
	if(xkUpper(chr)) {
		return(chr | 32);
	}
	return(chr);
}

XK_INLINE XKCORE_API XkUInt32 xkToUpper(const XkUInt32 chr) {
	if(xkLower(chr)) {
		return(chr & 0x5F);
	}
	return(chr);
}

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
