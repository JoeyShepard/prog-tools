#ifndef __GUARD_PROG_TOOLS_FORTH_CHECK
    #define __GUARD_PROG_TOOLS_FORTH_CHECK

    #include "forth-engine.h"

    #define FORTH_CHECK_MAX     8

    extern void (*forth_checks[FORTH_CHECK_MAX][FORTH_CHECK_MAX])(struct ForthEngine *engine);

#endif
