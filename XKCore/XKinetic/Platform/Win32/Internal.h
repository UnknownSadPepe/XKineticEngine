#pragma once

#include <windows.h>

typedef struct {
	HINSTANCE instance;
	HANDLE stdout;
	WORD stdoutAttribute;
	HANDLE stderr;
	WORD stderrAttribute;
	HANDLE stdin;
	HANDLE heap;
} __XkWin32Platform;

#define XK_PLATFORM __XkWin32Platform handle

