#pragma once

#define XK_NULL ((void*)0)

typedef enum {
	XK_ERROR_UNKNOWN										= -1,
	XK_SUCCESS													= 0,
	XK_ERROR_BAD_ALLOCATE								= 1,
	XK_ERROR_MODULE_NOT_PRESENT 				= 2,
	XK_ERROR_MODULE_SYMBOL_NOT_PRESENT 	= 3,
	XK_ERROR_RESOURCE_NOT_LOAD					= 4,
	XK_ERROR_RESOURCE_NOT_CREATE				= 5,
	XK_ERROR_CREATE_FAILED							= 6,
	XK_ERROR_INITIALIZE_FAILED					= 7
} XkResult;

typedef void* XkHandle;

typedef unsigned int XkBool32;

#define XK_FALSE 0
#define XK_TRUE 1

typedef char XkChar8;
typedef short XkChar16;
typedef long XkChar32;

typedef char XkInt8;
typedef unsigned char XkUInt8;
typedef short XkInt16;
typedef unsigned short XkUInt16;
typedef int XkInt32;
typedef unsigned int XkUInt32;
typedef long long XkInt64;
typedef unsigned long long XkUInt64;

typedef float XkFloat32;
typedef double XkFloat64;

typedef unsigned long XkSize;
