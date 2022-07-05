#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API void				xkStringFromString8(XkString, XkString8);
extern XKCORE_API void				xkNStringFromString8(XkString, XkString8, const XkSize);

extern XKCORE_API void				xkStringFromString16(XkString, XkString16);
extern XKCORE_API void				xkNStringFromString16(XkString, XkString16, const XkSize);

extern XKCORE_API void				xkStringFromString32(XkString, XkString32);
extern XKCORE_API void				xkNStringFromString32(XkString, XkString32, const XkSize);

extern XKCORE_API void				xkStringFromWString(XkString, XkWString);
extern XKCORE_API void				xkNStringFromWString(XkString, XkWString, const XkSize);

extern XKCORE_API void				xkString8FromString(XkString8, XkString);
extern XKCORE_API void				xkNString8FromString(XkString8, XkString, const XkSize);

extern XKCORE_API void				xkString8FromString16(XkString8, XkString16);
extern XKCORE_API void				xkNString8FromString16(XkString8, XkString16, const XkSize);

extern XKCORE_API void				xkString8FromString32(XkString8, XkString32);
extern XKCORE_API void				xkNString8FromString32(XkString8, XkString32, const XkSize);

extern XKCORE_API void				xkString8FromWString(XkString8, XkWString);
extern XKCORE_API void				xkNString8FromWString(XkString8, XkWString, const XkSize);

extern XKCORE_API void				xkString16FromString(XkString16, XkString);
extern XKCORE_API void				xkNString16FromString(XkString16, XkString, const XkSize);

extern XKCORE_API void				xkString16FromString8(XkString16, XkString8);
extern XKCORE_API void				xkNString16FromString8(XkString16, XkString8, const XkSize);

extern XKCORE_API void				xkString16FromString32(XkString16, XkString32);
extern XKCORE_API void				xkNString16FromString32(XkString16, XkString32, const XkSize);

extern XKCORE_API void				xkString16FromWString(XkString16, XkWString);
extern XKCORE_API void				xkNString16FromWString(XkString16, XkWString, const XkSize);

extern XKCORE_API void				xkString32FromString(XkString32, XkString);
extern XKCORE_API void				xkNString32FromString(XkString32, XkString, const XkSize);

extern XKCORE_API void				xkString32FromString8(XkString32, XkString8);
extern XKCORE_API void				xkNString32FromString8(XkString32, XkString8, const XkSize);

extern XKCORE_API void				xkString32FromString16(XkString32, XkString16);
extern XKCORE_API void				xkNString32FromString16(XkString32, XkString16, const XkSize);

extern XKCORE_API void				xkString32FromWString(XkString32, XkWString);
extern XKCORE_API void				xkNString32FromWString(XkString32, XkWString, const XkSize);

extern XKCORE_API void				xkWStringFromString(XkWString, XkString);
extern XKCORE_API void				xkNWStringFromString(XkWString, XkString, const XkSize);

extern XKCORE_API void				xkWStringFromString8(XkWString, XkString8);
extern XKCORE_API void				xkNWStringFromString8(XkWString, XkString8, const XkSize);

extern XKCORE_API void				xkWStringFromString16(XkWString, XkString16);
extern XKCORE_API void				xkNWStringFromString16(XkWString, XkString16, const XkSize);

extern XKCORE_API void				xkWStringFromString32(XkWString, XkString32);
extern XKCORE_API void				xkNWStringFromString32(XkWString, XkString32, const XkSize);

extern XKCORE_API XkSize 			xkStringLength(XkString);
extern XKCORE_API XkString 		xkCopyString(XkString, XkString);
extern XKCORE_API XkString 		xkNCopyString(XkString, XkString, const XkSize);
extern XKCORE_API XkString 		xkConcatString(XkString, XkString);
extern XKCORE_API XkString 		xkNConcatString(XkString, XkString, const XkSize);
extern XKCORE_API XkInt32 		xkCompareString(XkString, XkString);
extern XKCORE_API XkInt32 		xkNCompareString(XkString, XkString, const XkSize);
extern XKCORE_API XkString 		xkTokenString(XkString, XkString*, XkString);
extern XKCORE_API XkString 		xkNTokenString(XkString, XkString*, XkString, const XkSize);
extern XKCORE_API XkString 		xkDuplicateString(XkString);
extern XKCORE_API XkString 		xkNDuplicateString(XkString, const XkSize);

extern XKCORE_API XkSize 			xkStringFormat(XkString, XkString, ...);
extern XKCORE_API XkSize 			xkStringNFormat(XkString, const XkSize, XkString, ...);
extern XKCORE_API XkSize 			xkStringFFormat(XkString, XkString, XkArgs);
extern XKCORE_API XkSize 			xkStringNFFormat(XkString, const XkSize, XkString, XkArgs);

