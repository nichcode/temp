
#include "PAL/PAL.h"

int main(int argc, char** argv)
{
    PAL_InitData init_data;
    init_data.custom_allocator = false;
    PAL_Init(init_data);

    PAL_Terminate();
    return 0;
}