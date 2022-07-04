#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkFileFlag_T {
	XK_FILE_FLAG_RO_BIT = 0x0001,
	XK_FILE_FLAG_WO_BIT = 0x0002,
	XK_FILE_FLAG_RW_BIT = 0x0004,
	XK_FILE_FLAG_AP_BIT = 0x0008,
	XK_FILE_FLAG_CR_BIT = 0x0010
} XkFileFlag;

typedef enum XkFileSeek_T {
	XK_FILE_SEEK_SET = 0,
	XK_FILE_SEEK_CUR = 1,
	XK_FILE_SEEK_END = 2
}	XkFileSeek;

typedef struct XkFile_T* XkFile;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkOpenFile(XkFile*, const XkString, const XkFileFlag);
extern XKCORE_API XkResult 	xkOpenAsyncFile(XkFile*, const XkString, const XkFileFlag);
extern XKCORE_API void 			xkCloseFile(XkFile);

extern XKCORE_API XkSize 		xkFileSize(XkFile);

extern XKCORE_API void 			xkCreateFile(const XkString);
extern XKCORE_API void 			xkRemoveFile(const XkString);

extern XKCORE_API void 			xkRenameFile(const XkString, const XkString);

extern XKCORE_API XkSize 		xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

extern XKCORE_API void 			xkWriteFile(XkFile, const XkString, const XkSize);
extern XKCORE_API void 			xkReadFile(XkFile, XkString, const XkSize);

extern XKCORE_API void 			xkAsyncWriteFile(XkFile, const XkString, const XkSize);
extern XKCORE_API void 			xkAsyncReadFile(XkFile, XkString, const XkSize);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus
