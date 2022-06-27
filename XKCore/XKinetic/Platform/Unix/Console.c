#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"

#if defined(XK_UNIX)

#include <unistd.h>

#define XK_UNIX_COLOR_RESET			"\e[0m"

#define XK_UNIX_COLOR_FBLACK		"\e[0;30m"
#define XK_UNIX_COLOR_FRED			"\e[0;31m"
#define XK_UNIX_COLOR_FGREEN		"\e[0;32m"
#define XK_UNIX_COLOR_FYELLOW		"\e[0;33m"
#define XK_UNIX_COLOR_FBLUE			"\e[0;34m"
#define XK_UNIX_COLOR_FPURPLE		"\e[0;35m"
#define XK_UNIX_COLOR_FCYAN			"\e[0;36m"
#define XK_UNIX_COLOR_FWHITE		"\e[0;37m"

#define XK_UNIX_COLOR_FUBLACK		"\e[4;30m"
#define XK_UNIX_COLOR_FURED			"\e[4;31m"
#define XK_UNIX_COLOR_FUGREEN		"\e[4;32m"
#define XK_UNIX_COLOR_FUYELLOW	"\e[4;33m"
#define XK_UNIX_COLOR_FUBLUE		"\e[4;34m"
#define XK_UNIX_COLOR_FUPURPLE	"\e[4;35m"
#define XK_UNIX_COLOR_FUCYAN		"\e[4;36m"
#define XK_UNIX_COLOR_FUWHITE		"\e[4;37m"

#define XK_UNIX_COLOR_FBBLACK		"\e[1;30m"
#define XK_UNIX_COLOR_FBRED			"\e[1;31m"
#define XK_UNIX_COLOR_FBGREEN		"\e[1;32m"
#define XK_UNIX_COLOR_FBYELLOW	"\e[1;33m"
#define XK_UNIX_COLOR_FBBLUE		"\e[1;34m"
#define XK_UNIX_COLOR_FBPURPLE	"\e[1;35m"
#define XK_UNIX_COLOR_FBCYAN		"\e[1;36m"
#define XK_UNIX_COLOR_FBWHITE		"\e[1;37m"

#define XK_UNIX_COLOR_BBLACK		"\e[1;40m"
#define XK_UNIX_COLOR_BRED			"\e[1;41m"
#define XK_UNIX_COLOR_BGREEN		"\e[1;42m"
#define XK_UNIX_COLOR_BYELLOW		"\e[1;43m"
#define XK_UNIX_COLOR_BBLUE			"\e[1;44m"
#define XK_UNIX_COLOR_BPURPLE		"\e[1;45m"
#define XK_UNIX_COLOR_BCYAN			"\e[1;46m"
#define XK_UNIX_COLOR_BWHITE		"\e[1;47m"

void xkWriteConsole(const XkConsoleHandle handle, const XkString buffer, const XkSize size) {
	// Select stream.
	int stream = 0;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = 1; break;
		case XK_CONSOLE_STDERR: stream = 2; break;
		default: stream = -1; return;
	}

	// Write console buffer.
	write(stream, buffer, size);
}

