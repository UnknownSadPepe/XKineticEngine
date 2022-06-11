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

  DCB dcb = {0};
  COMMTIMEOUTS timeouts;

  dcb.DCBlength = sizeof(dcb);

  GetCommTimeouts(file->handle.handle, &timeouts);
  GetCommTimeouts(file->handle.handle, &timeouts);
  timeouts.ReadIntervalTimeout          = 50;
  timeouts.ReadTotalTimeoutConstant     = 50;
  timeouts.ReadTotalTimeoutMultiplier   = 50;
  timeouts.WriteTotalTimeoutConstant    = 50;
  timeouts.WriteTotalTimeoutMultiplier  = 10;
  if(!SetCommTimeouts(file->handle.handle, &timeouts)) {
		__xkErrorHandle("Win32: Failed to setting timeouts on port");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

  GetCommState(file->handle.handle, &dcb);
  dcb.BaudRate =          19200;
  dcb.Parity =            NOPARITY;
  dcb.fBinary =           TRUE;
  dcb.fParity =           FALSE;            
  dcb.fOutxCtsFlow =      FALSE;
  dcb.fOutxDsrFlow =      FALSE;
  dcb.fDtrControl =       DTR_CONTROL_DISABLE; // DTR flow control type 
  dcb.fDsrSensitivity =   FALSE;            // DSR sensitivity 
  dcb.fTXContinueOnXoff = FALSE;            // XOFF continues Tx 
  dcb.fOutX =             FALSE;            // No XON/XOFF out flow control 
  dcb.fInX =              FALSE;            // No XON/XOFF in flow control
  dcb.fErrorChar =        FALSE;            // Disable error replacement 
  dcb.fNull =             FALSE;            // Disable null stripping 
  dcb.fRtsControl =       RTS_CONTROL_DISABLE; // RTS flow control 
  dcb.fAbortOnError =     FALSE;            // Do not abort reads/writes on err
  dcb.ByteSize =          8;                // Number of bits/byte, 4-8 
  dcb.StopBits =          ONESTOPBIT;       // 0,1,2 = 1, 1.5, 2
  dcb.EvtChar =           0x84;             // 'T' 

  if (!SetCommState (file->handle.handle, &dcb)) {
		__xkErrorHandle("Win32: Failed to configure serial port");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }
  return 0;

_catch:
	return(result);
}

XkResult xkOpenAsyncFile(XkFile* pFile, const XkString name, const XkFileFlag flag) {
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

	file->handle.handle = CreateFile(name, flags, FILE_SHARE_READ, NULL, open, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if(file->handle.handle == INVALID_HANDLE_VALUE) {
		__xkErrorHandle("Win32: Failed to open async file");
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
	/// TODO: implementation.
	OVERLAPPED oWrite = {
		.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)
	};
	WriteFile(file->handle.handle, buffer, size, NULL, &oWrite);

	DWORD dwCommEvent;
	WaitCommEvent(file->handle.handle, &dwCommEvent, &oWrite);

	CloseHandle(oWrite.hEvent);
}

void xkAsyncReadFile(XkFile file, XkString buffer, const XkSize size) {
	/// TODO: implementation.
	OVERLAPPED oRead = {
		.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)
	};
	ReadFile(file->handle.handle, buffer, size, NULL, &oRead);

	DWORD dwCommEvent;
	WaitCommEvent(file->handle.handle, &dwCommEvent, &oRead);

	CloseHandle(oRead.hEvent);
}

#endif // XK_WIN32
