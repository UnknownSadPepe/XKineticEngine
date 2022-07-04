/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"

/* ########## MACROS SECTION ########## */
#ifndef COMMON_LVB_UNDERSCORE
	#define COMMON_LVB_UNDERSCORE 0x8000
#endif // COMMON_LVB_UNDERSCORE

/* ########## FUNCTIONS SECTION ########## */
void xkWriteConsole(const XkConsoleHandle handle, const XkString buffer, const XkSize size) {
	HANDLE stream = INVALID_HANDLE_VALUE;
	switch(handle) {
		case XK_CONSOLE_STDOUT: {
			stream = GetStdHandle(STD_OUTPUT_HANDLE);
			if(stream == INVALID_HANDLE_VALUE) return;
		}

		case XK_CONSOLE_STDERR: {
			stream =  GetStdHandle(STD_ERROR_HANDLE);
			if(stream == INVALID_HANDLE_VALUE) return;
		}

		default: return;
	}

	LPDWORD numberWritten = 0;
	WriteConsoleA(stream, buffer, (DWORD)size, numberWritten, 0);
}

void xkWriteConsoleColored(const XkConsoleHandle handle, const XkConsoleColor color, const XkString buffer, const XkSize size) {
	CONSOLE_SCREEN_BUFFER_INFO CBI = {};

	HANDLE stream = INVALID_HANDLE_VALUE;
	switch(handle) {
		case XK_CONSOLE_STDOUT: {
			stream = GetStdHandle(STD_OUTPUT_HANDLE);
			if(stream == INVALID_HANDLE_VALUE) return;
			GetConsoleScreenBufferInfo(stream, &CBI); break;
		}

		case XK_CONSOLE_STDERR: {
			stream =  GetStdHandle(STD_ERROR_HANDLE);
			if(stream == INVALID_HANDLE_VALUE) return;
			GetConsoleScreenBufferInfo(stream, &CBI); break;
		}

		default: return;
	}	

	WORD attribute = 0;
	switch(color) { 
		case XK_COLOR_FBLACK: attribute		= 0; break;
		case XK_COLOR_FRED: attribute			= FOREGROUND_RED; break;
		case XK_COLOR_FGREEN: attribute		= FOREGROUND_GREEN; break;
		case XK_COLOR_FYELLOW: attribute	= FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FBLUE: attribute		= FOREGROUND_BLUE; break;
		case XK_COLOR_FPURPLE: attribute	= FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FCYAN: attribute		= FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FWHITE: attribute		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ; break;

		case XK_COLOR_FUBLACK: attribute	= COMMON_LVB_UNDERSCORE; break;
		case XK_COLOR_FURED: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_RED; break;
		case XK_COLOR_FUGREEN: attribute	= COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN; break;
		case XK_COLOR_FUYELLOW: attribute = COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FUBLUE: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_BLUE; break;
		case XK_COLOR_FUPURPLE: attribute = COMMON_LVB_UNDERSCORE | FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FUCYAN: attribute		= COMMON_LVB_UNDERSCORE | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FUWHITE: attribute	= COMMON_LVB_UNDERSCORE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;

		case XK_COLOR_FBBLACK: attribute	= FOREGROUND_INTENSITY; break;
		case XK_COLOR_FBRED: attribute		= FOREGROUND_INTENSITY | FOREGROUND_RED; break;
		case XK_COLOR_FBGREEN: attribute	= FOREGROUND_INTENSITY | FOREGROUND_GREEN; break;
		case XK_COLOR_FBYELLOW: attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case XK_COLOR_FBBLUE: attribute		= FOREGROUND_INTENSITY | FOREGROUND_BLUE; break;
		case XK_COLOR_FBPURPLE: attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE; break;
		case XK_COLOR_FBCYAN: attribute		= FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
		case XK_COLOR_FBWHITE: attribute	= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;

		case XK_COLOR_BBLACK: attribute		= 0; break;
		case XK_COLOR_BRED: attribute			= BACKGROUND_RED; break;
		case XK_COLOR_BGREEN: attribute		=	BACKGROUND_GREEN; break;
		case XK_COLOR_BYELLOW: attribute	=	BACKGROUND_GREEN | BACKGROUND_RED; break;
		case XK_COLOR_BBLUE: attribute		= BACKGROUND_BLUE; break;
		case XK_COLOR_BPURPLE: attribute	=	BACKGROUND_RED | BACKGROUND_BLUE; break;
		case XK_COLOR_BCYAN: attribute		= BACKGROUND_GREEN | BACKGROUND_BLUE; break;
		case XK_COLOR_BWHITE: attribute		=	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;

		default: {
			attribute = CBI.wAttributes;
			break;
		}
	}

	SetConsoleTextAttribute(stream, attribute);

	LPDWORD numberWritten = 0;
	WriteConsoleA(stream, buffer, (DWORD)size, numberWritten, 0);

	SetConsoleTextAttribute(stream, CBI.wAttributes);
}

void xkReadConsole(XkString buffer, const XkSize size) {
	HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
	if(stdin == INVALID_HANDLE_VALUE) return;

	DWORD numberReaden;
	ReadConsoleA(stdin, buffer, (DWORD)size, &numberReaden, NULL);
}
