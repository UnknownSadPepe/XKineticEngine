#pragma once

#include "XKinetic/XKCore.h"

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
XK_EXPORT XkSize xkTimeStringFormat(XkTime* const, XkString, const XkSize, const XkString);
