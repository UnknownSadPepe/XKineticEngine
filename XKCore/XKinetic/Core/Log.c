/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/String.h"
#include "XKinetic/Platform/Time.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Core/Log.h"

/* ########## MACROS SECTION ########## */
#define XK_LOG_TIME_BUFFER_SIZE 64
#define XK_LOG_TYPE_BUFFER_SIZE 3
#define XK_LOG_ARG_BUFFER_SIZE 1024
#define XK_LOG_BUFFER_SIZE (XK_LOG_TIME_BUFFER_SIZE + XK_LOG_TYPE_BUFFER_SIZE + XK_LOG_ARG_BUFFER_SIZE)

/* ########## TYPES SECTION ########## */
typedef enum XkLogType_T {
	XK_LOG_TYPE_FATAL 		= 0,
	XK_LOG_TYPE_ERROR 		= 1,
	XK_LOG_TYPE_WARNING 	= 2,
	XK_LOG_TYPE_TRACE 		= 3,
	XK_LOG_TYPE_INFO 			= 4,
	XK_LOG_TYPE_NOTICE 		= 5,
	XK_LOG_TYPE_DEBUG 		= 6
}	XkLogType;

typedef struct __XkLogger_T {
	XkBool8 initialized;

	XkFile file;
} __XkLogger;

/* ########## GLOBAL VARIABLES SECTION ########## */
static __XkLogger _xkLogger;

/* ########## FUNCTION DECLARATIONS SECTION ########## */
static void __xkLog(const XkLogType, const XkString, XkArgs);

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeLog() {
	XkResult result = XK_SUCCESS;

	if(_xkLogger.initialized) {
		goto _catch;
	}

	result = xkOpenFile(&_xkLogger.file, "XKineticLogs.log", XK_FILE_FLAG_WO_BIT | XK_FILE_FLAG_CR_BIT);
	if(result != XK_SUCCESS) goto _catch;

	_xkLogger.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateLog() {
	if(!_xkLogger.initialized) {
		return;
	}

	xkCloseFile(_xkLogger.file);

	_xkLogger.initialized = XK_FALSE;
}

void xkLogFatal(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_FATAL, format, args);
	xkEndArgs(args);
}

void xkLogError(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_ERROR, format, args);
	xkEndArgs(args);
}

void xkLogWarning(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_WARNING, format, args);
	xkEndArgs(args);
}

void xkLogTrace(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_TRACE, format, args);
	xkEndArgs(args);
}

void xkLogInfo(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_INFO, format, args);
	xkEndArgs(args);
}

void xkLogNotice(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_NOTICE, format, args);
	xkEndArgs(args);
}

#if defined(XK_DEBUG)
void xkLogDebug(const XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	__xkLog(XK_LOG_TYPE_DEBUG, format, args);
	xkEndArgs(args);
}
#endif // XK_DEBUG

void __xkLog(const XkLogType type, const XkString format, XkArgs args) {
	if(!_xkLogger.initialized) {
		return;
	}

	static const XkString typeBuffer[] = {"FTL", "ERR", "WRG", "TRC", "INF", "NTC", "DBG"};
	XkChar logBuffer[XK_LOG_BUFFER_SIZE] = {};

	XkConsoleHandle stream = type <= XK_LOG_TYPE_ERROR ? XK_CONSOLE_STDERR : XK_CONSOLE_STDOUT;

	XkConsoleColor color = 0;
	switch(type) {
		case XK_LOG_TYPE_FATAL:		color = XK_COLOR_BRED; 		break;
		case XK_LOG_TYPE_ERROR:		color = XK_COLOR_FRED; 		break;
		case XK_LOG_TYPE_WARNING: color = XK_COLOR_FYELLOW; break;
		case XK_LOG_TYPE_TRACE:		color = XK_COLOR_BGREEN; 	break;
		case XK_LOG_TYPE_INFO:		color = XK_COLOR_FWHITE; 	break;
		case XK_LOG_TYPE_NOTICE:	color = XK_COLOR_FCYAN; 	break;
		case XK_LOG_TYPE_DEBUG:		color = XK_COLOR_FBLUE; 	break;
		default:									color = 0; 								break;
	}

	// Format time buffer.
	XkChar timeBuffer[XK_LOG_TIME_BUFFER_SIZE];
	XkSize rawTime = xkGetTime();
	XkTime tm;
	xkTimeFormat(&tm, rawTime);
	xkTimeStringFormat(&tm, timeBuffer, XK_LOG_TIME_BUFFER_SIZE, "%x-%X");

	// Format argument buffer.
	XkChar argBuffer[XK_LOG_ARG_BUFFER_SIZE];
	xkStringNFFormat(argBuffer, XK_LOG_ARG_BUFFER_SIZE, format, args);

	// Format log buffer.
	const XkSize size = xkStringNFormat(logBuffer, XK_LOG_BUFFER_SIZE, "[%s]{%s} %s\n", timeBuffer, typeBuffer[type], argBuffer);

	xkWriteConsoleColored(stream, color, logBuffer, size);

	xkWriteFile(_xkLogger.file, logBuffer, size);
}
