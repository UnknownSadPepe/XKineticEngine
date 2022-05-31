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

XKCORE_API XkSize xkGetTime(void);
XKCORE_API void xkTimeFormat(XkTime* const, const XkSize);
XKCORE_API XkSize xkTimeStringFormat(XkTime* const, XkChar8*, const XkChar8*);

