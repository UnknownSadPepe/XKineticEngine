#pragma once

#include "XKinetic/XKinetic.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	XkString name;
	struct {
		XkUInt32 major;
		XkUInt32 minor;	
		XkUInt32 patch;	
	}	version;
} XkApplicationConfig;

typedef struct XkApplication XkApplication;

extern XkApplication _xkApplication;

extern XkResult xkCreateApplication(const XkSize, const XkString*);
extern void xkDestroyApplication(void);
extern void xkUpdateApplication(void);

#ifdef __cplusplus
}
#endif // __cplusplus
