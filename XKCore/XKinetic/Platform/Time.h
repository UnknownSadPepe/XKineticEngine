#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkTime_T {
	XkSize second;
	XkSize minute;
	XkSize hour;
	XkSize wDay;
	XkSize mDay;
	XkSize month;
	XkSize year;
	XkSize yDay;
} XkTime;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkSize 	xkGetTime();
extern XKCORE_API void 		xkTimeFormat(XkTime* const, const XkSize);
extern XKCORE_API XkSize 	xkTimeStringFormat(XkTime* const, XkString, const XkSize, const XkString);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus
