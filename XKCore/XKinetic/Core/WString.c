/// TODO: remove #include <wchar.h>
#include <wchar.h>
/// TODO: remove #include <stdio.h>
#include <stdio.h>
#include "XKinetic/Core/Types.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/WString.h"

XkSize xkWStringLength(XkWString string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkWString xkCopyWString(XkWString dstString, XkWString srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = L'\0';
	return(dstString);
}

XkWString xkNCopyWString(XkWString dstString, XkWString srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = L'\0';
	return(dstString);
}

XkWString xkConcatWString(XkWString dstString, XkWString srcString) {
	return(xkCopyWString(dstString + xkWStringLength(dstString), srcString));
}

XkWString xkNConcatWString(XkWString dstString, XkWString srcString, const XkSize length) {
	return(xkNCopyWString(dstString + xkWStringLength(dstString), srcString, length));
}

XkInt32 xkCompareWString(XkWString string1, XkWString string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareWString(XkWString string1, XkWString string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}
	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkWString xkTokenWString(XkWString string, XkWString token) {
	while(*string) {
		if(xkWDelim(*string, token)) {
			*string = L'\0';
			return(string + 1);
		}
		++string;
	}

	return(string);
}

XkWString xkNTokenWString(XkWString string, XkWString token, const XkSize length) {
	XkSize len = length;
	while(*string && --len) {
		if(xkWDelim(*string, token)) {
			*string = L'\0';
			return(string + 1);
		}
		++string;
	}

	return(string);
}

XkWString xkDuplicateWString(XkWString string) {
  const XkSize length = xkWStringLength(string);
  XkWString result = xkAllocateMemory(sizeof(XkWChar) * (length + 1));
  xkCopyWString(result, string);
  return(result);
}

XkWString xkNDublicateWString(XkWString string, const XkSize length) {
  XkWString result = xkAllocateMemory(sizeof(XkWChar) * (length + 1));
  xkNCopyWString(result, string, length);
  return(result);
}

XkSize xkWStringFormat(XkWString string, XkWString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkWStringFFormat(string, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkWStringNFormat(XkWString string, const XkSize length, XkWString format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	const XkSize size = xkWStringNFFormat(string, length, format, args);
	xkEndArgs(args);
	return(size);
}

XkSize xkWStringFFormat(XkWString string, XkWString format, XkArgs args) {
	/*TODO: remove vswprintf*/
	int size = vswprintf((wchar_t*)string, 1024, (const wchar_t*)format, args);
	return((XkSize)size);
}

XkSize xkWStringNFFormat(XkWString string, const XkSize length, XkWString format, XkArgs args) {
	/*TODO: remove vswprintf*/
	int size = vswprintf((wchar_t*)string, (size_t)length, (const wchar_t*)format, args);
	return((XkSize)size);
}
