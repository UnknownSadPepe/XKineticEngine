#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/External.h" 

XK_API_EXPORT XkResult xkWindowInitialize(void);
XK_API_EXPORT void xkWindowTerminate(void);

XK_API_EXPORT XkResult xkCreateWindow(XkWindow*, const XkChar8*, const XkSize, const XkSize, const XkWindowHint);
XK_API_EXPORT void xkDestroyWindow(XkWindow);

XK_API_EXPORT void xkShowWindow(XkWindow, const XkWindowShow);

XK_API_EXPORT void xkFocusWindow(XkWindow);

XK_API_EXPORT void xkSetWindowSize(XkWindow, const XkSize, const XkSize);
XK_API_EXPORT void xkGetWindowSize(XkWindow, XkSize* const, XkSize* const);

XK_API_EXPORT void xkSetWindowSizeLimits(XkWindow, const XkSize, const XkSize, const XkSize, const XkSize);

XK_API_EXPORT void xkSetWindowPosition(XkWindow, const XkInt32, const XkInt32);
XK_API_EXPORT void xkGetWindowPosition(XkWindow, XkInt32* const, XkInt32* const);

XK_API_EXPORT void xkSetWindowTitle(XkWindow, const XkChar8*);

XK_API_EXPORT void xkSetWindowIcon(XkWindow, const XkSize, const XkWindowIcon*);

XK_API_EXPORT XkBool32 xkShouldWindowClosed(XkWindow);
XK_API_EXPORT XkBool32 xkShouldWindowShowed(XkWindow, const XkWindowShow);

XK_API_EXPORT void xkSetWindowShowCallback(XkWindow, const XkWindowShowPfn);
XK_API_EXPORT void xkSetWindowKeyCallback(XkWindow, const XkWindowKeyPfn);
XK_API_EXPORT void xkSetWindowButtonCallback(XkWindow, const XkWindowButtonPfn);
XK_API_EXPORT void xkSetWindowCursorCallback(XkWindow, const XkWindowCursorPfn);
XK_API_EXPORT void xkSetWindowCursorEnterCallback(XkWindow, const XkWindowCursorPfn);
XK_API_EXPORT void xkSetWindowScrollCallback(XkWindow, const XkWindowScrollPfn);
XK_API_EXPORT void xkSetWindowCloseCallback(XkWindow, const XkWindowClosePfn);
XK_API_EXPORT void xkSetWindowPositionCallback(XkWindow, const XkWindowPositionPfn);
XK_API_EXPORT void xkSetWindowSizeCallback(XkWindow, const XkWindowSizePfn);
XK_API_EXPORT void xkSetWindowFocusCallback(XkWindow, const XkWindowFocusPfn);

XK_API_EXPORT void xkPollWindowEvents(void);
XK_API_EXPORT void xkWaitWindowEvents(void);

