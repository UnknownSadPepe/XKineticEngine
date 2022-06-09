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

XK_EXPORT XkResult xkOpenFile(XkFile*, const XkChar8*, const XkFileFlag);
XK_EXPORT XkResult xkOpenAsyncFile(XkFile*, const XkChar8*, const XkFileFlag);
XK_EXPORT void xkCloseFile(XkFile);

XK_EXPORT void xkCreateFile(const XkChar8*);
XK_EXPORT void xkRemoveFile(const XkChar8*);

XK_EXPORT void xkRenameFile(const XkChar8*, const XkChar8*);

XK_EXPORT XkSize xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XK_EXPORT void xkWriteFile(XkFile, const XkChar8*, const XkSize);
XK_EXPORT void xkReadFile(XkFile, XkChar8*, const XkSize);

XK_EXPORT void xkAsyncWriteFile(XkFile, const XkChar8*, const XkSize);
XK_EXPORT void xkAsyncReadFile(XkFile, XkChar8*, const XkSize);
