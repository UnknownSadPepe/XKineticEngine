#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_UNIX)

#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

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

	// Select file flags.
	int flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	// Open file.
	file->handle.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->handle.handle <= 0) {
		__xkErrorHandle("Unix: Failed to open file");
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
	int flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	// Open Unix file.
	file->handle.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->handle.handle <= 0) {
		__xkErrorHandle("Unix: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	// Close Unix file
	close(file->handle.handle);

	// Free file.
	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	// Get Unix file stat.
	struct stat stat;
	fstat(file->handle.handle, &stat);

	// Return file stat size.
	return((XkSize)stat.st_size);
}

void xkCreateFile(const XkString name) {
	// Create Unix file.
	creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

void xkRemoveFile(const XkString name) {
	// Remove Unix file.
	unlink(name);
}

void xkRenameFile(const XkString oldName, const XkString newName) {
	// Rename Unix file.
	link(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	// Select whence.
	int whence = 0;
	switch(seek) {
		case XK_FILE_SEEK_SET: whence = SEEK_SET; break;
		case XK_FILE_SEEK_CUR: whence = SEEK_CUR; break;
		case XK_FILE_SEEK_END: whence = SEEK_END; break;
	}

	// Seek Unix file.
	size_t seek = lseek(file->handle.handle, (long)offset, whence)

	return((XkSize)seek);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	// Write to Unix file.
	write(file->handle.handle, buffer, size);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	// Read from Unix file.
	read(file->handle.handle, buffer, size);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	/// TODO: implementation.
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	/// TODO: implementation.
}

#endif // XK_UNIX
