#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/Time.h"



XKCORE_API void xkTimeFormat(XkTime* const, const XkSize);
XKCORE_API XkSize xkTimeStringFormat(XkTime* const, XkChar8*, const XkChar8*);
