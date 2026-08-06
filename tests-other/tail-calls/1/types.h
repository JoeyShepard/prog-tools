#ifndef __GUARD_PROG_TOOLS_TYPES
    #define __GUARD_PROG_TOOLS_TYPES

    #ifdef CG50
        //Compiling for calculator. CG50 defined in CMakeLists.txt
    #else
        //Compiling for PC using SDL2 wrapper
        typedef uint16_t color_t;
    #endif
#endif
