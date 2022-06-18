#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XKCORE_API XkSize xkStringLength(XkString);
XKCORE_API XkString xkCopyString(XkString, XkString);
XKCORE_API XkString xkNCopyString(XkString, XkString, const XkSize);
XKCORE_API XkString xkConcatString(XkString, XkString);
XKCORE_API XkString xkNConcatString(XkString, XkString, const XkSize);
XKCORE_API XkInt32 xkCompareString(XkString, XkString);
XKCORE_API XkInt32 xkNCompareString(XkString, XkString, const XkSize);
XKCORE_API XkString xkTokenString(XkString, XkString);
XKCORE_API XkString xkNTokenString(XkString, XkString, const XkSize);
XKCORE_API XkString xkDuplicateString(XkString);
XKCORE_API XkString xkNDuplicateString(XkString, const XkSize);

XKCORE_API XkSize xkStringFormat(XkString, XkString, ...);
XKCORE_API XkSize xkStringNFormat(XkString, const XkSize, XkString, ...);
XKCORE_API XkSize xkStringFFormat(XkString, XkString, XkArgs);
XKCORE_API XkSize xkStringNFFormat(XkString, const XkSize, XkString, XkArgs);

#ifdef __cplusplus
}
#endif // __cplusplus
