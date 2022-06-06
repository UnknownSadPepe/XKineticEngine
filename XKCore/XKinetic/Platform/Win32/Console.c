#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

void xkColorConsole(const XkConsoleHandle handle, const XkConsoleColor color) {
	/// TODO: implementation.


	HANDLE stream;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = GetStdHandle(STD_OUTPUT_HANDLE); break;
		case XK_CONSOLE_STDERR: stream = GetStdHandle(STD_ERROR_HANDLE); break;
	}	


	SetConsoleTextAttribute(stream, attribute);
}

void xkWriteConsole(const XkConsoleHandle handle, const XkChar8* buffer, const XkSize size) {
	HANDLE stream;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = GetStdHandle(STD_OUTPUT_HANDLE); break;
		case XK_CONSOLE_STDERR: stream = GetStdHandle(STD_ERROR_HANDLE); break;
	}	
	LPDWORD numberWritten = 0;
	WriteConsoleA(stream, buffer, (DWORD)size, numberWritten, 0);
}

void xkWriteConsoleColored(const XkConsoleHandle handle, const XkConsoleColor color, const XkChar8* buffer, const XkSize size) {
	CONSOLE_SCREEN_BUFFER_INFO CBI;
	GetConsoleScreenBufferInfo(_xkPlatform.handle.stdout, &CBI);

	HANDLE stream;
	switch(handle) {
		case XK_CONSOLE_STDOUT: stream = GetStdHandle(STD_OUTPUT_HANDLE); break;
		case XK_CONSOLE_STDERR: stream = GetStdHandle(STD_ERROR_HANDLE); break;
	}	

	WORD attribute;
	switch(color) { 
		case XK_COLOR_FBLACK_BIT: attribute		= 0; break;
		case XK_COLOR_FRED_BIT: attribute			= FOREGROUND_RED; break;
		case XK_COLOR_FGREEN_BIT: attribute		= FOREGROUND_GREEN; break;
		case XK_COLOR_FYELLOW_BIT: attribute	= FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FBLUE_BIT: attribute		= FOREGROUND_BLUE; break;
		case XK_COLOR_FPURPLE_BIT: attribute	= FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FCYAN_BIT: attribute		= FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FWHITE_BIT: attribute		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ; break;

		case XK_COLOR_FUBLACK_BIT: attribute	= COMMON_LVB_UNDERSCORE; break;
		case XK_COLOR_FURED_BIT: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_RED; break;
		case XK_COLOR_FUGREEN_BIT: attribute	= COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN; break;
		case XK_COLOR_FUYELLOW_BIT: attribute = COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FUBLUE_BIT: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_BLUE; break;
		case XK_COLOR_FUPURPLE_BIT: attribute = COMMON_LVB_UNDERSCORE | FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FUCYAN_BIT: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FUWHITE_BIT: attribute	= COMMON_LVB_UNDERSCORE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;

		case XK_COLOR_FBBLACK_BIT: attribute	= FOREGROUND_INTENSITY; break;
		case XK_COLOR_FBRED_BIT: attribute		= FOREGROUND_INTENSITY | FOREGROUND_RED; break;
		case XK_COLOR_FBGREEN_BIT: attribute	= FOREGROUND_INTENSITY | FOREGROUND_GREEN; break;
		case XK_COLOR_FBYELLOW_BIT: attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FBBLUE_BIT: attribute		= FOREGROUND_INTENSITY | FOREGROUND_BLUE; break;
		case XK_COLOR_FBPURPLE_BIT: attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FBCYAN_BIT: attribute		= FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FBWHITE_BIT: attribute	= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;

		case XK_COLOR_BBLACK_BIT: attribute		= 0; break;
		case XK_COLOR_BRED_BIT: attribute			= BACKGROUND_RED; break;
		case XK_COLOR_BGREEN_BIT: attribute		=	BACKGROUND_GREEN; break;
		case XK_COLOR_BYELLOW_BIT: attribute	=	BACKGROUND_GREEN | BACKGROUND_RED; break;
		case XK_COLOR_BBLUE_BIT: attribute		= BACKGROUND_BLUE; break;
		case XK_COLOR_BPURPLE_BIT: attribute	=	BACKGROUND_RED | BACKGROUND_BLUE; break;
		case XK_COLOR_BCYAN_BIT: attribute		= BACKGROUND_GREEN | BACKGROUND_BLUE; break;
		case XK_COLOR_BWHITE_BIT: attribute		=	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	}

	SetConsoleTextAttribute(stream, attribute);
	LPDWORD numberWritten = 0;
	WriteConsoleA(stream, buffer, (DWORD)size, numberWritten, 0);
	SetConsoleTextAttribute(stream, CBI.wAttributes);
}

void xkReadConsole(XkChar8* buffer, const XkSize size) {
	HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);

	DWORD numberReaden;
	ReadConsoleA(stdin, buffer, (DWORD)size, &numberReaden, NULL);
}

#endif // XK_WIN32
