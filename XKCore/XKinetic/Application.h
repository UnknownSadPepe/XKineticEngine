#pragma once

#include "XKinetic/XKinetic.h"

typedef struct {
	XkChar8* pName;
	struct {
		XkUInt32 major;
		XkUInt32 minor;	
		XkUInt32 patch;	
	}	version;
} XkApplicationConfig;

typedef struct XkApplication XkApplication;

extern XkApplication _xkApplication;

XK_IMPORT XkResult xkCreateApplication(const XkSize, const XkChar8**);
XK_IMPORT void xkDestroyApplication();
XK_IMPORT void xkUpdateApplication();
