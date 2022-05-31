#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/String.h"
#include "XKinetic/Core/File.h"
#include "XKinetic/Core/Memory.h"

#define XK_FILE_BUFFER_SIZE 1024

XkResult xkFileInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = __xkFileInitialize();
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkFileTerminate(void) {
	__xkFileTerminate();
}

XkResult xkOpenFile(XkFile* pFile, const XkChar8* name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!pFile) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkFile file = *pFile;

	result = __xkOpenFile(file, name, flag);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	__xkCloseFile(file);
	xkFreeMemory(file);
}

XkResult xkCreateFile(XkFile* pFile, const XkChar8* name) {
	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!pFile) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkFile file = *pFile;

	result = __xkCreateFile(file, name);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkRemoveFile(const XkChar8* name) {
	__xkRemoveFile(name);
}

void xkRenameFile(const XkChar8* oldName, const XkChar8* newName) {
	__xkRenameFile(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	return((XkSize)__xkSeekFile(file, offset, seek));
}

void xkFWriteFile(XkFile file, const XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	xkVWriteFile(file, format, args);
	xkEndArgs(args);
}

void xkFReadFile(XkFile file, XkChar8* format, ...) {
	XkArgs args;
	xkStartArgs(args, format);
	xkVReadFile(file, format, args);
	xkEndArgs(args);
}

void xkVWriteFile(XkFile file, const XkChar8* format, XkArgs args) {
	XkChar8 buffer[XK_FILE_BUFFER_SIZE] = {0};
	const XkSize size = xkStringNFFormat(buffer, XK_FILE_BUFFER_SIZE, format, args);
	__xkWriteFile(file, buffer, size);
}

void xkVReadFile(XkFile file, XkChar8* format, XkArgs args) {
	XkChar8 buffer[XK_FILE_BUFFER_SIZE] = {0};
	// TODO: implementation.
	const XkSize size = 0;
	__xkReadFile(file, buffer, size);
}

void xkWriteFile(XkFile file, const XkChar8* buffer, const XkSize size) {
	__xkWriteFile(file, buffer, size);
}

void xkReadFile(XkFile file, XkChar8* buffer, const XkSize size) {
	__xkReadFile(file, buffer, size);
}
