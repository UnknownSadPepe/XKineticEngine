#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"

XKCORE_API XkSize xkStringLength(const XkChar8*);
XKCORE_API XkChar8* xkCopyString(XkChar8*, const XkChar8*);
XKCORE_API XkChar8* xkNCopyString(XkChar8*, const XkChar8*, const XkSize);
XKCORE_API XkChar8* xkConcatString(XkChar8*, const XkChar8*);
XKCORE_API XkChar8* xkNConcatString(XkChar8*, const XkChar8*, const XkSize);
XKCORE_API XkInt32 xkCompareString(const XkChar8*, const XkChar8*);
XKCORE_API XkInt32 xkNCompareString(const XkChar8*, const XkChar8*, const XkSize);
XKCORE_API XkChar8* xkTokenString(XkChar8*, const XkChar8*);
XKCORE_API XkChar8* xkNTokenString(XkChar8*, const XkChar8*, const XkSize);

XKCORE_API XkSize xkStringFormat(XkChar8*, const XkChar8*, ...);
XKCORE_API XkSize xkStringNFormat(XkChar8*, const XkSize, const XkChar8*, ...);
XKCORE_API XkSize xkStringFFormat(XkChar8*, const XkChar8*, XkArgs);
XKCORE_API XkSize xkStringNFFormat(XkChar8*, const XkSize, const XkChar8*, XkArgs);
