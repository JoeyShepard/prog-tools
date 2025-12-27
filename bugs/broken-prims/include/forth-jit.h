#ifndef __GUARD_PROG_TOOLS_FORTH_JIT
    #define __GUARD_PROG_TOOLS_FORTH_JIT

    #include <stdint.h>

    #include "forth.h"

    enum ForthJitType
    {
        FORTH_JIT_EMPTY,    //Reclaimed after being used previously
        FORTH_JIT_CONST_
    };

    //Const pool and secondary addresses which also go in constant pool
    //Need table of IDs to addresses anyway for EXEC to work

    struct ForthJitData
    {
        uint32_t bytes_left;
        unsigned char data[];
    };

    struct ForthJitIDs
    {
        uint32_t bytes_left;
        uint32_t element_count;
        forth_prim_t address[];
    };
    
    struct ForthJitConstants
    {
        uint32_t bytes_left;
        uint32_t element_count;
        struct ForthJitElement
        {
            uint8_t type;
            uint8_t id;
        } elements[];
    };

    int forth_jit(struct ForthCompileInfo *compile);
    int forth_jit_free(struct ForthCompileInfo *compile);

#endif
