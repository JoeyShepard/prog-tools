#ifndef __GUARD_PROG_TOOLS_FORTH_JIT
    #define __GUARD_PROG_TOOLS_FORTH_JIT

    #include <stdint.h>

    enum ForthJitType
    {
        FORTH_JIT_EMPTY,    //Reclaimed after being used previously
        FORTH_JIT_CONST_
    };

    //Const pool and secondary addresses which also go in constant pool
    //Need table of IDs to addresses anyway for EXEC to work

    struct ForthJitInfo
    {
        uint32_t bytes_left;
        uint32_t element_count;
        struct ForthJitElement
        {
            
            uint8_t type;
            uint8_t id;
        } *elements;
        unsigned char data[];
    };

    int forth_jit(struct ForthEngine *engine);
    int forth_jit_free(struct ForthEngine *engine);

#endif