extern XKCORE_API XkSize 			xkString8Length(XkString8);
extern XKCORE_API XkString8 	xkCopyString8(XkString8, XkString8);
extern XKCORE_API XkString8 	xkNCopyString8(XkString8, XkString8, const XkSize);
extern XKCORE_API XkString8 	xkConcatString8(XkString8, XkString8);
extern XKCORE_API XkString8 	xkNConcatString8(XkString8, XkString8, const XkSize);
extern XKCORE_API XkInt32 		xkCompareString8(XkString8, XkString8);
extern XKCORE_API XkInt32 		xkNCompareString8(XkString8, XkString8, const XkSize);
extern XKCORE_API XkString8 	xkTokenString8(XkString8, XkString8*, XkString8);
extern XKCORE_API XkString8 	xkNTokenString8(XkString8, XkString8*, XkString8, const XkSize);
extern XKCORE_API XkString8 	xkDuplicateString8(XkString8);
extern XKCORE_API XkString8 	xkNDuplicateString8(XkString8, const XkSize);

extern XKCORE_API XkSize 			xkString16Length(XkString16);
extern XKCORE_API XkString16 	xkCopyString16(XkString16, XkString16);
extern XKCORE_API XkString16 	xkNCopyString16(XkString16, XkString16, const XkSize);
extern XKCORE_API XkString16 	xkConcatString16(XkString16, XkString16);
extern XKCORE_API XkString16 	xkNConcatString16(XkString16, XkString16, const XkSize);
extern XKCORE_API XkInt32 		xkCompareString16(XkString16, XkString16);
extern XKCORE_API XkInt32 		xkNCompareString16(XkString16, XkString16, const XkSize);
extern XKCORE_API XkString16 	xkTokenString16(XkString16, XkString16*, XkString16);
extern XKCORE_API XkString16 	xkNTokenString16(XkString16, XkString16*, XkString16, const XkSize);
extern XKCORE_API XkString16 	xkDuplicateString16(XkString16);
extern XKCORE_API XkString16 	xkNDuplicateString16(XkString16, const XkSize);

extern XKCORE_API XkSize 			xkString32Length(XkString32);
extern XKCORE_API XkString32 	xkCopyString32(XkString32, XkString32);
extern XKCORE_API XkString32 	xkNCopyString32(XkString32, XkString32, const XkSize);
extern XKCORE_API XkString32 	xkConcatString32(XkString32, XkString32);
extern XKCORE_API XkString32 	xkNConcatString32(XkString32, XkString32, const XkSize);
extern XKCORE_API XkInt32 		xkCompareString32(XkString32, XkString32);
extern XKCORE_API XkInt32 		xkNCompareString32(XkString32, XkString32, const XkSize);
extern XKCORE_API XkString32 	xkTokenString32(XkString32, XkString32*, XkString32);
extern XKCORE_API XkString32 	xkNTokenString32(XkString32, XkString32*, XkString32, const XkSize);
extern XKCORE_API XkString32 	xkDuplicateString32(XkString32);
extern XKCORE_API XkString32 	xkNDuplicateString32(XkString32, const XkSize);

extern XKCORE_API XkSize 			xkWStringLength(XkWString);
extern XKCORE_API XkWString 	xkCopyWString(XkWString, XkWString);
extern XKCORE_API XkWString 	xkNCopyWString(XkWString, XkWString, const XkSize);
extern XKCORE_API XkWString 	xkConcatWString(XkWString, XkWString);
extern XKCORE_API XkWString 	xkNConcatWString(XkWString, XkWString, const XkSize);
extern XKCORE_API XkInt32 		xkCompareWString(XkWString, XkWString);
extern XKCORE_API XkInt32 		xkNCompareWString(XkWString, XkWString, const XkSize);
extern XKCORE_API XkWString 	xkTokenWString(XkWString, XkWString*, XkWString);
extern XKCORE_API XkWString 	xkNTokenWString(XkWString, XkWString*, XkWString, const XkSize);
extern XKCORE_API XkWString 	xkDuplicateWString(XkWString);
extern XKCORE_API XkWString 	xkNDuplicateWString(XkWString, const XkSize);

extern XKCORE_API XkSize 			xkWStringFormat(XkWString, XkWString, ...);
extern XKCORE_API XkSize 			xkWStringNFormat(XkWString, const XkSize, XkWString, ...);
extern XKCORE_API XkSize 			xkWStringFFormat(XkWString, XkWString, XkArgs);
extern XKCORE_API XkSize 			xkWStringNFFormat(XkWString, const XkSize, XkWString, XkArgs);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
