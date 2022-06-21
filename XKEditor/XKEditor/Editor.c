#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"

struct XkApplication {
	XkApplicationConfig config;
};

XkApplication _xkApplication;

XkResult xkCreateApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKEditor";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) goto _catch;

	XkFreeList freelist;
	result = xkCreateFreeList(&freelist, sizeof(XkUInt32) * 16);
	if(result != XK_SUCCESS) {
		xkLogError("failed to create freelist");
		goto _catch;
	}

	XkUInt32* pf1 = xkFreeListAllocate(freelist, sizeof(XkUInt32));
	xkLogInfo("freelist: {%p} %d", pf1, *pf1);

	XkUInt32* pf2 = xkFreeListAllocate(freelist, sizeof(XkUInt32) * 10);
	for (XkSize i = 0; i < 10; i++) {
		xkLogInfo("freelist: {%p} %d", &pf2[i], pf2[i]);
	}

	XkUInt32* pf3 = xkFreeListAllocate(freelist, sizeof(XkUInt32) * 4);
	for (XkSize i = 0; i < 4; i++) {
		xkLogInfo("freelist: {%p} %d", &pf3[i], pf3[i]);
	}

	xkFreeListFree(freelist, pf2);
	xkFreeListFree(freelist, pf1);

	xkDestroyFreeList(freelist);

	XkHashTable hashtable;
	result = xkCreateHashTableCapacity(&hashtable, 16, XkUInt32);
	if(result != XK_SUCCESS) {
		xkLogError("failed to create hashtable");
		goto _catch;
	}

	xkHashTableInsert(hashtable, "mom", 666);
	xkHashTableInsert(hashtable, "dad", 777);
	xkHashTableInsert(hashtable, "son", 999);
	xkHashTableInsert(hashtable, "sys", 888);
	xkHashTableInsert(hashtable, "hello", 5);
	xkHashTableInsert(hashtable, "fuck", 2);
	xkHashTableInsert(hashtable, "duck", 1);
	xkHashTableInsert(hashtable, "kyplinov", 444);

	XkUInt32* ph1 = xkHashTableGet(hashtable, "mom");
	XkString ph2 = xkHashTableGet(hashtable, "dad");
	XkString ph3 = xkHashTableGet(hashtable, "son");
	XkUInt32* ph4 = xkHashTableGet(hashtable, "sys");
	XkUInt32* ph5 = xkHashTableGet(hashtable, "hello");
	XkUInt32* ph6 = xkHashTableGet(hashtable, "fuck");
	XkUInt32* ph7 = xkHashTableGet(hashtable, "duck");
	XkUInt32* ph8 = xkHashTableGet(hashtable, "kyplinov");
	xkLogInfo("hashtable: [%s]\t{%p} %d", "mom", ph1, *ph1);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "dad", ph2, *ph2);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "son", ph3, *ph3);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "sys", ph4, *ph4);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "hello", ph5, *ph5);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "fuck", ph6, *ph6);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "duck", ph7, *ph7);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "kyplinov", ph8, *ph8);
	
	xkHashTableSet(hashtable, "duck", 999);

	xkLogInfo("hashtable: [%s]\t{%p} %d", "mom", ph1, *ph1);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "dad", ph2, *ph2);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "son", ph3, *ph3);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "sys", ph4, *ph4);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "hello", ph5, *ph5);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "fuck", ph6, *ph6);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "duck", ph7, *ph7);
	xkLogInfo("hashtable: [%s]\t{%p} %d", "kyplinov", ph8, *ph8);

	xkDestroyHashTable(hashtable);

_catch:
	return(result);
}

void xkDestroyApplication(void) {
	xkTerminateLog();
}

void xkUpdateApplication(void) {

}
