
#include "PAL/PAL_defines.h"

#include "PAL_log.cpp"
#include "PAL_error.cpp"
#include "PAL_input.cpp"
#include "PAL_device.cpp"
#include "PAL_buffer.cpp"
#include "PAL.cpp"

#ifdef PAL_PLATFORM_WINDOWS
#include "win32/PAL_win32_platform.cpp"
#include "win32/PAL_win32_window.cpp"
#include "win32/PAL_wgl_context.cpp"
#endif // PAL_PLATFORM_WINDOWS

// opengl
#include "opengl/PAL_glfuncs.cpp"
#include "opengl/PAL_gldevice.cpp"
#include "opengl/PAL_glbuffer.cpp"

// dx11
#include "dx11/PAL_dx11device.cpp"
#include "dx11/PAL_dx11buffer.cpp"