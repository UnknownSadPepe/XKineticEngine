/* ########## INCLUDE SECTION ########## */
/// TODO: remove #include <wchar.h>
#include <wchar.h>
/*TODO: remove #include <stdio.h>*/
#include <stdio.h>
#include "XKinetic/Core/Types.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/String.h"

/* ########## FUNCTIONS SECTION ########## */
void xkStringFromString8(XkString string, XkString8 string8) {
	while(*string && *string8) {
		*string = (XkChar)*string8;

		++string;
		++string8;
	}
	*string = '\0';
}

void xkNStringFromString8(XkString string, XkString8 string8, const XkSize length) {
	XkSize len = length;
	while(*string && *string8 && --len) {
		*string = (XkChar)*string8;

		++string;
		++string8;
	}
	*string = '\0';
}

void xkStringFromString16(XkString string, XkString16 string16) {
	while(*string && *string16) {
		*string = (XkChar)*string16;

		++string;
		++string16;
	}
	*string = '\0';
}

void xkNStringFromString16(XkString string, XkString16 string16, const XkSize length) {
	XkSize len = length;
	while(*string && *string16 && --len) {
		*string = (XkChar)*string16;

		++string;
		++string16;
	}
	*string = '\0';
}

void xkStringFromString32(XkString string, XkString32 string32) {
	while(*string && *string32) {
		*string = (XkChar)*string32;

		++string;
		++string32;
	}
	*string = '\0';
}

void xkNStringFromString32(XkString string, XkString32 string32, const XkSize length) {
	XkSize len = length;
	while(*string && *string32 && --len) {
		*string = (XkChar)*string32;

		++string;
		++string32;
	}
	*string = '\0';
}

void xkStringFromWString(XkString string, XkWString wstring) {
	while(*string && *wstring) {
		*string = (XkChar)*wstring;

		++string;
		++wstring;
	}
	*string = '\0';
}

void xkNStringFromWString(XkString string, XkWString wstring, const XkSize length) {
	XkSize len = length;
	while(*string && *wstring) {
		*string = (XkChar)*wstring;

		++string;
		++wstring;
	}
	*string = '\0';
}

void xkString8FromString(XkString8 string8, XkString string) {
	while(*string8 && *string) {
		*string8 = (XkChar8)*string;

		++string8;
		++string;
	}
	*string8 = '\0';
}

void	xkNString8FromString(XkString8 string8, XkString string, const XkSize length) {
	XkSize len = length;
	while(*string8 && *string && --len) {
		*string8 = (XkChar8)*string;

		++string8;
		++string;
	}
	*string8 = '\0';
}

void	xkString8FromString16(XkString8 string8, XkString16 string16) {
	while(*string8 && *string16) {
		*string8 = (XkChar8)*string16;

		++string8;
		++string16;
	}
	*string8 = '\0';
}

void	xkNString8FromString16(XkString8 string8, XkString16 string16, const XkSize length) {
	XkSize len = length;
	while(*string8 && *string16 && --len) {
		*string8 = (XkChar8)*string16;

		++string8;
		++string16;
	}
	*string8 = '\0';
}

void	xkString8FromString32(XkString8 string8, XkString32 string32) {
	while(*string8 && *string32) {
		*string8 = (XkChar8)*string32;

		++string8;
		++string32;
	}
	*string8 = '\0';
}

void	xkNString8FromString32(XkString8 string8, XkString32 string32, const XkSize length) {
	XkSize len = length;
	while(*string8 && *string32 && --len) {
		*string8 = (XkChar8)*string32;

		++string8;
		++string32;
	}
	*string8 = '\0';
}

void xkString8FromWString(XkString8 string8, XkWString wstring) {
	while(*string8 && *wstring) {
		*string8 = (XkChar8)*wstring;

		++string8;
		++wstring;
	}
	*string8 = '\0';
}

void xkNString8FromWString(XkString8 string8, XkWString wstring, const XkSize length) {
	XkSize len = length;
	while(*string8 && *wstring && --len) {
		*string8 = (XkChar8)*wstring;

		++string8;
		++wstring;
	}
	*string8 = '\0';
}

