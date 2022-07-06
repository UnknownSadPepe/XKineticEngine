/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Core/String.h"

/* ########## MACROS SECTION ########## */
#define XK_HANDLER_ARG_BUFFER_SIZE 1024
#define XK_HANDLER_BUFFER_SIZE (XK_HANDLER_ARG_BUFFER_SIZE) + 1

/* ########## FUNCTIONS SECTION ########## */
void __xkErrorHandler(const XkString format, ...) {
	// Format argument buffer.
	XkChar argBuffer[XK_HANDLER_ARG_BUFFER_SIZE];
	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(argBuffer, XK_HANDLER_ARG_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	// Format buffer.
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];
	const XkSize size = xkStringNFormat(buffer, XK_HANDLER_BUFFER_SIZE, "{Error handler} %s\n", argBuffer);

	xkWriteConsoleColored(XK_CONSOLE_STDERR, XK_COLOR_BRED, buffer, size);
}

void __xkWarningHandler(const XkString format, ...) {
	// Format argument buffer.
	XkChar argBuffer[XK_HANDLER_ARG_BUFFER_SIZE];
	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(argBuffer, XK_HANDLER_ARG_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	// Format buffer.
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];
	const XkSize size = xkStringNFormat(buffer, XK_HANDLER_BUFFER_SIZE, "{Warning handler} %s\n", argBuffer);

	xkWriteConsoleColored(XK_CONSOLE_STDERR, XK_COLOR_FYELLOW, buffer, size);
}

//#if defined(XKCORE_DEBUG)
void __xkDebugHandler(const XkString format, ...) {
	// Format argument buffer.
	XkChar argBuffer[XK_HANDLER_ARG_BUFFER_SIZE];
	XkArgs args;
	xkStartArgs(args, format);
	xkStringNFFormat(argBuffer, XK_HANDLER_ARG_BUFFER_SIZE, format, args);
	xkEndArgs(args);

	// Format buffer.
	XkChar buffer[XK_HANDLER_BUFFER_SIZE];
	const XkSize size = xkStringNFormat(buffer, XK_HANDLER_BUFFER_SIZE, "{Debug handler} %s\n", argBuffer);

	xkWriteConsoleColored(XK_CONSOLE_STDERR, XK_COLOR_FBLUE, buffer, size);
}
//#endif // XKCORE_DEBUG
