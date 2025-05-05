
#include "PAL_pch.h"
#include "PAL/PAL.h"
#include "win32/PAL_wgl_context.h"

void* PAL_Alloc(u64 size)
{
    void* memory = malloc(size);
    memset(memory, 0, size);
    return memory;
}

void PAL_Win32Init()
{
    s_Instance = GetModuleHandleW(nullptr);

    WNDCLASSEXW wc = {};
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.cbWndExtra = 0;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursorW(s_Instance, IDC_ARROW);
    wc.hIcon = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hInstance = s_Instance;
    wc.lpfnWndProc = PAL_Win32Proc;
    wc.lpszClassName = s_ClassName;
    wc.lpszMenuName = NULL;
    wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    ATOM success = RegisterClassExW(&wc);
    PAL_CHECK(success, "Win32 window Registration failed", )

    PAL_WGLCreateDummyContext();
    s_Data.directx_flags = PAL_CheckDirectX();
}

void PAL_Win32Terminate()
{
    UnregisterClassW(s_ClassName, s_Instance);
    if (s_Data.directx_flags & PAL_DIRECTX11) {
        PAL_FreeLibrary(s_Data.dx11);
    }

    if (s_Data.directx_flags & PAL_DIRECTX10) {
        PAL_FreeLibrary(s_Data.dx10);
    }
}

PAL_Allocator PAL_GetAllocator()
{
    PAL_Allocator allocator;
    allocator.alloc = PAL_Alloc;
    allocator.free = free;
    allocator.copy = memcpy;
    allocator.set = memset;

    return allocator;
}

i32 PAL_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32 PAL_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
} 

void PAL_WriteConsole(PAL_LogLevel level, const char* msg)
{
    b8 error = level > PAL_LOG_LEVEL_WARN;
    HANDLE console = NULL;
    static u8 levels[4] = { 8, 2, 6, 4 };

    if (error) {
        console = GetStdHandle(STD_ERROR_HANDLE);
    }
    else {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    SetConsoleTextAttribute(console, levels[level]);
    wchar_t* wstring = PAL_ToWstring(msg);
    auto len = wcslen(wstring);
    DWORD number_written = 0;

    WriteConsoleW(console, wstring, (DWORD)len, &number_written, 0);
    SetConsoleTextAttribute(console, 15);
    s_Data.allocator.free(wstring);
}

void* PAL_LoadLibrary(const char* dll_name)
{
    HMODULE result = LoadLibraryA(dll_name);
    if (!result) {
        PAL_SetError( "failed to load dll %s", dll_name);
        return nullptr;
    }
    return result;
}

void* PAL_GetProcAddress(void* dll_name, const char* proc_name)
{
    PAL_CHECK(dll_name, "dll is null", nullptr)
    HMODULE dll_lib = (HMODULE)dll_name;
    FARPROC proc = GetProcAddress((HMODULE)dll_lib, proc_name);
    if (!proc) {
        PAL_SetError("Failed to load function: %s from DLL", proc_name);
        return nullptr;
    }
    return (void*)proc;
}

void PAL_FreeLibrary(void* dll_name)
{
    PAL_CHECK(dll_name, "dll is null",)
    FreeLibrary((HMODULE)dll_name);
}

u32 PAL_CheckDirectX()
{
    u32 directx_flags = 0;
    s_Data.dx11 = PAL_LoadLibrary("d3d11.dll");
    s_Data.dx10 = PAL_LoadLibrary("d3d10.dll");

    if (s_Data.dx11) {directx_flags |= PAL_DIRECTX11; }
    if (s_Data.dx10) {directx_flags |= PAL_DIRECTX10; }
    return directx_flags;
}