#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

typedef struct {
	XkSize second;
	XkSize minute;
	XkSize hour;
	XkSize wDay;
	XkSize mDay;
	XkSize month;
	XkSize year;
	XkSize yDay;
} XkTime;

XK_EXPORT XkSize xkGetTime(void);
XK_EXPORT void xkTimeFormat(XkTime* const, const XkSize);
XK_EXPORT XkSize xkTimeStringFormat(XkTime* const, XkChar8*, const XkChar8*);
