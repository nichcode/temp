
#include "PAL_pch.h"

void PAL_Assert(b8 expr, const char* file, u32 line, const char* msg, ...)
{
    if (expr) {}           
    else {                                                                
        if (msg[0] == 0) {
            PAL_SetError("Assertion failed in %s at line %i", file, line);    
        }  
        else {
            va_list arg_ptr;
            va_start(arg_ptr, msg);
            char* string = PAL_FormatArgs(msg, arg_ptr);
            va_end(arg_ptr);
            PAL_SetError("Assertion failed in %s at line %i \n%s", file, line, string); 
            s_Data.allocator.free(string);
        }   
    }
}