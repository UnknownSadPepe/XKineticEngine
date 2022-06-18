#pragma once

#include "XKinetic/XKinetic.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	XkString name;
	struct {
		XkUInt32 major;
		XkUInt32 minor;	
		XkUInt32 patch;	
	}	version;
} XkApplicationConfig;

typedef struct XkApplication XkApplication;

extern XkApplication _xkApplication;

XK_IMPORT XkResult xkCreateApplication(const XkSize, const XkWString*);
XK_IMPORT void xkDestroyApplication();
XK_IMPORT void xkUpdateApplication();

#ifdef __cplusplus
}
#endif // __cplusplus
