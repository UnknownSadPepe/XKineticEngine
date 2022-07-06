/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Core/String.h"

/* ########## MACROS SECTION ########## */
#define XK_ERROR_HANDLER_ARG_BUFFER_SIZE 1024

/* ########## FUNCTIONS SECTION ########## */
void __xkErrorHandler(const XkString format, ...) {
	// Format buffer.
	XkChar buffer[XK_ERROR_HANDLER_ARG_BUFFER_SIZE] = {};
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkStringNFFormat(buffer, XK_ERROR_HANDLER_ARG_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	xkWriteConsoleColored(XK_CONSOLE_STDERR, XK_COLOR_BRED, buffer, size);
}
