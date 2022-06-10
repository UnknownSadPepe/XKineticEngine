#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_UNIX)

#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>

XkResult xkOpenFile(XkFile* pFile, const XkChar8* name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	int flags = 0;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	file->handle.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->handle.handle <= 0) {
		__xkErrorHandle("Unix: Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult xkOpenAsyncFile(XkFile* pFile, const XkChar8* name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	/// TODO: implementation.

	*pFile = xkAllocateMemory(sizeof(struct XkFile));
	if(!(*pFile)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkFile file = *pFile;

	int flags = 0;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

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
	close(file->handle.handle);
	xkFreeMemory(file);
}

void xkCreateFile(const XkChar8* name) {
	creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

void xkRemoveFile(const XkChar8* name) {
	unlink(name);
}

void xkRenameFile(const XkChar8* oldName, const XkChar8* newName) {
	link(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	int whence = 0;

	switch(seek) {
		case XK_FILE_SEEK_SET: whence = SEEK_SET; break;
		case XK_FILE_SEEK_CUR: whence = SEEK_CUR; break;
		case XK_FILE_SEEK_END: whence = SEEK_END; break;
	}

	return((XkSize)lseek(file->handle.handle, (long)offset, whence));
}

void xkWriteFile(XkFile file, const XkChar8* buffer, const XkSize size) {
	write(file->handle.handle, buffer, size);
}

void xkReadFile(XkFile file, XkChar8* buffer, const XkSize size) {
	read(file->handle.handle, buffer, size);
}

void xkAsyncWriteFile(XkFile file, const XkChar8* buffer, const XkSize size) {
	/// TODO: implementation.
}

void xkAsyncReadFile(XkFile file, XkChar8* buffer, const XkSize size) {
	/// TODO: implementation.
}

#endif // XK_UNIX
