#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkResult xkOpenFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	DWORD flags = 0;
	DWORD open = OPEN_EXISTING;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	//if(flag & XK_FILE_FLAG_AP_BIT) flags |= OF_APPEND;
	/// TODO: implementation.
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	file->handle.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);
	if(file->handle.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult xkOpenAsyncFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	/// TODO: impementation.

	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	DWORD flags = 0;
	DWORD open = OPEN_EXISTING;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	//if(flag & XK_FILE_FLAG_AP_BIT) flags |= OF_APPEND;
	/// TODO: implementation.
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	file->handle.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_FLAG_OVERLAPPED, NULL);
	if(file->handle.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	file->handle.overlapped.Offset = 0;
	file->handle.overlapped.OffsetHigh = 0;

	file->handle.overlapped.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if(file->handle.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to create async file event");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	CloseHandle(file->handle.handle);
	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	LARGE_INTEGER size;
	GetFileSizeEx(file->handle.handle, &size);
	return((XkSize)size.QuadPart);
}

void xkCreateFile(const XkString name) {
	CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

void xkRemoveFile(const XkString name) {
	DeleteFileA(name);
}

void xkRenameFile(const XkString oldName, const XkString newName) {
	MoveFile(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	DWORD moveMethod = 0;

	if(seek == XK_FILE_SEEK_SET) moveMethod = FILE_BEGIN;
	if(seek == XK_FILE_SEEK_CUR) moveMethod = FILE_CURRENT;
	if(seek == XK_FILE_SEEK_END) moveMethod = FILE_END;

	DWORD pointer = SetFilePointer(file->handle.handle, offset, NULL, moveMethod);
	return((XkSize)pointer);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	DWORD numberOfBytesWrite;
	WriteFile(file->handle.handle, buffer, size, &numberOfBytesWrite, NULL);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	DWORD numberOfBytesRead;
	ReadFile(file->handle.handle, buffer, size, &numberOfBytesRead, NULL);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	/// TODO: impementation.

	WriteFile(file->handle.handle, buffer, size, NULL, &file->handle.overlapped);

	if(WaitForSingleObject(file->handle.overlapped.hEvent, INFINITE) != WAIT_OBJECT_0) {
		__xkErrorHandle("Win32: Failed to wait async file event");
		return;
	}

	if(!ResetEvent(file->handle.overlapped.hEvent)) {
		__xkErrorHandle("Win32: Failed to reset async file event");
		return;
	}

	file->handle.overlapped.Offset += (DWORD)size;
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	/// TODO: impementation.

	ReadFile(file->handle.handle, buffer, size, NULL, &file->handle.overlapped);

	WaitForSingleObject(file->handle.overlapped.hEvent, INFINITE);

	if(!ResetEvent(file->handle.overlapped.hEvent)) {
		__xkErrorHandle("Win32: Failed to reset async file event");
	}
}

#endif // XK_WIN32
