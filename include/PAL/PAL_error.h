
#pragma once

#include "PAL_defines.h"

#include <stdarg.h>

PAL_API void PAL_SetError(const char* msg, ...);
PAL_API const char* PAL_GetError();
PAL_API void PAL_ClearError();