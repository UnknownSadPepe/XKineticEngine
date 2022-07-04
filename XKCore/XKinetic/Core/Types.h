#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
XK_INLINE XKCORE_API XkBool xkAlbet(const XkUInt32 chr) {
	return((chr | 32) - 'a' < 26);
}

XK_INLINE XKCORE_API XkBool xkDigit(const XkUInt32 chr) {
	return((chr - '0') < 10);
}

XK_INLINE XKCORE_API XkBool xkAlnum(const XkUInt32 chr) {
	return(xkAlbet(chr) || xkDigit(chr));
}

XK_INLINE XKCORE_API XkBool xkDelim(const XkChar chr, XkString delim) {
	while(*delim) {
		if(chr == *delim) {
			return(XK_TRUE);
		}
		++delim;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool xkDelim8(const XkChar chr, XkString8 delim8) {
	while(*delim8) {
		if(chr == *delim8) {
			return(XK_TRUE);
		}
		++delim8;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool xkDelim16(const XkChar chr, XkString16 delim16) {
	while(*delim16) {
		if(chr == *delim16) {
			return(XK_TRUE);
		}
		++delim16;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool xkDelim32(const XkChar chr, XkString32 delim32) {
	while(*delim32) {
		if(chr == *delim32) {
			return(XK_TRUE);
		}
		++delim32;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool xkWDelim(const XkWChar chr, XkWString wdelim) {
	while(*wdelim) {
		if(chr == *wdelim) {
			return(XK_TRUE);
		}
		++wdelim;
	}
	return(XK_FALSE);
}

XK_INLINE XKCORE_API XkBool xkLower(const XkUInt32 chr) {
	return((chr - 'a') < 26);
}

XK_INLINE XKCORE_API XkBool xkUpper(const XkUInt32 chr) {
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
