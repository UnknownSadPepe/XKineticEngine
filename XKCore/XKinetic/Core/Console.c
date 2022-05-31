#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/String.h"
#include "XKinetic/Core/Console.h"

#define XK_CONSOLE_BUFFER_SIZE 1024

XkResult xkConsoleInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = __xkConsoleInitialize();
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkConsoleTerminate(void) {
	__xkConsoleTerminate();	
}

void xkColorConsole(const XkConsoleHandle stream, const XkConsoleColor color) {
	__xkColorConsole(stream, color);
}

void xkFWriteConsole(const XkConsoleHandle stream, const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	xkVWriteConsole(stream, format, args);
	xkEndArgs(args);
}

void xkFReadConsole(XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	xkVReadConsole(format, args);
	xkEndArgs(args);
}

void xkVWriteConsole(const XkConsoleHandle stream, const XkChar8* format, XkArgs args) {
	XkChar8 buffer[XK_CONSOLE_BUFFER_SIZE] = {0};
	const XkSize size = xkStringNFFormat(buffer, XK_CONSOLE_BUFFER_SIZE, format, args);
	xkWriteConsole(stream, buffer, size);
}

void xkVReadConsole(XkChar8* format, XkArgs args) {
	XkChar8 buffer[XK_CONSOLE_BUFFER_SIZE] = {0};
	// TODO: implementation.
	const XkSize size = 0;
	xkReadConsole(buffer, size);
}

void xkWriteConsole(const XkConsoleHandle stream, const XkChar8* buffer, const XkSize size) {
	__xkWriteConsole(stream, buffer, size);
}

void xkReadConsole(XkChar8* buffer, const XkSize size) {
	__xkReadConsole(buffer, size);
}
