#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Time.h"

#if defined(XK_UNIX)

#include <sys/time.h>

XkSize xkGetTime(void) {
	struct timeval tmv;
	gettimeofday(&tmv, NULL);
	return((XkSize)tmv.tv_sec);
}

#endif // XK_UNIX

