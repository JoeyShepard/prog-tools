#ifndef __GUARD_PROG_TOOLS_FORTH_ENGINE
    #define __GUARD_PROG_TOOLS_FORTH_ENGINE

    #include <stdint.h>

    #include "forth-primitives.h"

    #define FORTH_STACK_SIZE    256 //See forth-engine! Stack pointer index is byte so circular stack wraps naturally

    //Functions
    //=========
    int forth_process_source(const char *source);

#endif