void xkString16FromString(XkString16 string16, XkString string) {
	while(*string16 && *string) {
		*string16 = (XkChar16)*string;

		++string16;
		++string;
	}
	*string16 = u'\0';
}

void xkNString16FromString(XkString16 string16, XkString string, const XkSize length) {
	XkSize len = length;
	while(*string16 && *string && --len) {
		*string16 = (XkChar16)*string;

		++string16;
		++string;
	}
	*string16 = u'\0';
}

void xkString16FromString8(XkString16 string16, XkString8 string8) {
	while(*string16 && *string8) {
		*string16 = (XkChar16)*string8;

		++string16;
		++string8;
	}
	*string16 = u'\0';
}

void xkNString16FromString8(XkString16 string16, XkString8 string8, const XkSize length) {
	XkSize len = length;
	while(*string16 && *string8 && --len) {
		*string16 = (XkChar16)*string8;

		++string16;
		++string8;
	}
	*string16 = u'\0';
}

void xkString16FromString32(XkString16 string16, XkString32 string32) {
	while(*string16 && *string32) {
		*string16 = (XkChar16)*string32;

		++string16;
		++string32;
	}
	*string16 = u'\0';
}

void xkNString16FromString32(XkString16 string16, XkString32 string32, const XkSize length) {
	XkSize len = length;
	while(*string16 && *string32 && --len) {
		*string16 = (XkChar16)*string32;

		++string16;
		++string32;
	}
	*string16 = u'\0';
}

void xkString16FromWString(XkString16 string16, XkWString wstring) {
	while(*string16 && *wstring) {
		*string16 = (XkChar16)*wstring;

		++string16;
		++wstring;
	}
	*string16 = u'\0';
}

void xkNString16FromWString(XkString16 string16, XkWString wstring, const XkSize length) {
	XkSize len = length;
	while(*string16 && *wstring && --len) {
		*string16 = (XkChar16)*wstring;

		++string16;
		++wstring;
	}
	*string16 = u'\0';
}

void xkString32FromString(XkString32 string32, XkString string) {
	while(*string32 && *string) {
		*string32 = (XkChar32)*string;

		++string32;
		++string;
	}
	*string32 = U'\0';
}

void xkNString32FromString(XkString32 string32, XkString string, const XkSize length) {
	XkSize len = length;
	while(*string32 && *string && --len) {
		*string32 = (XkChar32)*string;

		++string32;
		++string;
	}
	*string32 = U'\0';
}

void xkString32FromString8(XkString32 string32, XkString8 string8) {
	while(*string32 && *string8) {
		*string32 = (XkChar32)*string8;

		++string32;
		++string8;
	}
	*string32 = U'\0';
}

void xkNString32FromString8(XkString32 string32, XkString8 string8, const XkSize length) {
	XkSize len = length;
	while(*string32 && *string8 && --len) {
		*string32 = (XkChar32)*string8;

		++string32;
		++string8;
	}
	*string32 = U'\0';
}

void xkString32FromString16(XkString32 string32, XkString16 string16) {
	while(*string32 && *string16) {
		*string32 = (XkChar32)*string16;

		++string32;
		++string16;
	}
	*string32 = U'\0';
}

void xkNString32FromString16(XkString32 string32, XkString16 string16, const XkSize length) {
	XkSize len = length;
	while(*string32 && *string16 && --len) {
		*string32 = (XkChar32)*string16;

		++string32;
		++string16;
	}
	*string32 = U'\0';
}

void xkString32FromWString(XkString32 string32, XkWString wstring) {
	while(*string32 && *wstring) {
		*string32 = (XkChar32)*wstring;

		++string32;
		++wstring;
	}
	*string32 = U'\0';
}

void xkNString32FromWString(XkString32 string32, XkWString wstring, const XkSize length) {
	XkSize len = length;
	while(*string32 && *wstring && --len) {
		*string32 = (XkChar32)*wstring;

		++string32;
		++wstring;
	}
	*string32 = U'\0';
}

void xkWStringFromString(XkWString wstring, XkString string) {
	while(*wstring && *string) {
		*wstring = (XkWChar)*string;

		++wstring;
		++string;
	}
	*wstring = L'\0';
}

