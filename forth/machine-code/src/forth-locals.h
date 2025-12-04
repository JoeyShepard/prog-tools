#ifndef __GUARD_PROG_TOOLS_FORTH_LOCALS
    #define __GUARD_PROG_TOOLS_FORTH_LOCALS

    #include "forth-engine.h"

    extern void (*forth_locals_fetch[])(struct ForthEngine *engine);
    extern void (*forth_locals_store[])(struct ForthEngine *engine);

#endif
