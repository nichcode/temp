
#pragma once

#include "PAL_win32.h"
#include "wglext.h"

#include "wingdi.h"

// gdi32 function procs
typedef int WINAPI (*ChoosePixelFormatFun)(HDC hdc,CONST PIXELFORMATDESCRIPTOR *ppfd);
typedef int WINAPI (*SetPixelFormatFun)(HDC hdc,int format,CONST PIXELFORMATDESCRIPTOR *ppfd);
typedef int WINAPI (*DescribePixelFormatFun)(HDC hdc,int iPixelFormat,UINT nBytes,LPPIXELFORMATDESCRIPTOR ppfd);
typedef int WINAPI (*SwapBuffersFun)(HDC hdc);

// wgl function procs
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTPROC) (HDC hDc);
typedef BOOL (WINAPI * PFNWGLDELETECONTEXTPROC) (HGLRC oldContext);
typedef BOOL (WINAPI * PFNWGLMAKECURRENTPROC) (HDC hDc, HGLRC newContext);
typedef PROC (WINAPI * PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);

static ChoosePixelFormatFun s_ChoosePixelFormat = nullptr;
static SetPixelFormatFun s_SetPixelFormat = nullptr;
static DescribePixelFormatFun s_DescribePixelFormat = nullptr;
static SwapBuffersFun s_SwapBuffers = nullptr;

static PFNWGLGETPROCADDRESSPROC s_wglGetProcAddress = nullptr;
static PFNWGLCREATECONTEXTPROC s_wglCreateContext = nullptr;
static PFNWGLDELETECONTEXTPROC s_wglDeleteContext = nullptr;
static PFNWGLMAKECURRENTPROC s_wglMakeCurrent = nullptr;

static PFNWGLSWAPINTERVALEXTPROC s_wglSwapIntervalEXT = nullptr;
static PFNWGLCHOOSEPIXELFORMATARBPROC s_wglChoosePixelFormatARB = nullptr;
static PFNWGLCREATECONTEXTATTRIBSARBPROC s_wglCreateContextAttribsARB = nullptr;

void* PAL_LoadGdiProcs(HMODULE gdi32, const char* func_name);
void* PAL_LoadWGLProcs(HMODULE opengl32, const char* func_name);

void PAL_WGLCreateDummyContext();
HGLRC PAL_WGLCreateContext(HWND window, i32 major, i32 minor);