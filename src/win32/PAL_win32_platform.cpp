
#include "PAL_pch.h"

void* alloc(u64 size)
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
}

void PAL_Win32Terminate()
{
    UnregisterClassW(s_ClassName, s_Instance);
}

PAL_Allocator PAL_GetAllocator()
{
    PAL_Allocator allocator;
    allocator.alloc = alloc;
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