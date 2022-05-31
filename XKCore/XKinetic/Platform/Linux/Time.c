#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_LINUX)

#include <sys/time.h>
#include "XKinetic/Platform/Linux/Internal.h"

XkSize __xkGetTime(void) {
	struct timeval tmv;
	gettimeofday(&tmv, NULL);
	return((XkSize)tmv.tv_sec);
}

#endif // XK_PLATFORM_LINUX

