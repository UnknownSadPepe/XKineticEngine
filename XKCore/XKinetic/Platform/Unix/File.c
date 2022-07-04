/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

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

	int flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	file->unix.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->unix.handle <= 0) {
		__xkErrorHandle("Unix: Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
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

	int flags = 0;
	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	file->unix.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->unix.handle <= 0) {
		__xkErrorHandle("Unix: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	xkAssert(file);

	close(file->unix.handle);

	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	xkAssert(file);

	struct stat stat;
	fstat(file->unix.handle, &stat);

	return((XkSize)stat.st_size);
}

void xkCreateFile(const XkString name) {
	creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

void xkRemoveFile(const XkString name) {
	unlink(name);
}

void xkRenameFile(const XkString oldName, const XkString newName) {
	link(oldName, newName);
}

XkSize xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
	xkAssert(file);

	int whence = 0;
	switch(seek) {
		case XK_FILE_SEEK_SET: whence = SEEK_SET; break;
		case XK_FILE_SEEK_CUR: whence = SEEK_CUR; break;
		case XK_FILE_SEEK_END: whence = SEEK_END; break;
	}

	size_t size = lseek(file->unix.handle, (long)offset, whence);

	return((XkSize)size);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);

	write(file->unix.handle, buffer, size);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);

	read(file->unix.handle, buffer, size);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);
	/// TODO: Implementation.
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);
	/// TODO: Implementation.
}
