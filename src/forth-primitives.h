#ifndef __GUARD_PROG_TOOLS_FORTH_PRIMITIVES
    #define __GUARD_PROG_TOOLS_FORTH_PRIMITIVES

    #include <stdint.h>

    //Macro for filling in name and len in struct ForthPrimitive below
    #define PRIMITIVE(x) {x,sizeof(x)-1}

    //structs
    struct ForthPrimitive
    {
        const char *name;
        uint8_t len;
    };

    //Globals
    extern const struct ForthPrimitive forth_primitives[];
    extern const int forth_primitives_len;

#endif
