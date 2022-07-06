/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Time.h"

#include <sys/time.h>

/* ########## FUNCTIONS SECTION ########## */
XkSize xkGetTime() {
	struct timeval tmv;
	gettimeofday(&tmv, NULL);
	
	return((XkSize)tmv.tv_sec);
}
