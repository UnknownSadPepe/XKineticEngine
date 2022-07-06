/* ########## INCLUDE SECTION ########## */
/// TODO: Remove #include <time.h>.
#include <time.h>
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Time.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
void xkTimeFormat(XkTime* const pTime, const XkSize rawTime) {
	xkAssert(pTime);
	xkAssert(rawTime > 0);

	time_t rt = (time_t)rawTime;
	struct tm t = *localtime(&rt);

	pTime->second		= (XkSize)t.tm_sec;
	pTime->minute		= (XkSize)t.tm_min;
	pTime->hour 		= (XkSize)t.tm_hour;
	pTime->mDay 		= (XkSize)t.tm_mday;
	pTime->month 		= (XkSize)t.tm_mon;
	pTime->year 		= (XkSize)t.tm_year;
	pTime->wDay 		= (XkSize)t.tm_wday;
	pTime->yDay 		= (XkSize)t.tm_yday;
}

XkSize xkTimeStringFormat(XkTime* const pTime, XkString buffer, const XkSize size, const XkString format) {
	xkAssert(pTime);
	xkAssert(buffer);
	xkAssert(size > 0);
	xkAssert(format);

	struct tm t 	= {};
	t.tm_sec 			= (int)pTime->second;
	t.tm_min			= (int)pTime->minute;
	t.tm_hour 		= (int)pTime->hour;
	t.tm_mday 		= (int)pTime->mDay;
	t.tm_mon			= (int)pTime->month;
	t.tm_year 		= (int)pTime->year;
	t.tm_wday 		= (int)pTime->wDay;
	t.tm_yday 		= (int)pTime->yDay;

	/// TODO: Remove 'strftime'.
	size_t formatSize = strftime(buffer, size, format, &t);
	
	return((XkSize)formatSize);
}

