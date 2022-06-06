#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/File.h"

#if defined(XK_UNIX)

#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>

XkResult xkFileInitialize(void) {
	XkResult result = XK_SUCCESS;

	/// NOTE: Nothing to do here.

_catch:
	return(result);
}

void xkFileTerminate(void) {
	/// NOTE: Nothing to do here.
}

XkResult xkOpenFile(XkFile file, const XkChar8* name, const XkFileFlag flag) {
	XkResult result = XK_SUCCESS;

	int flags = 0;

	if(flag & XK_FILE_FLAG_RO_BIT) flags |= O_RDONLY;
	if(flag & XK_FILE_FLAG_WO_BIT) flags |= O_RDWR;
	if(flag & XK_FILE_FLAG_RW_BIT) flags |= O_WRONLY;
	if(flag & XK_FILE_FLAG_AP_BIT) flags |= O_APPEND;
	if(flag & XK_FILE_FLAG_CR_BIT) flags |= O_CREAT;

	file->handle.handle = open(name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->handle.handle <= 0) {
		__xkErrorHandle("Failed to open file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkCloseFile(XkFile file) {
	close(file->handle.handle);
}

XkResult xkCreateFile(XkFile file, const XkChar8* name) {
	XkResult result = XK_SUCCESS;

	file->handle.handle = creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(file->handle.handle <= 0) {
		__xkErrorHandle("Failed to create file");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkRemoveFile(const XkChar8* name) {
	unlink(name);
}

void xkRenameFile(const XkChar8* oldName, const XkChar8* newName) {
	link(oldName, newName);
}

XkSize __xkSeekFile(XkFile file, const XkInt32 offset, const XkFileSeek seek) {
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

#endif // XK_UNIX
