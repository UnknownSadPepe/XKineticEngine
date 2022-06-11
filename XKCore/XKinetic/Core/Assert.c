#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/Log.h"

void __xkAssertion(const XkString expr, const XkString file, const XkInt32 line) {
	xkLogFatal("Assertion failure: %s file: %s line: %d", expr, file, line);
}
