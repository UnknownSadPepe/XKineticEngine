/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

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

	file->posix.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->posix.handle <= 0) {
		__xkErrorHandle("Posix: Failed to open file");
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

	file->posix.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->posix.handle <= 0) {
		__xkErrorHandle("Posix: Failed to open async file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	xkAssert(file);

	close(file->posix.handle);

	xkFreeMemory(file);
}

XkSize xkFileSize(XkFile file) {
	xkAssert(file);

	struct stat stat;
	fstat(file->posix.handle, &stat);

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

	size_t size = lseek(file->posix.handle, (long)offset, whence);

	return((XkSize)size);
}

void xkWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);

	write(file->posix.handle, buffer, size);
}

void xkReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);

	read(file->posix.handle, buffer, size);
}

void xkAsyncWriteFile(XkFile file, const XkString buffer, const XkSize size) {
	xkAssert(file);

	struct aiocb* aio = XK_NULL_HANDLE;
	aio = xkAllocateMemory(sizeof(struct aiocb));
	if(!aio) {
		__xkErrorHandle("Posix: Failed to allocate async file buffer");	
	}

	aio->aio_buf 		= (void*)buffer;
	aio->aio_fildes = file->posix.handle;
	aio->aio_nbytes = size;
	aio->aio_offset = 0;

	if(aio_write(aio) < 0) {
		__xkErrorHandle("Posix: Failed to write async file buffer");	
		goto _free;
	}

	file->posix.aio = aio;

_catch:
	return;

_free:
	if(aio) {
		xkFreeMemory(aio);		
	}

	goto _catch;
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	xkAssert(file);

	struct aiocb* aio = XK_NULL_HANDLE;
	aio = xkAllocateMemory(sizeof(struct aiocb));
	if(!aio) {
		__xkErrorHandle("Posix: Failed to allocate async file buffer");	
		goto _catch;
	}

	xkZeroMemory(aio, sizeof(struct aiocb));

	aio->aio_buf 		= (void*)buffer;
	aio->aio_fildes = file->posix.handle;
	aio->aio_nbytes = size;
	aio->aio_offset = 0;

	if(aio_read(aio) < 0) {
		__xkErrorHandle("Posix: Failed to read async file buffer");	
		goto _free;
	}

	file->posix.aio = aio;

_catch:
	return;

_free:
	if(aio) {
		xkFreeMemory(aio);		
	}

	goto _catch;
}

void xkWaitAsyncFile(XkFile file) {
	xkAssert(file);

	/// NOTE: Wait until end of writing or reading.
	while(aio_error(file->posix.aio) == EINPROGRESS) {}

	if(aio_return(file->posix.aio) < 0) {
		__xkErrorHandle("Posix: Failed to wait async file");		
	}
}
