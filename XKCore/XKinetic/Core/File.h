#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"
#include "XKinetic/Platform/External.h"

XK_API_EXPORT XkResult xkFileInitialize(void);
XK_API_EXPORT void xkFileTerminate(void);

XKCORE_API XkResult xkOpenFile(XkFile*, const XkChar8*, const XkFileFlag);
XKCORE_API void xkCloseFile(XkFile);

XKCORE_API XkResult xkCreateFile(XkFile*, const XkChar8*);
XKCORE_API void xkRemoveFile(const XkChar8*);

XKCORE_API void xkRenameFile(const XkChar8*, const XkChar8*);

XKCORE_API XkSize xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XKCORE_API void xkFWriteFile(XkFile, const XkChar8*, ...);
XKCORE_API void xkFReadFile(XkFile, XkChar8*, ...);
XKCORE_API void xkVWriteFile(XkFile, const XkChar8*, XkArgs);
XKCORE_API void xkVReadFile(XkFile, XkChar8*, XkArgs);
XKCORE_API void xkWriteFile(XkFile, const XkChar8*, const XkSize);
XKCORE_API void xkReadFile(XkFile, XkChar8*, const XkSize);
