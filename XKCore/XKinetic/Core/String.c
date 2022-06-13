/*TODO: remove #include <stdio.h>*/
#include <stdio.h>
#include "XKinetic/Core/Types.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/String.h"

XkSize xkStringLength(XkString string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkString xkCopyString(XkString dstString, XkString srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkString xkNCopyString(XkString dstString, XkString srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkString xkConcatString(XkString dstString, XkString srcString) {
	return(xkCopyString(dstString + xkStringLength(dstString), srcString));
}

XkString xkNConcatString(XkString dstString, XkString srcString, const XkSize length) {
	return(xkNCopyString(dstString + xkStringLength(dstString), srcString, length));
}

XkInt32 xkCompareString(XkString string1, XkString string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareString(XkString string1, XkString string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkString xkTokenString(XkString string, XkString token) {
	while(*string) {
		if(xkDelim(*string, token)) {
			*string = '\0';
			return(string + 1);
		}
		++string;
	}

	return(string);
}

XkString xkNTokenString(XkString string, XkString token, const XkSize length) {
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

XkString xkDuplicateString(XkString string) {
  const XkSize length = xkStringLength(string);
  XkString result = xkAllocateMemory(sizeof(XkChar) * (length + 1));
  xkCopyString(result, string);
  return(result);
}

XkString xkNDublicateString(XkString string, const XkSize length) {
  XkString result = xkAllocateMemory(sizeof(XkChar) * (length + 1));
  xkNCopyString(result, string, length);
  return(result);
}

XkSize xkStringFormat(XkString string, XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkStringFFormat(string, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkStringNFormat(XkString string, const XkSize length, XkString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkStringNFFormat(string, length, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkStringFFormat(XkString string, XkString format, XkArgs args) {
	/*TODO: remove vsprintf*/
	int size = vsprintf(string, format, args);
	return((XkSize)size);
}

XkSize xkStringNFFormat(XkString string, const XkSize length, XkString format, XkArgs args) {
	/*TODO: remove vsnprintf*/
	int size = vsnprintf(string, (unsigned long)length, (const char*)format, args);
	return((XkSize)size);
}
