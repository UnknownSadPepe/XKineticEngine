/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult xkOpenFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	xkAssert(pFile);

	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile_T));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	DWORD flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= FILE_APPEND_DATA;

	DWORD open = OPEN_EXISTING;
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	file->windows.winapi.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);
	if(file->windows.winapi.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(file) {
		xkFreeMemory(file);
	}

	goto _catch;
}

XkResult xkOpenAsyncFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	xkAssert(pFile);

	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile_T));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	DWORD flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= FILE_APPEND_DATA;

	DWORD open = OPEN_EXISTING;
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	file->windows.winapi.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_FLAG_OVERLAPPED, NULL);
	if(file->windows.winapi.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	file->windows.winapi.overlapped.Offset = 0;
	file->windows.winapi.overlapped.OffsetHigh = 0;

	file->windows.winapi.overlapped.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if(file->windows.winapi.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to create async file event");
		result = XK_ERROR_UNKNOWN;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(file) {
		xkFreeMemory(file);
	}

	goto _catch;
}

void xkCloseFile(XkFile file) {
	xkAssert(file);

	CloseHandle(file->windows.winapi.handle);

	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	xkAssert(file);

	LARGE_INTEGER size;
	GetFileSizeEx(file->windows.winapi.handle, &size);

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
	xkAssert(file);

	DWORD moveMethod = 0;
	if(seek == XK_FILE_SEEK_SET) moveMethod = FILE_BEGIN;
	if(seek == XK_FILE_SEEK_CUR) moveMethod = FILE_CURRENT;
	if(seek == XK_FILE_SEEK_END) moveMethod = FILE_END;

	DWORD pointer = SetFilePointer(file->windows.winapi.handle, offset, NULL, moveMethod);

	return((XkSize)pointer);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);

	DWORD numberOfBytesWrite;
	WriteFile(file->windows.winapi.handle, buffer, size, &numberOfBytesWrite, NULL);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);

	DWORD numberOfBytesRead;
	ReadFile(file->windows.winapi.handle, buffer, size, &numberOfBytesRead, NULL);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);

	WriteFile(file->windows.winapi.handle, buffer, size, NULL, &file->windows.winapi.overlapped);

	file->windows.winapi.overlapped.Offset += (DWORD)size;
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);

	ReadFile(file->windows.winapi.handle, buffer, size, NULL, &file->windows.winapi.overlapped);
}

void xkWaitAsyncFile(XkFile file) {
	xkAssert(file);

	WaitForSingleObject(file->windows.winapi.overlapped.hEvent, INFINITE);

	if(!ResetEvent(file->windows.winapi.overlapped.hEvent)) {
		__xkErrorHandle("Win32: Failed to reset async file event");
	}	
}