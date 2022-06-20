#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

XKCORE_API XkResult xkOpenFile(XkFile*, const XkString, const XkFileFlag);
XKCORE_API XkResult xkOpenAsyncFile(XkFile*, const XkString, const XkFileFlag);
XKCORE_API void xkCloseFile(XkFile);

XKCORE_API XkSize xkFileSize(XkFile);

XKCORE_API void xkCreateFile(const XkString);
XKCORE_API void xkRemoveFile(const XkString);

XKCORE_API void xkRenameFile(const XkString, const XkString);

XKCORE_API XkSize xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XKCORE_API void xkWriteFile(XkFile, const XkString, const XkSize);
XKCORE_API void xkReadFile(XkFile, XkString, const XkSize);

XKCORE_API void xkAsyncWriteFile(XkFile, const XkString, const XkSize);
XKCORE_API void xkAsyncReadFile(XkFile, XkString, const XkSize);

#ifdef __cplusplus
}
#endif // __cplusplus
