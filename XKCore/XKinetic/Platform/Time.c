/*TODO: remove #include <time.h>*/
#include <time.h>
#include "XKinetic/Platform/Time.h"

void xkTimeFormat(XkTime* const pTime, const XkSize rawTime) {
	time_t rt = (time_t)rawTime;
	struct tm t = {0};
	localtime_s(&t, &rt);

  pTime->second = (XkSize)t.tm_sec;
  pTime->minute = (XkSize)t.tm_min;
  pTime->hour = (XkSize)t.tm_hour;
  pTime->mDay = (XkSize)t.tm_mday;
  pTime->month = (XkSize)t.tm_mon;
  pTime->year = (XkSize)t.tm_year;
  pTime->wDay = (XkSize)t.tm_wday;
  pTime->yDay = (XkSize)t.tm_yday;
}

XkSize xkTimeStringFormat(XkTime* const pTime, XkString buffer, const XkSize size, const XkString format) {
	struct tm t = {
		.tm_sec = (int)pTime->second,
		.tm_min = (int)pTime->minute,
		.tm_hour = (int)pTime->hour,
		.tm_mday = (int)pTime->mDay,
		.tm_mon = (int)pTime->month,
		.tm_year = (int)pTime->year,
		.tm_wday = (int)pTime->wDay,
		.tm_yday = (int)pTime->yDay
	};

	return((XkSize)strftime(buffer, size, format, &t));
}

