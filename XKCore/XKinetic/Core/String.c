/*TODO: remove #include <stdio.h>*/
#include <stdio.h>
#include "XKinetic/Core/Types.h"
#include "XKinetic/Core/String.h"

XkSize xkStringLength(const XkChar8* string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkChar8* xkCopyString(XkChar8* dstString, const XkChar8* srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkChar8* xkNCopyString(XkChar8* dstString, const XkChar8* srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkChar8* xkConcatString(XkChar8* dstString, const XkChar8* srcString) {
	return(xkCopyString(dstString + xkStringLength(dstString), srcString));
}

XkChar8* xkNConcatString(XkChar8* dstString, const XkChar8* srcString, const XkSize length) {
	return(xkNCopyString(dstString + xkStringLength(dstString), srcString, length));
}

XkInt32 xkCompareString(const XkChar8* string1, const XkChar8* string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareString(const XkChar8* string1, const XkChar8* string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkChar8* xkTokenString(XkChar8* string, const XkChar8* token) {
	while(*string) {
		if(xkDelim(*string, token)) {
			*string = '\0';
			return(string + 1);
		}
		++string;
	}

	return(string);
}

XkChar8* xkNTokenString(XkChar8* string, const XkChar8* token, const XkSize length) {
	XkSize len = length;
	while(*string && --len) {
		if(xkDelim(*string, token)) {
			*string = '\0';
			return(string + 1);
		}
		++string;
	}

	return(string);
}

XkSize xkStringFormat(XkChar8* string, const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkStringFFormat(string, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkStringNFormat(XkChar8* string, const XkSize length, const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkStringNFFormat(string, length, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkStringFFormat(XkChar8* string, const XkChar8* format, XkArgs args) {
	/*TODO: remove vsprintf*/
	int size = vsprintf(string, format, args);
	return((XkSize)size);
}

XkSize xkStringNFFormat(XkChar8* string, const XkSize length, const XkChar8* format, XkArgs args) {
	/*TODO: remove vsnprintf*/
	int size = vsnprintf(string, (unsigned long)length, (const char*)format, args);
	return((XkSize)size);
}
