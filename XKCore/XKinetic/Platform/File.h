#pragma once

#include "XKinetic/XKCore.h"

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

typedef struct XkFile* XkFile;

XK_EXPORT XkResult xkOpenFile(XkFile*, const XkString, const XkFileFlag);
XK_EXPORT XkResult xkOpenAsyncFile(XkFile*, const XkString, const XkFileFlag);
XK_EXPORT void xkCloseFile(XkFile);

XK_EXPORT void xkCreateFile(const XkString);
XK_EXPORT void xkRemoveFile(const XkString);

XK_EXPORT void xkRenameFile(const XkString, const XkString);

XK_EXPORT XkSize xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XK_EXPORT void xkWriteFile(XkFile, const XkString, const XkSize);
XK_EXPORT void xkReadFile(XkFile, XkString, const XkSize);

XK_EXPORT void xkAsyncWriteFile(XkFile, const XkString, const XkSize);
XK_EXPORT void xkAsyncReadFile(XkFile, XkString, const XkSize);
