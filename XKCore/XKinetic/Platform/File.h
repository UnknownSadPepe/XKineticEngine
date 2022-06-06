#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

typedef enum {
	XK_FILE_FLAG_RO_BIT = 1,
	XK_FILE_FLAG_WO_BIT = 2,
	XK_FILE_FLAG_RW_BIT = 4,
	XK_FILE_FLAG_AP_BIT = 8,
	XK_FILE_FLAG_CR_BIT = 16
} XkFileFlag;

typedef enum {
	XK_FILE_SEEK_SET = 0,
	XK_FILE_SEEK_CUR = 1,
	XK_FILE_SEEK_END = 2
}	XkFileSeek;

struct XkFile {
	XK_PLATFORM_FILE;
};

typedef struct XkFile* XkFile;

XK_EXPORT XkResult xkFileInitialize(void);
XK_EXPORT void xkFileTerminate(void);

XK_EXPORT XkResult xkOpenFile(XkFile, const XkChar8*, const XkFileFlag);
XK_EXPORT void xkCloseFile(XkFile);

XK_EXPORT XkResult xkCreateFile(XkFile, const XkChar8*);
XK_EXPORT void xkRemoveFile(const XkChar8*);

XK_EXPORT void xkRenameFile(const XkChar8*, const XkChar8*);

XK_EXPORT XkSize xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XK_EXPORT void xkWriteFile(XkFile, const XkChar8*, const XkSize);
XK_EXPORT void xkReadFile(XkFile, XkChar8*, const XkSize);

XK_EXPORT void xkAsyncWriteFile(XkFile, const XkChar8*, const XkSize);
XK_EXPORT void xkAsyncReadFile(XkFile, XkChar8*, const XkSize);
