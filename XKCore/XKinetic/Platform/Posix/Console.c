/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Core/String.h"

#include <unistd.h>

/* ########## MACROS SECTION ########## */
#define XK_CONSOLE_BUFFER_SIZE 1024

#define XK_POSIX_COLOR_RESET			"\e[0m"

#define XK_POSIX_COLOR_FBLACK			"\e[0;30m"
#define XK_POSIX_COLOR_FRED				"\e[0;31m"
#define XK_POSIX_COLOR_FGREEN			"\e[0;32m"
#define XK_POSIX_COLOR_FYELLOW		"\e[0;33m"
#define XK_POSIX_COLOR_FBLUE			"\e[0;34m"
#define XK_POSIX_COLOR_FPURPLE		"\e[0;35m"
#define XK_POSIX_COLOR_FCYAN			"\e[0;36m"
#define XK_POSIX_COLOR_FWHITE			"\e[0;37m"

#define XK_POSIX_COLOR_FUBLACK		"\e[4;30m"
#define XK_POSIX_COLOR_FURED			"\e[4;31m"
#define XK_POSIX_COLOR_FUGREEN		"\e[4;32m"
#define XK_POSIX_COLOR_FUYELLOW		"\e[4;33m"
#define XK_POSIX_COLOR_FUBLUE			"\e[4;34m"
#define XK_POSIX_COLOR_FUPURPLE		"\e[4;35m"
#define XK_POSIX_COLOR_FUCYAN			"\e[4;36m"
#define XK_POSIX_COLOR_FUWHITE		"\e[4;37m"

#define XK_POSIX_COLOR_FBBLACK		"\e[1;30m"
#define XK_POSIX_COLOR_FBRED			"\e[1;31m"
#define XK_POSIX_COLOR_FBGREEN		"\e[1;32m"
#define XK_POSIX_COLOR_FBYELLOW		"\e[1;33m"
#define XK_POSIX_COLOR_FBBLUE			"\e[1;34m"
#define XK_POSIX_COLOR_FBPURPLE		"\e[1;35m"
#define XK_POSIX_COLOR_FBCYAN			"\e[1;36m"
#define XK_POSIX_COLOR_FBWHITE		"\e[1;37m"

#define XK_POSIX_COLOR_BBLACK			"\e[1;40m"
#define XK_POSIX_COLOR_BRED				"\e[1;41m"
#define XK_POSIX_COLOR_BGREEN			"\e[1;42m"
#define XK_POSIX_COLOR_BYELLOW		"\e[1;43m"
#define XK_POSIX_COLOR_BBLUE			"\e[1;44m"
#define XK_POSIX_COLOR_BPURPLE		"\e[1;45m"
#define XK_POSIX_COLOR_BCYAN			"\e[1;46m"
#define XK_POSIX_COLOR_BWHITE			"\e[1;47m"

/* ########## FUNCTIONS SECTION ########## */
void xkWriteConsole(const XkConsoleHandle handle, const XkString buffer, const XkSize size) {
	int stream = 0;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = 1; break;
		case XK_CONSOLE_STDERR: stream = 2; break;
		default: 								return;
	}

	XkChar fmtBuffer[XK_CONSOLE_BUFFER_SIZE];
	const XkSize fmtSize = xkStringNFormat(fmtBuffer, XK_CONSOLE_BUFFER_SIZE, "%s\n", buffer);

	write(stream, fmtBuffer, fmtSize);
}

