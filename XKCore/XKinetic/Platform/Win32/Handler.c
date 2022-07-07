/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/String.h"

#include <windows.h>

/* ########## MACROS SECTION ########## */
#define XK_HANDLER_BUFFER_SIZE 1024

/* ########## FUNCTIONS SECTION ########## */
void __xkErrorHandler(const XkString format, ...) {
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];

	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(buffer, XK_HANDLER_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	MessageBox(NULL, buffer, "XKinetic Error Handler", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void __xkWarningHandler(const XkString format, ...) {
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];

	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(buffer, XK_HANDLER_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	MessageBox(NULL, buffer, "XKinetic Warning Handler", MB_OK | MB_ICONWARNING | MB_TOPMOST);
}

#if defined(XKCORE_DEBUG)
void __xkDebugHandler(const XkString format, ...) {
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];

	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(buffer, XK_HANDLER_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	MessageBox(NULL, buffer, "XKinetic Debug Handler", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
}
#endif // XKCORE_DEBUG
