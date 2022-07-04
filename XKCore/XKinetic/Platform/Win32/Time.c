/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Time.h"

/* ########## FUNCTIONS SECTION ########## */
XkSize xkGetTime() {
	return((XkSize)(GetTickCount64() / 1000));
}