void xkWriteConsoleColored(const XkConsoleHandle handle, const XkConsoleColor color, const XkString buffer, const XkSize size) {
	int stream = 0;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = 1; break;
		case XK_CONSOLE_STDERR: stream = 2; break;
		default: 								return;
	}

	const char* pColor = XK_NULL_HANDLE;
	switch(color) {
		case XK_COLOR_FBLACK: 	pColor = XK_POSIX_COLOR_FBLACK; break;
		case XK_COLOR_FRED: 		pColor = XK_POSIX_COLOR_FRED; break;
		case XK_COLOR_FGREEN: 	pColor = XK_POSIX_COLOR_FGREEN; break;
		case XK_COLOR_FYELLOW: 	pColor = XK_POSIX_COLOR_FYELLOW; break;
		case XK_COLOR_FBLUE: 		pColor = XK_POSIX_COLOR_FBLUE; break;
		case XK_COLOR_FPURPLE: 	pColor = XK_POSIX_COLOR_FPURPLE; break;
		case XK_COLOR_FCYAN: 		pColor = XK_POSIX_COLOR_FCYAN; break;
		case XK_COLOR_FWHITE: 	pColor = XK_POSIX_COLOR_FWHITE; break;

		case XK_COLOR_FUBLACK: 	pColor = XK_POSIX_COLOR_FUBLACK; break;
		case XK_COLOR_FURED: 		pColor = XK_POSIX_COLOR_FURED; break;
		case XK_COLOR_FUGREEN: 	pColor = XK_POSIX_COLOR_FUGREEN; break;
		case XK_COLOR_FUYELLOW: pColor = XK_POSIX_COLOR_FUYELLOW; break;
		case XK_COLOR_FUBLUE: 	pColor = XK_POSIX_COLOR_FUBLUE; break;
		case XK_COLOR_FUPURPLE: pColor = XK_POSIX_COLOR_FUPURPLE; break;
		case XK_COLOR_FUCYAN: 	pColor = XK_POSIX_COLOR_FUCYAN; break;
		case XK_COLOR_FUWHITE: 	pColor = XK_POSIX_COLOR_FUWHITE; break;

		case XK_COLOR_FBBLACK: 	pColor = XK_POSIX_COLOR_FBBLACK; break;
		case XK_COLOR_FBRED: 		pColor = XK_POSIX_COLOR_FBRED; break;
		case XK_COLOR_FBGREEN: 	pColor = XK_POSIX_COLOR_FBGREEN; break;
		case XK_COLOR_FBYELLOW: pColor = XK_POSIX_COLOR_FBYELLOW; break;
		case XK_COLOR_FBBLUE: 	pColor = XK_POSIX_COLOR_FBBLUE; break;
		case XK_COLOR_FBPURPLE: pColor = XK_POSIX_COLOR_FBPURPLE; break;
		case XK_COLOR_FBCYAN: 	pColor = XK_POSIX_COLOR_FBCYAN; break;
		case XK_COLOR_FBWHITE: 	pColor = XK_POSIX_COLOR_FBWHITE; break;

		case XK_COLOR_BBLACK: 	pColor = XK_POSIX_COLOR_BBLACK; break;
		case XK_COLOR_BRED: 		pColor = XK_POSIX_COLOR_BRED; break;
		case XK_COLOR_BGREEN: 	pColor = XK_POSIX_COLOR_BGREEN; break;
		case XK_COLOR_BYELLOW: 	pColor = XK_POSIX_COLOR_BYELLOW; break;
		case XK_COLOR_BBLUE: 		pColor = XK_POSIX_COLOR_BBLUE; break;
		case XK_COLOR_BPURPLE: 	pColor = XK_POSIX_COLOR_BPURPLE; break;
		case XK_COLOR_BCYAN: 		pColor = XK_POSIX_COLOR_BCYAN; break;
		case XK_COLOR_BWHITE: 	pColor = XK_POSIX_COLOR_BWHITE; break;

		default: 										pColor = XK_NULL_HANDLE; break;
	}

	XkChar fmtBuffer[XK_CONSOLE_BUFFER_SIZE];
	const XkSize fmtSize = xkStringNFormat(fmtBuffer, XK_CONSOLE_BUFFER_SIZE, "%s%s%s\n", pColor, buffer, XK_POSIX_COLOR_RESET);

	write(stream, fmtBuffer, fmtSize);
}

void xkReadConsole(XkString buffer, const XkSize size) {
	read(0, buffer, size);
}