void xkNWStringFromString(XkWString wstring, XkString string, const XkSize length) {
	XkSize len = length;
	while(*wstring && *string && --len) {
		*wstring = (XkWChar)*string;

		++wstring;
		++string;
	}
	*wstring = L'\0';
}

void xkWStringFromString8(XkWString wstring, XkString8 string8) {
	while(*wstring && *string8) {
		*wstring = (XkWChar)*string8;

		++wstring;
		++string8;
	}
	*wstring = L'\0';
}

void xkNWStringFromString8(XkWString wstring, XkString8 string8, const XkSize length) {
	XkSize len = length;
	while(*wstring && *string8 && --len) {
		*wstring = (XkWChar)*string8;

		++wstring;
		++string8;
	}
	*wstring = L'\0';
}

void xkWStringFromString16(XkWString wstring, XkString16 string16) {
	while(*wstring && *string16) {
		*wstring = (XkWChar)*string16;

		++wstring;
		++string16;
	}
	*wstring = L'\0';
}

void xkNWStringFromString16(XkWString wstring, XkString16 string16, const XkSize length) {
	XkSize len = length;
	while(*wstring && *string16 && --len) {
		*wstring = (XkWChar)*string16;

		++wstring;
		++string16;
	}
	*wstring = L'\0';
}

void xkWStringFromString32(XkWString wstring, XkString32 string32) {
	while(*wstring && *string32) {
		*wstring = (XkWChar)*string32;

		++wstring;
		++string32;
	}
	*wstring = L'\0';
}

void xkNWStringFromString32(XkWString wstring, XkString32 string32, const XkSize length) {
	XkSize len = length;
	while(*wstring && *string32 && --len) {
		*wstring = (XkWChar)*string32;

		++wstring;
		++string32;
	}
	*wstring = L'\0';
}

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

	return(XK_NULL_HANDLE);
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

	return(XK_NULL_HANDLE);
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
	/// TODO: remove 'vsprintf'.
	int size = vsprintf(string, format, args);
	return((XkSize)size);
}

XkSize xkStringNFFormat(XkString string, const XkSize length, XkString format, XkArgs args) {
	/// TODO: remove 'vsnprintf'.
	int size = vsnprintf(string, (unsigned long)length, (const char*)format, args);
	return((XkSize)size);
}

