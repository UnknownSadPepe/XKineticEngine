/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/Log.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
void __xkAssertion(const XkString expression, const XkString file, const XkInt32 line) {
	xkLogFatal("Assertion failure: %s file: %s line: %d", expression, file, line);
}
