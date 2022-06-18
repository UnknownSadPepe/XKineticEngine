#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XKCORE_API XkSize xkWStringLength(XkWString);
XKCORE_API XkWString xkCopyWString(XkWString, XkWString);
XKCORE_API XkWString xkNCopyWString(XkWString, XkWString, const XkSize);
XKCORE_API XkWString xkConcatWString(XkWString, XkWString);
XKCORE_API XkWString xkNConcatWString(XkWString, XkWString, const XkSize);
XKCORE_API XkInt32 xkCompareWString(XkWString, XkWString);
XKCORE_API XkInt32 xkNCompareWString(XkWString, XkWString, const XkSize);
XKCORE_API XkWString xkTokenWString(XkWString, XkWString);
XKCORE_API XkWString xkNTokenWString(XkWString, XkWString, const XkSize);
XKCORE_API XkWString xkDuplicateWString(XkWString);
XKCORE_API XkWString xkNDuplicateWString(XkWString, const XkSize);

XKCORE_API XkSize xkWStringFormat(XkWString, XkWString, ...);
XKCORE_API XkSize xkWStringNFormat(XkWString, const XkSize, XkWString, ...);
XKCORE_API XkSize xkWStringFFormat(XkWString, XkWString, XkArgs);
XKCORE_API XkSize xkWStringNFFormat(XkWString, const XkSize, XkWString, XkArgs);

#ifdef __cplusplus
}
#endif // __cplusplus
