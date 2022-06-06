#include "XKinetic/Core/String.h"
#include "XKinetic/Core/Time.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Core/Log.h"

typedef enum {
	XK_LOG_TYPE_FATAL = 0,
	XK_LOG_TYPE_ERROR = 1,
	XK_LOG_TYPE_WARNING = 2,
	XK_LOG_TYPE_TRACE = 3,
	XK_LOG_TYPE_INFO = 4,
	XK_LOG_TYPE_NOTICE = 5,
	XK_LOG_TYPE_DEBUG = 6
}	XkLogType;

static void __xkLog(const XkLogType, const XkChar8*, XkArgs);

static struct {
	XkFile file;
} _xkLogger;

#define XK_LOG_BUFFER_SIZE 1024

XkResult xkLogInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = xkOpenFile(_xkLogger.file, "XKineticLogFile.log", XK_FILE_FLAG_WO_BIT | XK_FILE_FLAG_CR_BIT);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkLogTerminate(void) {
	xkCloseFile(_xkLogger.file);
}

void xkLogFatal(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_FATAL, format, args);
	xkEndArgs(args);
}

void xkLogError(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_ERROR, format, args);
	xkEndArgs(args);
}

void xkLogWarning(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_WARNING, format, args);
	xkEndArgs(args);
}

void xkLogTrace(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_TRACE, format, args);
	xkEndArgs(args);
}

void xkLogInfo(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_INFO, format, args);
	xkEndArgs(args);
}

void xkLogNotice(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_NOTICE, format, args);
	xkEndArgs(args);
}

void xkLogDebug(const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_DEBUG, format, args);
	xkEndArgs(args);
}

void __xkLog(const XkLogType type, const XkChar8* format, XkArgs args) {
	static const XkChar8* typeString[] = {"FATAL", "ERROR", "WARNING", "TRACE", "INFO", "NOTICE", "DEBUG"};
	XkChar8 buffer[XK_LOG_BUFFER_SIZE] = {0};

	XkConsoleHandle stream = type <= XK_LOG_TYPE_ERROR ? XK_CONSOLE_STDERR : XK_CONSOLE_STDOUT;
	XkConsoleColor color;
	switch(type) {
		case XK_LOG_TYPE_FATAL:		color = XK_COLOR_BRED_BIT; break;
		case XK_LOG_TYPE_ERROR:		color = XK_COLOR_FRED_BIT; break;
		case XK_LOG_TYPE_WARNING: color = XK_COLOR_FYELLOW_BIT; break;
		case XK_LOG_TYPE_TRACE:		color = XK_COLOR_BGREEN_BIT; break;
		case XK_LOG_TYPE_INFO:		color = XK_COLOR_FWHITE_BIT; break;
		case XK_LOG_TYPE_NOTICE:	color = XK_COLOR_FCYAN_BIT; break;
		case XK_LOG_TYPE_DEBUG:		color = XK_COLOR_FBLUE_BIT; break;
	}

	XkChar8 timeBuffer[64];
	XkSize rawTime = xkGetTime();
	XkTime tm;
	xkTimeFormat(&tm, rawTime);
	xkTimeStringFormat(&tm, timeBuffer, "%x-%X");

	xkStringNFFormat(buffer, XK_LOG_BUFFER_SIZE, format, args);
	const XkSize size = xkStringNFormat(buffer, XK_LOG_BUFFER_SIZE, "[%s]{%s} %s", timeBuffer, typeString[type], buffer);

	xkColorConsole(stream, color);
	xkWriteConsole(stream, buffer, size);
	xkColorConsole(stream, XK_COLOR_RESET);
	//xkWriteConsole(stream, "\n", );

	xkWriteFile(_xkLogger.file, buffer, size);
}
