#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

#define XK_ERROR_HANDLER_BUFFER_SIZE 1024

void __xkErrorHandler(const XkChar8* format, ...) {
	XkChar8 buffer[XK_ERROR_HANDLER_BUFFER_SIZE] = {0};

	va_list args;
	va_start(args, format);
	vsnprintf(buffer, XK_ERROR_HANDLER_BUFFER_SIZE, format, args);
	fprintf(stderr, "Platform Error Handler: %s\n", buffer);
	MessageBox(NULL, buffer, "Platform Error Handler", MB_ABORTRETRYIGNORE);
	va_end(args);
}

#endif // XK_WIN32