XkSize xkString8Length(XkString8 string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkString8 xkCopyString8(XkString8 dstString, XkString8 srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkString8 xkNCopyString8(XkString8 dstString, XkString8 srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = '\0';
	return(dstString);
}

XkString8 xkConcatString8(XkString8 dstString, XkString8 srcString) {
	return(xkCopyString8(dstString + xkString8Length(dstString), srcString));
}

XkString8 xkNConcatString8(XkString8 dstString, XkString8 srcString, const XkSize length) {
	return(xkNCopyString8(dstString + xkString8Length(dstString), srcString, length));
}

XkInt32 xkCompareString8(XkString8 string1, XkString8 string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareString8(XkString8 string1, XkString8 string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkString8 xkTokenString8(XkString8 string, XkString8 token) {
	XkSize count = 0;

	while(*string) {
		if(xkDelim8(*string, token)) {
			*string = '\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString8 xkNTokenString8(XkString8 string, XkString8 token, const XkSize length) {
	XkSize count = 0;
	
	XkSize len = length;
	while(*string && --len) {
		if(xkDelim8(*string, token)) {
			*string = '\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString8 xkDuplicateString8(XkString8 string) {
  const XkSize length = xkString8Length(string);
  XkString8 result = xkAllocateMemory(sizeof(XkChar8) * (length + 1));
  xkCopyString8(result, string);
  return(result);
}

XkString8 xkNDublicateString8(XkString8 string, const XkSize length) {
  XkString8 result = xkAllocateMemory(sizeof(XkChar8) * (length + 1));
  xkNCopyString8(result, string, length);
  return(result);
}

XkSize xkString16Length(XkString16 string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkString16 xkCopyString16(XkString16 dstString, XkString16 srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = u'\0';
	return(dstString);
}

XkString16 xkNCopyString16(XkString16 dstString, XkString16 srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = u'\0';
	return(dstString);
}

XkString16 xkConcatString16(XkString16 dstString, XkString16 srcString) {
	return(xkCopyString16(dstString + xkString16Length(dstString), srcString));
}

XkString16 xkNConcatString16(XkString16 dstString, XkString16 srcString, const XkSize length) {
	return(xkNCopyString16(dstString + xkString16Length(dstString), srcString, length));
}

XkInt32 xkCompareString16(XkString16 string1, XkString16 string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareString16(XkString16 string1, XkString16 string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkString16 xkTokenString16(XkString16 string, XkString16 token) {
	while(*string) {
		if(xkDelim16(*string, token)) {
			*string = u'\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString16 xkNTokenString16(XkString16 string, XkString16 token, const XkSize length) {
	XkSize len = length;
	while(*string && --len) {
		if(xkDelim16(*string, token)) {
			*string = u'\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString16 xkDuplicateString16(XkString16 string) {
  const XkSize length = xkString16Length(string);
  XkString16 result = xkAllocateMemory(sizeof(XkChar16) * (length + 1));
  xkCopyString16(result, string);
  return(result);
}

XkString16 xkNDublicateString16(XkString16 string, const XkSize length) {
  XkString16 result = xkAllocateMemory(sizeof(XkChar16) * (length + 1));
  xkNCopyString16(result, string, length);
  return(result);
}

XkSize xkString32Length(XkString32 string) {
	XkSize length = 0;
	while(*string) {
		++length;
		++string;
	}
	return(length);
}

XkString32 xkCopyString32(XkString32 dstString, XkString32 srcString) {
	while(*srcString) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = U'\0';
	return(dstString);
}

XkString32 xkNCopyString32(XkString32 dstString, XkString32 srcString, const XkSize length) {
	XkSize len = length;
	while(*srcString && --len) {
		*dstString = *srcString;
		++dstString;
		++srcString;
	}
	*dstString = U'\0';
	return(dstString);
}

XkString32 xkConcatString32(XkString32 dstString, XkString32 srcString) {
	return(xkCopyString32(dstString + xkString32Length(dstString), srcString));
}

XkString32 xkNConcatString32(XkString32 dstString, XkString32 srcString, const XkSize length) {
	return(xkNCopyString32(dstString + xkString32Length(dstString), srcString, length));
}

XkInt32 xkCompareString32(XkString32 string1, XkString32 string2) {
	while((*string1 && *string2) && *string1 == *string2) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkInt32 xkNCompareString32(XkString32 string1, XkString32 string2, const XkSize length) {
	XkSize len = length;
	while((*string1 && *string2) && (*string1 == *string2) && --len) {
		++string1;
		++string2;
	}

	XkInt32 status = (*string1 == *string2) ? 1 : (*string1 > *string2) ? 0 : -1;
	return(status);
}

XkString32 xkTokenString32(XkString32 string, XkString32 token) {
	while(*string) {
		if(xkDelim32(*string, token)) {
			*string = U'\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString32 xkNTokenString32(XkString32 string, XkString32 token, const XkSize length) {
	XkSize len = length;
	while(*string && --len) {
		if(xkDelim32(*string, token)) {
			*string = U'\0';
			return(string + 1);
		}
		++string;
	}

	return(XK_NULL_HANDLE);
}

XkString32 xkDuplicateString32(XkString32 string) {
  const XkSize length = xkString32Length(string);
  XkString32 result = xkAllocateMemory(sizeof(XkChar32) * (length + 1));
  xkCopyString32(result, string);
  return(result);
}

XkString32 xkNDublicateString32(XkString32 string, const XkSize length) {
  XkString32 result = xkAllocateMemory(sizeof(XkChar32) * (length + 1));
  xkNCopyString32(result, string, length);
  return(result);
}

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

	return(XK_NULL_HANDLE);
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

	return(XK_NULL_HANDLE);
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
	/// TODO: Remove 'vswprintf'.
	int size = vswprintf((wchar_t*)string, 1024, (const wchar_t*)format, args);

	return((XkSize)size);
}

XkSize xkWStringNFFormat(XkWString string, const XkSize length, XkWString format, XkArgs args) {
	/// TODO: Remove 'vswprintf'.
	int size = vswprintf((wchar_t*)string, (size_t)length, (const wchar_t*)format, args);
	
	return((XkSize)size);
}
