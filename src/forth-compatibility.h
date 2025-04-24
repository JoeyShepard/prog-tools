//Compatibility layer for Forth engine so engine can be reused on different systems

#ifndef __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY
    #define __GUARD_PROG_TOOLS_FORTH_COMPATIBILITY

    #include "structs.h"

    #define FORTH_MAX_SPACES    1500    //Max for SPACES primitive

    extern struct ConsoleInfo *forth_engine_console;

    void forth_print(const char *text);

#endif
