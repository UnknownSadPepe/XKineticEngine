#pragma once

#include "XKinetic/XKinetic.h"

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