void xkWriteConsoleColored(const XkConsoleHandle handle, const XkConsoleColor color, const XkString buffer, const XkSize size) {
	// Select stream.
	int stream = 0;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = 1; break;
		case XK_CONSOLE_STDERR: stream = 2; break;
		default: stream = -1; return;
	}

	// Select color.
	const char* pColor = XK_NULL_HANDLE;
	size_t colorSize = 8;
	switch(color) {
		case XK_COLOR_FBLACK_BIT: 	pColor = XK_UNIX_COLOR_FBLACK; break;
		case XK_COLOR_FRED_BIT: 		pColor = XK_UNIX_COLOR_FRED; break;
		case XK_COLOR_FGREEN_BIT: 	pColor = XK_UNIX_COLOR_FGREEN; break;
		case XK_COLOR_FYELLOW_BIT: 	pColor = XK_UNIX_COLOR_FYELLOW; break;
		case XK_COLOR_FBLUE_BIT: 		pColor = XK_UNIX_COLOR_FBLUE; break;
		case XK_COLOR_FPURPLE_BIT: 	pColor = XK_UNIX_COLOR_FPURPLE; break;
		case XK_COLOR_FCYAN_BIT: 		pColor = XK_UNIX_COLOR_FCYAN; break;
		case XK_COLOR_FWHITE_BIT: 	pColor = XK_UNIX_COLOR_FWHITE; break;

		case XK_COLOR_FUBLACK_BIT: 	pColor = XK_UNIX_COLOR_FUBLACK; break;
		case XK_COLOR_FURED_BIT: 		pColor = XK_UNIX_COLOR_FURED; break;
		case XK_COLOR_FUGREEN_BIT: 	pColor = XK_UNIX_COLOR_FUGREEN; break;
		case XK_COLOR_FUYELLOW_BIT: pColor = XK_UNIX_COLOR_FUYELLOW; break;
		case XK_COLOR_FUBLUE_BIT: 	pColor = XK_UNIX_COLOR_FUBLUE; break;
		case XK_COLOR_FUPURPLE_BIT: pColor = XK_UNIX_COLOR_FUPURPLE; break;
		case XK_COLOR_FUCYAN_BIT: 	pColor = XK_UNIX_COLOR_FUCYAN; break;
		case XK_COLOR_FUWHITE_BIT: 	pColor = XK_UNIX_COLOR_FUWHITE; break;

		case XK_COLOR_FBBLACK_BIT: 	pColor = XK_UNIX_COLOR_FBBLACK; break;
		case XK_COLOR_FBRED_BIT: 		pColor = XK_UNIX_COLOR_FBRED; break;
		case XK_COLOR_FBGREEN_BIT: 	pColor = XK_UNIX_COLOR_FBGREEN; break;
		case XK_COLOR_FBYELLOW_BIT: pColor = XK_UNIX_COLOR_FBYELLOW; break;
		case XK_COLOR_FBBLUE_BIT: 	pColor = XK_UNIX_COLOR_FBBLUE; break;
		case XK_COLOR_FBPURPLE_BIT: pColor = XK_UNIX_COLOR_FBPURPLE; break;
		case XK_COLOR_FBCYAN_BIT: 	pColor = XK_UNIX_COLOR_FBCYAN; break;
		case XK_COLOR_FBWHITE_BIT: 	pColor = XK_UNIX_COLOR_FBWHITE; break;

		case XK_COLOR_BBLACK_BIT: 	pColor = XK_UNIX_COLOR_BBLACK; break;
		case XK_COLOR_BRED_BIT: 		pColor = XK_UNIX_COLOR_BRED; break;
		case XK_COLOR_BGREEN_BIT: 	pColor = XK_UNIX_COLOR_BGREEN; break;
		case XK_COLOR_BYELLOW_BIT: 	pColor = XK_UNIX_COLOR_BYELLOW; break;
		case XK_COLOR_BBLUE_BIT: 		pColor = XK_UNIX_COLOR_BBLUE; break;
		case XK_COLOR_BPURPLE_BIT: 	pColor = XK_UNIX_COLOR_BPURPLE; break;
		case XK_COLOR_BCYAN_BIT: 		pColor = XK_UNIX_COLOR_BCYAN; break;
		case XK_COLOR_BWHITE_BIT: 	pColor = XK_UNIX_COLOR_BWHITE; break;

		default: {
			pColor = XK_NULL_HANDLE;
			colorSize = 0;
			break;
		}
	}
	// Write console color.
	write(stream, pColor, colorSize);

	// Write console buffer.
	write(stream, buffer, size);

	// Reset console color.
	write(stream, XK_UNIX_COLOR_RESET, 5);
}

void xkReadConsole(XkString buffer, const XkSize size) {
	// Read console buffer.
	read(0, buffer, size);
}

#endif // XK_UNIX
