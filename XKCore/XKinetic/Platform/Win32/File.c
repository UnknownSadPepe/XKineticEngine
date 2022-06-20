#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkResult xkOpenFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	// Allocate file.
	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	// Template file.
	XkFile file = *pFile;

	// Select flags.
	DWORD flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= FILE_APPEND_DATA;

	// Check to open.
	DWORD open = OPEN_EXISTING;
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	// Open Win32 file.
	file->win32.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);
	if(file->win32.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult xkOpenAsyncFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	// Allocate file.
	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	// Template file.
	XkFile file = *pFile;

	// Select file flags.
	DWORD flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= GENERIC_READ;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= GENERIC_READ | GENERIC_WRITE;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= FILE_APPEND_DATA;

	// Check to open.
	DWORD open = OPEN_EXISTING;
	if(flag & XK_FILE_FLAG_CR_BIT) open = CREATE_ALWAYS;

	// Open Win32 file.
	file->win32.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_FLAG_OVERLAPPED, NULL);
	if(file->win32.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Initialize Win32 file overlapped.
	file->win32.overlapped.Offset = 0;
	file->win32.overlapped.OffsetHigh = 0;

	// Create Win32 file event.
	file->win32.overlapped.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if(file->win32.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to create async file event");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	// Close Win32 file.
	CloseHandle(file->win32.handle);

	// Free file.
	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	// Get Win32 file size.
	LARGE_INTEGER size;
	GetFileSizeEx(file->win32.handle, &size);

	// Return file size.
	return((XkSize)size.QuadPart);
}

void xkCreateFile(const XkString name) {
	// Create Win32 file.
	CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

void xkRemoveFile(const XkString name) {
	// Remove Win32 file.
	DeleteFileA(name);
}

void xkRenameFile(const XkString oldName, const XkString newName) {
	// Rename Win32 file.
	MoveFile(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	// Select move method.
	DWORD moveMethod = 0;
	if(seek == XK_FILE_SEEK_SET) moveMethod = FILE_BEGIN;
	if(seek == XK_FILE_SEEK_CUR) moveMethod = FILE_CURRENT;
	if(seek == XK_FILE_SEEK_END) moveMethod = FILE_END;

	// Set Win32 file pointer.
	DWORD pointer = SetFilePointer(file->win32.handle, offset, NULL, moveMethod);

	return((XkSize)pointer);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	// Write to file.
	DWORD numberOfBytesWrite;
	WriteFile(file->win32.handle, buffer, size, &numberOfBytesWrite, NULL);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	// Read from file.
	DWORD numberOfBytesRead;
	BOOL readed = ReadFile(file->win32.handle, buffer, size, &numberOfBytesRead, NULL);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	/// TODO: impementation.

	WriteFile(file->win32.handle, buffer, size, NULL, &file->win32.overlapped);

	if(WaitForSingleObject(file->win32.overlapped.hEvent, INFINITE) != WAIT_OBJECT_0) {
		__xkErrorHandle("Win32: Failed to wait async file event");
		return;
	}

	if(!ResetEvent(file->win32.overlapped.hEvent)) {
		__xkErrorHandle("Win32: Failed to reset async file event");
		return;
	}

	file->win32.overlapped.Offset += (DWORD)size;
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	/// TODO: impementation.

	BOOL readed = ReadFile(file->win32.handle, buffer, size, NULL, &file->win32.overlapped);

	WaitForSingleObject(file->win32.overlapped.hEvent, INFINITE);

	if(!ResetEvent(file->win32.overlapped.hEvent)) {
		__xkErrorHandle("Win32: Failed to reset async file event");
	}
}

#endif // XK_WIN32
