/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/String.h"

#include <windows.h>

/* ########## MACROS SECTION ########## */
#define XK_ERROR_HANDLER_BUFFER_SIZE 1024

/* ########## FUNCTIONS SECTION ########## */
void __xkErrorHandler(const XkString format, ...) {
	XkChar buffer[XK_ERROR_HANDLER_BUFFER_SIZE] = {};

	xkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(buffer, XK_ERROR_HANDLER_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	MessageBox(NULL, buffer, "XKinetic Error Handler", MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_TOPMOST);
}
