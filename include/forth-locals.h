#ifndef __GUARD_PROG_TOOLS_FORTH_LOCALS
    #define __GUARD_PROG_TOOLS_FORTH_LOCALS

    #include "forth-engine.h"

    //Max number of locals a word can have
    #define FORTH_LOCALS_WORD_MAX   32

    //Globals
    extern void (*forth_locals_fetch[])(struct ForthEngine *engine);
    extern void (*forth_locals_store[])(struct ForthEngine *engine);

    //Functions
    void prim_locals_copy(struct ForthEngine *engine);
    void prim_locals_zero(struct ForthEngine *engine);

#endif
