#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkResult __xkFileInitialize(void) {
	XkResult result = XK_SUCCESS;

	/// NOTE: Nothing doing here.

_catch:
	return(result);
}

void __xkFileTerminate(void) {
	/// NOTE: Nothing doing here.
}

XkResult __xkOpenFile(XkFile file, const XkChar8* name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	UINT flags = 0;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= OF_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= OF_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= OF_READWRITE;
	//if(flag & XK_FILE_FLAG_AP_BIT) flags |= OF_APPEND;
	/// TODO: implementation.
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= OF_CREATE;

	file->handle.handle = OpenFile(name, NULL, flags);
	if(file->handle.handle == HFILE_ERROR) {
		__xkErrorHandle("Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkCloseFile(XkFile file) {
	CloseHandle(file->handle.handle);
}

XkResult __xkCreateFile(XkFile file, const XkChar8* name) {
	XkResult result = XK_SUCCESS;

	file->handle.handle = CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(file->handle.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Failed to create file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;	
	}

_catch:
	return(result);
}

void __xkRemoveFile(const XkChar8* name) {
	DeleteFileA(name);
}

void __xkRenameFile(const XkChar8* oldName, const XkChar8* newName) {
	MoveFile(oldName, newName);
}

XkSize __xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	DWORD moveMethod = 0;

	if(seek == 0) moveMethod = FILE_BEGIN;
	if(seek == 1) moveMethod = FILE_CURRENT;
	if(seek == 2) moveMethod = FILE_END;

	DWORD pointer = SetFilePointer(file->handle.handle, offset, NULL, moveMethod);
	return((XkSize)pointer);
}

void __xkWriteFile(XkFile file, const XkChar8* buffer, const XkSize size) {
	WORD numberOfBytesWrite;
	WriteFile(file->handle.handle, buffer, size, &numberOfBytesWrite, NULL);
}

void __xkReadFile(XkFile file, XkChar8* buffer, const XkSize size) {
	WORD numberOfBytesRead;
	ReadFile(file->handle.handle, buffer, size, &numberOfBytesRead, NULL);
}

#endif // XK_WIN32
