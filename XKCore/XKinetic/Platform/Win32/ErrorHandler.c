#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

#define XK_ERROR_HANDLER_BUFFER_SIZE 1024

void __xkErrorHandler(const XkString format, ...) {
	XkChar buffer[XK_ERROR_HANDLER_BUFFER_SIZE] = {0};

	// Format string.
	va_list args;
	va_start(args, format);
	// Print to console.
	vsnprintf(buffer, XK_ERROR_HANDLER_BUFFER_SIZE, format, args);
	// Win32 message box.
	MessageBox(NULL, buffer, "XKinetic Error Handler", MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_TOPMOST);
	va_end(args);
}

#endif // XK_WIN32
