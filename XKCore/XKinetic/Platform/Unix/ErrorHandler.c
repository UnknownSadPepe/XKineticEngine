/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"

/* ########## MACROS SECTION ########## */
#define XK_ERROR_HANDLER_ARG_BUFFER_SIZE 1024
#define XK_ERROR_HANDLER_BUFFER_SIZE XK_ERROR_HANDLER_ARG_BUFFER_SIZE

/* ########## FUNCTIONS SECTION ########## */
void __xkErrorHandler(const XkString format, ...) {
	XkChar handleBuffer[XK_ERROR_HANDLER_BUFFER_SIZE] = {};

	// Format argument buffer.
	XkChar argBuffer[XK_ERROR_HANDLER_ARG_BUFFER_SIZE] = {};
	xkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(argBuffer, XK_ERROR_HANDLER_ARG_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	const XkSize size = xkStringNFormat(handleBuffer, XK_ERROR_HANDLER_BUFFER_SIZE, "%s\n", argBuffer);

	xkWriteConsoleColored(XK_CONSOLE_STDERR, XK_COLOR_BRED_BIT, handleBuffer, size);
}
